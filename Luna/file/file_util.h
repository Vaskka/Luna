//
//  file_util.h
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef file_util_h
#define file_util_h

#include <unistd.h>
#include <sys/stat.h>

#include "../common.h"
#include "../utils/util.h"
#include "../common/struct_common.h"



typedef struct FileParam {
    // 文件根目录的绝对路径
    char* rootPath;
    
    // 相对根目录的j相对路径
    char* relativePath;
    
    // 读或写的缓存区，规定最后一个byte一定是'\0'，标志结束此'\0'不是文件c内容，仅作为内容的结束标志。
    char* buffer;
} FileParam;


// 读取文件信息 can running in thread
void* readFileWithPath(void* _FILEPARAM param);


// 向路径写入文件(新建文件并写入)
void* writeFileWithPath(void* _FILEPARAM param);

// 获取文件大小
FILE_LEN file_size(char* filename);

// 判断路径是否存在 1-存在 0-不存在
int pathExist(const char* path);

// 获取路径中最后一级文件名
char* getFinalFileName(char* path);

#endif /* file_util_h */
