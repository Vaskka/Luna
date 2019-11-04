//
//  util.c
//  SocketTest
//
//  Created by 曹志铭 on 2019/10/9.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#include "util.h"

/**
    不暴露的接口，工具函数
 */

// 数字字符映射

char numberToChar(int i) {
    if (i > 9 || i < 0) {
        raise_error("convert invalid number to char.");
    }
    
    return (char) (i + 48);
}

/**
 暴露接口实现
 */

// 检查是否是test结尾
int endWith(const char* original, const char* test) {
    int len = strlen(test);
    int orlen = strlen(original);
    
    for (int i = len - 1; i >= 0; i--) {
        if (*(original + orlen - 1 - i) != *(test + len - 1 - i)) {
            return 0;
        }
    }
    
    return 1;
}

// 检查是否是start开始
int startWith(const char * original, const char* test) {
    int len = strlen(test);
    
    for (int i = 0; i < len; i++) {
        if (*(original + i) != *(test + i)) {
            return 0;
        }
    }
    
    return 1;
}

// sub string
char* subString(char* original, int startIndex, int endIndex) {
    int len = strlen(original);
    
    if (startIndex < 0 || endIndex < 0 || startIndex >= len || endIndex > len || startIndex > endIndex) {
        return original;
    }
    
    char* result = (char*) malloc(sizeof(char) * (endIndex - startIndex + 1));
    
    int k = 0;
    for (int i = startIndex; i < endIndex; i++, k++) {
        
        *(result + k) = *(original + i);
    }
        
    *(result + k) = '\0';
    
    return result;

}

// 连接两个路径
char* joinPath(const char* p1, const char* p2) {
    int len1 = strlen(p1);
    int len2 = strlen(p2);
    char* p1convert;
    char* p2convert;
    
    // 去除p1结尾的'/'
    if (endWith(p1, "/")) {
        p1convert = subString(p1, 0, len1 - 1);
        len1--;
    }
    else {
        p1convert = p1;
    }
    
    // 去除p2开头的'/'
    if (startWith(p2, "/")) {
        p2convert = subString(p2, 1, len2);
        len2--;
    }
    else {
        p2convert = p2;
    }
    
    // 连接
    char* result = malloc(sizeof(char) * (len1 + len2 + 2));
    
    int i;
    for (i = 0; i < len1; i++) {
        *(result + i) = *(p1convert + i);
    }
    
    *(result + i) = '/';
    
    for (i = len1 + 1; i < len1 + len2 + 1; i++) {
        *(result + i) = *(p2convert + i - len1 - 1);
    }
    
    *(result + i) = '\0';
    
    return result;
    
}


// unsigned int 2 char*
char* convertUnsignedIntegerToString(unsigned int ui) {
    return convertUnsignedLongToString(ui);
}


// unsigned long 2 char*
char* convertUnsignedLongToString(unsigned long ul) {
    
    unsigned long value = ul < 0 ? -ul : ul;
    
    // 统计位数
    int count = 0;
    while (value > 0) {
        value /= 10;
        count++;
    }
    
    // 申请空间
    int length = count + 1;
    char* resString = (char*) malloc(sizeof(char) * length);
    
    // 依次赋值
    int lastIndex = length - 1;
    resString[lastIndex] = '\0';

    value = ul < 0 ? -ul : ul;
    while (value > 0) {
        lastIndex--;
        resString[lastIndex] = numberToChar(value % 10);
        value /= 10;
    }
    
    return resString;
}


// long long 2 char*
char* convertLongLongToString(long long ll) {
    int negative = ll < 0 ? 1 : 0;
    
    long long value = ll < 0 ? -ll : ll;
    
    // 统计位数
    int count = 0;
    while (value > 0) {
        value /= 10;
        count++;
    }
    
    // 申请空间
    int length = count + 1 + negative;
    char* resString = (char*) malloc(sizeof(char) * length);
    
    if (negative) {
        resString[0] = '-';
    }
    
    // 依次赋值
    int lastIndex = length - 1;
    resString[lastIndex] = '\0';

    value = ll < 0 ? -ll : ll;
    while (value > 0) {
        lastIndex--;
        resString[lastIndex] = numberToChar(value % 10);
        value /= 10;
    }
    
    return resString;
    
}


// 整数2char*
char* convertIntegerToString(int i) {
    
    return convertLongToString(i);
}

// long2char*
char* convertLongToString(long l) {
    
    return convertLongLongToString(l);
}
