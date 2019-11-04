//
//  stringbuilder.c
//  Luna
//
//  Created by 曹志铭 on 2019/10/30.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include "stringbuilder.h"

// 创建字符串构造器
StringBuilder* initStringBuilder(char* seq) {
    
    StringBuilder* res = (StringBuilder*) malloc(sizeof(StringBuilder));
    res->sequence = llCreateList();
    if (seq != NULL) {
        appendString(res, seq);
    }

    return res;
}

/**
 append and insert method
 */

// append一个字符
void appendChar(StringBuilder* ref, const char c) {
    llAddLast(ref->sequence, (void*) c);
}

// append一个数字
void appendInteger(StringBuilder* ref, const int i) {
    
    appendString(ref, convertIntegerToString(i));
}

// append一个长整型
void appendLong(StringBuilder* ref, const long li) {
    appendString(ref, convertLongToString(li));
}

// append一个long long
void appendLongLong(StringBuilder* ref, const long long ll) {
    appendString(ref, convertLongLongToString(ll));
}

// append一个无符号整型
void appendUnsignedInteger(StringBuilder* ref, const unsigned int ui) {
    appendString(ref, convertUnsignedIntegerToString(ui));
}

// append一个无符号长整型
void appendUnsignedLong(StringBuilder* ref, const unsigned long ul) {
    appendString(ref, convertUnsignedLongToString(ul));
}

// append一个字符串
void appendString(StringBuilder* ref, const char* s) {
    
    for (unsigned long i = 0; i < strlen(s); i++) {
        appendChar(ref, *(s + i));
    }
}

// append另一个字符构造器
void appendStringBuilder(StringBuilder* ref, const StringBuilder* stringBuilder) {
    llAppendLinkedList(ref->sequence, stringBuilder->sequence);
}


// insert一个字符
void insertChar(StringBuilder* ref, const char c, const int index) {
    
    llInsert(ref->sequence, index, (void*) c);
}

// insert一个数字
void insertInteger(StringBuilder* ref, const int i, const int index) {
    insertString(ref, convertIntegerToString(i), index);
}

// insert一个long
void insertLong(StringBuilder* ref, const long li, const int index) {
    insertString(ref, convertLongToString(li), index);
}


// insert一个long long
void insertLongLong(StringBuilder* ref, const long long ll, const int index) {
    insertString(ref, convertLongLongToString(ll), index);
}

// insert一个无符号整型s
void insertUnsignedInteger(StringBuilder* ref, const unsigned int ui, const int index) {
    insertString(ref, convertUnsignedIntegerToString(ui), index);
}

// insert一个无符号长整型
void insertUnsignedLong(StringBuilder* ref, const unsigned long uli, const int index) {
    insertString(ref, convertUnsignedLongToString(uli), index);
}

// insert一个字符串
void insertString(StringBuilder* ref, const char* s, const int index) {
    
    for (unsigned long i = 0; i < strlen(s); i++) {
        insertChar(ref, *(s + i), index + i);
    }
}

/**
 remove method
 */

// 删除第index个字符
void removeIndexChar(StringBuilder* ref, const int index) {
    llRemoveIndexElement(ref->sequence, index);

}

/**
 get attr of this builder
 */

// 得到长度
int length(const StringBuilder* ref) { return llGetSize(ref->sequence); }

// 得到c风格字符串
char* toString(const StringBuilder* ref) {
    
    int len = length(ref);
    char* res = (char*) malloc(sizeof(char) * (len + 1));
    res[len] = '\0';

    llIteratorInit(ref->sequence);
    
    int i = 0;
    while (llIteratorHasNext(ref->sequence)) {
        *(res + i) = (char) llIteratorNext(ref->sequence);
        i++;
    }
    
    llIteratorClose(ref->sequence);
    return res;
}


// destory字符串构造器
void destoryStringBuilder(StringBuilder* ref) {
    
    llDestory(ref->sequence);
    free(ref);
}
