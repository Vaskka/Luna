//
//  linkedlist.h
//  linkedlist
//
//  Created by Vaskka on 2019/10/28.
//  Copyright © 2019 Vaskka. All rights reserved.
//

#ifndef linkedlist_h
#define linkedlist_h

#include "../common/struct_common.h"

// 内部节点
typedef struct LinkedListItem {

    void* value;

    struct LinkedListItem* prePointer;

    struct LinkedListItem* nextPointer;

} LinkedListItem;


// linkedlist
typedef struct LinkedList {
    
    LinkedListItem* head;

    LinkedListItem* tail;

    LinkedListItem* curr;

    int size;
    
} LinkedList;



/* 迭代器方法 */

// 创建迭代器引用
void llIteratorInit(LinkedList* original);

// hasNext
int llIteratorHasNext(const LinkedList* original);

// next获得内部用户数据
void* llIteratorNext(LinkedList* original);

// 关闭迭代器
void llIteratorClose(LinkedList* original);

/* 链表方法 */


// 创建一个list
LinkedList* llCreateList(void);

// 增加一个element在尾部
void llAddLast(LinkedList* list, void* ele);

// 增加一个element在首部
void llAddFirst(LinkedList* list, void* ele);

// 获取头部第一个元素的引用
void* llGetFirst(const LinkedList* list);

// 获取尾部第一个元素的引用
void* llGetLast(const LinkedList* list);

// 插入一个element
void llInsert(LinkedList* list, int index, void* ele);

// 删除首部第一个element（不会回收内部用户数据所分配的内存，只会回收节点的内存，使用时需要注意内存泄漏问题）
void llRemoveFirstElement(LinkedList* list);

// 删除尾部第一个element（不会回收内部用户数据所分配的内存，只会回收节点的内存，使用时需要注意内存泄漏问题）
void llRemoveLastElement(LinkedList* list);

// 删除指定e位置的元素
void llRemoveIndexElement(LinkedList* list, int index);

// 获取第index的ele, index < 0 等效于 index == 0, index >= size 等效于 index == size
void* llGet(const LinkedList* list, int index);

// 获取真实大小
int llGetSize(const LinkedList* list);

// 销毁一个list, 不会回收内部用户数据所分配的内存，只会回收节点的内存，使用时需要注意内存泄漏问题）
void llDestory(LinkedList* list);

// 销毁list并释放内部用户数据
void llDestoryAndFree(LinkedList* list);


// 链表连接
void llAppendLinkedList(LinkedList* original, LinkedList* appendList);



#endif /* linkedlist_h */
