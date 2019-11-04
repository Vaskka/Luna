//
//  file_util.c
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include "file_util.h"

// 获取文件大小
FILE_LEN file_size(char* filename) {
    struct stat statbuf;
    stat(filename, &statbuf);
    unsigned long size = statbuf.st_size;
 
    return size;
}

// 读取文件信息 can running in thread
void* readFileWithPath(void* _FILEPARAM param) {
    
    FileParam* fileParam = (FileParam*) param;
    
    char* abspath = joinPath(fileParam->rootPath, fileParam->relativePath);
    FILE_LEN size = file_size(abspath);
    
    FILE* file = fopen(abspath, "rb");
    if (file == NULL) {
        raise_error("文件打开失败");
        return (void*) 1;
    }
    
    fileParam->buffer = _STRING malloc(sizeof(char) * size + 1);
    
    int i = 0;
    char ch = fgetc(file);
    while (ch != EOF) {
        *(fileParam->buffer + i) = ch;
        ch = fgetc(file);
        i++;
    }
    
    *(fileParam->buffer + i) = '\0';

    fclose(file);
    
    return (void*) 0;
}


// 向路径写入文件(新建文件并写入) can running in thread
void* writeFileWithPath(void* _FILEPARAM param) {
    
    FileParam* fileParam = (FileParam*) param;
    
    char* abspath = joinPath(fileParam->rootPath, fileParam->relativePath);
    FILE* file = fopen(abspath, "wb");
    if (file == NULL) {
        raise_error("文件打开失败");
    }
    
    // write content
    FILE_LEN i;
    FILE_LEN len = strlen(fileParam->buffer);
    for (i = 0; i < len; i++) {
        fputc(*(fileParam->buffer + i), file);
    }
    
    fclose(file);
    
    return (void*) 0;
}

// 判断路径是否存在 1-存在 0-不存在
int pathExist(const char* path) {
    return access(path, F_OK) < 0 ? 0 : 1;
}


// 获取路径中最后一级文件名
char* getFinalFileName(char* path) {
    
    if (!pathExist(path)) {
        raise_error("when get file final filename, the path does not exist.");
        return NULL;
    }
    
    int len = strlen(path);
    
    for (int i = len - 1; i >= 0; i--) {
        if (*(path + i) == '/') {
            char* filename = subString(path, i + 1, len);
            return filename;
        }
    }
    
    return path;
}


