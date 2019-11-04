//
//  main.c
//  Luna
//
//  Created by 曹志铭 on 2019/10/12.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include <stdio.h>

#include "utils/util.h"
#include "common.h"
#include "file/file_util.h"
#include "datastruct/strtype_tree.h"
#include "datastruct/stringbuilder/stringbuilder.h"
#include "net/net_server_util.h"

/**
 TODO: socket
 */

int main(int argc, const char * argv[]) {
    
    
//    pthread_create(&pid, NULL, luna_ping, NULL);
//
//
//    while (1) {
//
//    }
    char* path ="/Users/vaskka/Desktop";
    FileParam param;
    param.rootPath = path;
    param.relativePath = "b.c";
    
    readFileWithPath((void*) &param);
    
    printf("length is:%d\n", strlen(param.buffer));
    
    sendData("192.168.43.203", param.buffer);

    return 0;
}
