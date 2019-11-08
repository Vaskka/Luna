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
 TODO: 文件夹/文件没有就创建
 */



int main(int argc, const char * argv[]) {
    
    
//    pthread_create(&pid, NULL, luna_ping, NULL);
//
//
//    while (1) {
//
//    }

    //printf("%s\n", getLunaProtocal("uidddd", "rel/path/to/path.ccc", "datadatatasdafwefwfdsvdsvdssdfds"));
        //receiveData("/Users/vaskka/Desktop", "a.txt");
    receiveData("/Users/vaskka/Desktop");
    //sendData("127.0.0.1", "asdfghjklkjhjkjhjkjhj");
    //sendData("127.0.0.1", "uidddddd", "a/b/c/m.txt", "datadatatasdafwefwfdsvdsvdssdfds");
    
    return 0;
}
