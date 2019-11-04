//
//  util.h
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef util_h
#define util_h

#include <string.h>
#include <math.h>
#include "../common.h"
#include "../common/struct_common.h"
#include "../linkedlist/linkedlist.h"

/**
 字符串操作
 */

// 检查是否是test结尾
int endWith(const char* original, const char* test);

// s检查是否是test开始
int startWith(const char * original, const char* test);

// 连接两个路径
char* joinPath(const char* p1, const char* p2);

// sub string
char* subString(char* original, int startIndex, int endIndex);

/**
 各种类型转换
 */

// 整字2char*
char* convertIntegerToString(int i);

// long2char*
char* convertLongToString(long l);

// unsigned int 2 char*
char* convertUnsignedIntegerToString(unsigned int ui);

// unsigned long 2 char*
char* convertUnsignedLongToString(unsigned long ul);

// long long 2 char*
char* convertLongLongToString(long long ll);


/**
 链表额外操作
 */

// 链表连接操作
void appendLinkedList(LinkedList* original, const LinkedList* appendList);


#endif /* util_h */
