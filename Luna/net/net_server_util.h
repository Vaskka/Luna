//
//  net_server_util.h
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef net_server_util_h
#define net_server_util_h

// std lib
#include <string.h>

// net dependence
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <ifaddrs.h>

#include "../common.h"
#include "net_constant.h"


// send ping running in thread
void* luna_ping(void* s);

// send broadcast text running in thread
void* broadcast_text(void* _CHARABLE text);

// get host ip for it self
int getSelfIp(char* ipRef);

// send data through tcp
int sendData(char* destIp, char* data);

#endif /* net_server_util_h */
