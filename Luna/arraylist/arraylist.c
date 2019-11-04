//
//  arraylist.c
//  arraylist
//
//  Created by 曹志铭 on 2019/10/10.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include "arraylist.h"


// 内部检查扩展空间
void _extendSize(ArrayList* list) {
    if (list->count == list->size) {
       // max memery
       if (list->count >= MAX_SIZE) {
           char error_msg[64];
           
           sprintf(error_msg, "out of max size: %d", list->count);
           raise_error(error_msg);
           
           return;
       }
       
       // append size
        if ((list->count + EACH_APPEND_SIZE) > MAX_SIZE) {
            list->count = MAX_SIZE;
        }
        else {
            list->count = list->count + EACH_APPEND_SIZE;
        }
       
       // append size
       void** newList = malloc(sizeof(void*) * list->count);
       
       // copy original
       for (int i = 0; i < list->size; i++) {
           *(newList + i) = *(list->innerArray + i);
       }
    
        free(list->innerArray);
        list->innerArray = newList;
           
    }
}


// 创建一个list
ArrayList* alCreateList(int initSize) {
    
    if (initSize <= 0) {
        initSize = DEFAULT_INIT_SIZE;
    }
    
    ArrayList* list;
    list = malloc(sizeof(ArrayList));
    
    list->innerArray = malloc(sizeof(void*) * initSize);
    list->size = 0;
    list->count = initSize;
    
    return list;
}

// 增加一个element
void alAdd(ArrayList* list, void* ele) {
   
    _extendSize(list);
    *(list->innerArray + list->size) = ele;
    list->size++;
    
}

// 插入一个element
void alInsert(ArrayList* list, int index, void* ele) {
    _extendSize(list);

    if (index < 0 || index > list->size) {
        char error_msg[64];
        
        sprintf(error_msg, "index out of range:%d", index);
        raise_error(error_msg);
        return;
    }
    
    for (int i = list->size; i > index; i--) {
        *(list->innerArray + i) = *(list->innerArray + i - 1);
    }
    
    *(list->innerArray + index) = ele;
    list->size++;
}

// 删除index位置的element
void alRemoveIndexElement(ArrayList* list, int index) {
    if (index < 0 || index > list->size) {
        char error_msg[64];
        
        sprintf(error_msg, "index out of range:%d", index);
        raise_error(error_msg);
        return;
    }
    
    for (int j = index; j < list->size - 1; j++) {
        *(list->innerArray + j) = *(list->innerArray + j + 1);
    }
    
    list->size--;
}

// 删除搜索到的第一个element
void alRemoveElement(ArrayList* list, void* ele) {
    for (int i = 0; i < list->size; i++) {
        if (*(list->innerArray + i) == ele) {
            for (int j = i; j < list->size - 1; j++) {
                *(list->innerArray + j) = *(list->innerArray + j + 1);
            }
            
            list->size--;
        }
    }
}

// 获取第index的ele
void* alGet(const ArrayList* list, int index) {
        
    // out of range
    if (index < 0 || index >= list->size) {
        char error_msg[64];
        
        sprintf(error_msg, "index out of range:%d", index);
        raise_error(error_msg);
        return (void*) -1;
    }
    
    return *(list->innerArray + index);
}

// 获取size
int alGetSize(const ArrayList* list) {
    return list->size;
}

// 销毁一个list
void alDestory(ArrayList* list) {
    // 释放内部数组
    free(list->innerArray);
    
    // 释放本身
    free(list);
}


