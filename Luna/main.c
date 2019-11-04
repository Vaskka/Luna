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

    while (1) {
        receiveData("/Users/vaskka/Desktop", "a.txt");
    }

    
    return 0;
}
