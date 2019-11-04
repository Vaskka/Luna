//
//  arraylist.h
//  arraylist
//
//  Created by 曹志铭 on 2019/10/10.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef arraylist_h
#define arraylist_h

#include "../common/struct_common.h"

#define DEFAULT_INIT_SIZE 64
#define MAX_SIZE 65536
#define EACH_APPEND_SIZE 1024


typedef struct ArrayList {
    
    void** innerArray;
    
    // 真实个数
    int size;
    
    // 已分配个数
    int count;
    
    
} ArrayList;

// 创建一个list
ArrayList* alCreateList(int initSize);

// 增加一个element
void alAdd(ArrayList* list, void* ele);

// 插入一个element
void alInsert(ArrayList* list, int index, void* ele);

// 删除index位置的element（不会回收remove的地址所分配的内存，使用时需要注意内存泄漏问题）
void alRemoveIndexElement(ArrayList* list, int index);

// 删除搜索到的第一个element（不会回收remove的地址所分配的内存，使用时需要注意内存泄漏问题）
void alRemoveElement(ArrayList* list, void* ele);

// 获取第index的ele
void* alGet(const ArrayList* list, int index);

// 获取真实大小
int alGetSize(const ArrayList* list);

// 销毁一个list
void alDestory(ArrayList* list);

// // 内部检查扩展空间
// void _extendSize(ArrayList* list);

#endif /* arraylist_h */
