//
//  stringbuilder.h
//  Luna
//
//  Created by 曹志铭 on 2019/10/30.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef stringbuilder_h
#define stringbuilder_h

#include "../../common.h"
#include "../../linkedlist/linkedlist.h"
#include "../../utils/util.h"

#include <string.h>


typedef struct StringBuilder {
    // 字符序列
    LinkedList* sequence;
    
} StringBuilder;

// 创建字符串构造器
StringBuilder* initStringBuilder(char* seq);

/**
 append and insert method
 */

// append一个字符
void appendChar(StringBuilder* ref, const char c);

// append一个数字
void appendInteger(StringBuilder* ref, const int i);

// append一个长整型
void appendLong(StringBuilder* ref, const long li);

// append一个long long
void appendLongLong(StringBuilder* ref, const long long ll);

// append一个无符号整型
void appendUnsignedInteger(StringBuilder* ref, const unsigned int ui);

// append一个无符号长整型
void appendUnsignedLong(StringBuilder* ref, const unsigned long ul);

// append一个字符串
void appendString(StringBuilder* ref, const char* s);

// append另一个字符构造器
void appendStringBuilder(StringBuilder* ref, const StringBuilder* stringBuilder);


// insert一个字符
void insertChar(StringBuilder* ref, const char c, const int index);

// insert一个数字
void insertInteger(StringBuilder* ref, const int i, const int index);

// insert一个long
void insertLong(StringBuilder* ref, const long li, const int index);

// insert一个long long
void insertLongLong(StringBuilder* ref, const long long ll, const int index);

// insert一个无符号整型
void insertUnsignedInteger(StringBuilder* ref, const unsigned int ui, const int index);

// insert一个无符号长整型
void insertUnsignedLong(StringBuilder* ref, const unsigned long ul, const int index);

// insert一个字符串
void insertString(StringBuilder* ref, const char* s, const int index);

/**
 remove method
 */

// 删除第index个字符
void removeIndexChar(StringBuilder* ref, const int index);

/**
 get attr of this builder
 */

// 得到c风格字符串
char* toString(const StringBuilder* ref);

// 得到长度
int length(const StringBuilder* ref);

// destory字符串构造器
void destoryStringBuilder(StringBuilder* ref);

#endif /* stringbuilder_h */
