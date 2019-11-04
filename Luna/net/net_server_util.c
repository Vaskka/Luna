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
            if(inet_ntop(AF_INET, tmpAddrPtr, ipRef, INET_ADDRSTRLEN))
            {
                status = 0;
                if(strcmp("127.0.0.1",ipRef))
                {
                     break;
                }
            }
        }else if(ifAddrStruct->ifa_addr->sa_family==AF_INET6){
            //可以添加IP6相应代码
        }
        ifAddrStruct=ifAddrStruct->ifa_next;
    }
    return status;
}


// send data through tcp
int sendData(char* destIp, char* data) {
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
    send(sockfd, data, strlen(data), 0);

    // close the socket
    close(sockfd);
    return 0;
}


// listen and receive
int receiveData(char* rootPath, char* relPath) {
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
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
    char buff[20];
    FileParam param;
    param.rootPath = rootPath;
    param.relativePath = relPath;
    param.buffer = buff;
    
    // for test
    int byteCount = 0;
    
    do {
        bzero(param.buffer, strlen(param.buffer));
        connfd = accept(sockfd, (struct sockaddr*) &servaddr, (socklen_t*) &len);
        n = recv(connfd, param.buffer, strlen(param.buffer), 0);
        
        byteCount += n;
        
        appendFileWithPath((void*) &param);
    }
    while (n != 0);

    printf("number of byte is %d\n", byteCount);
    
    // After chatting close the socket
    close(sockfd);
    
    return byteCount;
}
