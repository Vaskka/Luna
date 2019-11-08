//
//  net_server_util.c
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include "net_server_util.h"


// send ping
void* luna_ping(void* s) {
    
    return broadcast_text(PING_TEXT);
}


// send broadcast
void* broadcast_text(void* text) {
    
    char* readChars = (char*) text;
    
    int brdcFd;
    if((brdcFd = socket(PF_INET, SOCK_DGRAM, 0)) == -1){
        printf("socket fail\n");
        return (void*) ERROR_SOCKET_CREATE;
    }
    
    int optval = 1;
    setsockopt(brdcFd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int));
        
    struct sockaddr_in theirAddr;
    memset(&theirAddr, 0, sizeof(struct sockaddr_in));
    
    // server地址和监听端口
    theirAddr.sin_family = AF_INET;
    theirAddr.sin_addr.s_addr = inet_addr(HOST_ARRE);
    theirAddr.sin_port = htons(HOST_PORT);
    int sendBytes;
    
    // loop send ping
    while((sendBytes = sendto(brdcFd, readChars, strlen(readChars), 0,
            (struct sockaddr *)&theirAddr, sizeof(struct sockaddr))) != -1){
        printf("msg=%s, msgLen=%lu, sendBytes=%d\n", readChars, strlen(readChars), sendBytes);
    }
    
    // echo wrong and close socket
    printf("broadcast fail, errno=%d\n", errno);
    close(brdcFd);
    
    // return error code
    return (void*) ERROR_SOCKET_SEND;
    
    
}

// get host ip for it self
int getSelfIp(char* ipRef) {
    struct ifaddrs * ifAddrStruct=NULL;
    void * tmpAddrPtr=NULL;
    int status = -1;

    getifaddrs(&ifAddrStruct);

    while (ifAddrStruct!=NULL)
    {
        if (ifAddrStruct->ifa_addr->sa_family==AF_INET)  // check it is IP4
        {
            tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            if (inet_ntop(AF_INET, tmpAddrPtr, ipRef, INET_ADDRSTRLEN))
            {
                status = 0;
                if (strcmp("127.0.0.1",ipRef))
                {
                     break;
                }
            }
        } else if(ifAddrStruct->ifa_addr->sa_family==AF_INET6){
            //可以添加IP6相应代码
        }
        ifAddrStruct=ifAddrStruct->ifa_next;
    }
    
    return status;
}


// get luna-protocal string
char* getLunaProtocal(char* uid, char* pathToFile, char* data) {
    
    cJSON* root = cJSON_CreateObject();
    cJSON* rootType = cJSON_CreateNumber(0);
    cJSON* rootContent = cJSON_CreateObject();
    
    cJSON* contentData = cJSON_CreateString(data);
    cJSON* contentPath = cJSON_CreateString(pathToFile);
    cJSON* contentLength = cJSON_CreateNumber(strlen(data));
    cJSON* contentId = cJSON_CreateString(uid);
    
    cJSON_AddItemToObject(rootContent, "id", contentId);
    cJSON_AddItemToObject(rootContent, "path", contentPath);
    cJSON_AddItemToObject(rootContent, "length", contentLength);
    cJSON_AddItemToObject(rootContent, "data", contentData);
    
    cJSON_AddItemToObject(root, "type", rootType);
    cJSON_AddItemToObject(root, "content", rootContent);
    
    char* res = cJSON_Print(root);
    cJSON_Delete(root);

    return res;
}


// send data through tcp
int sendData(char* destIp, char* uid, char* pathToFile, char* data) {
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(destIp);
    servaddr.sin_port = htons(TRANSFER_PORT);

    // connect the client socket to server socket
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    //send data
    // 构造协议结构
    char* buff = getLunaProtocal(uid, pathToFile, data);
    
    
    size_t n = send(sockfd, buff, strlen(buff), 0);
    free(buff);
    printf("send: %s, count: %ld", buff, n);
//    int factor = 2;
//    unsigned long border = (len - (len % factor));
//    for (int i = 0; i < border / factor; i++) {
//        size_t n = send(sockfd, data + (i * factor), factor, 0);
//        printf("send %s:count:%ld\n", (data + (i * factor)),n);
//    }
//
//    size_t n = send(sockfd, data + border, len % factor, 0);
//    printf("send %s:count:%ld\n", data + border,n);
    
    // close the socket
    close(sockfd);
    return 0;
}



// 构造FileParam
FileParam* getFileParam(char* rootPath, char* receiveData) {
    FileParam* param = (FileParam*) malloc(sizeof(FileParam));
    param->rootPath = rootPath;
    
    cJSON* root = cJSON_Parse(receiveData);
    
    int type = cJSON_GetObjectItem(root, "type")->valueint;
    cJSON* content = cJSON_GetObjectItem(root, "content");
    if (type) {
        // 1-control
    }
    else {
        // 0-data
        
        // 路径结构: id/rel/path/to/file.xxx
        char* id = cJSON_GetObjectItem(content, "id")->valuestring;
        char* path = cJSON_GetObjectItem(content, "path")->valuestring;
        char* relPath = joinPath(id, path);
        
        param->relativePath = relPath;
        
        // copy data
        param->buffer = (char*) malloc(sizeof(char) * cJSON_GetObjectItem(content, "length")->valueint);
        strcpy(param->buffer, cJSON_GetObjectItem(content, "data")->valuestring);
    }
    
    cJSON_Delete(root);
    return param;
}



// listen and receive
int receiveData(char* rootPath) {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr;

    // socket create and verification
                //todo

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror ("socket create error");
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(TRANSFER_PORT);

    // Binding newly created socket to given IP and verification
                //todo
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror ("socket bind error");
        return 2;
    }

    // Now server is ready to listen and verification
                //todo
    if (listen(sockfd, 10) == -1) {
        perror ("socket listen error");
        return 3;
    }

    // Accept the data packet from client and verification
                //todo
    len = sizeof(servaddr);
    
    ssize_t n = 0;
    char* buff = (char*) malloc(sizeof(char) * 1024 * 1024 * 20);
    
    do {
        
        connfd = accept(sockfd, (struct sockaddr*) &servaddr, (socklen_t*) &len);
        n = recv(connfd, buff, 8192, 0);
        
        if (n < 0) {
            raise_error("tcp receive error");
            continue;
        }
        
        if (n == 0) {
            raise_error("tcp receive empty message");
            continue;
        }
        
        // 根据协议构造FileParam
        FileParam* param = getFileParam(rootPath, buff);
        
        writeFileWithPath((void*) &param);
        printf("read data:%s, count:%d\n", buff, n);
    }
    while (1);
    
    // After chatting close the socket
    close(sockfd);
    
    return 0;
}
