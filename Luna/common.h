//
//  common.h
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef common_h
#define common_h

#include <stdio.h>
#include <stdlib.h>

// 标记需要转换 void*  to  char*
#define _CHARABLE

// 需要转换为文件参数结构指针，定义在utils/file_util.h
#define _FILEPARAM

// 转换为String
#define _STRING (char *)

#define FILE_LEN unsigned long

#endif /* common_h */
