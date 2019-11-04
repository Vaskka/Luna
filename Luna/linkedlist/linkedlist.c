#include "linkedlist.h"


/* 迭代器实现 */

// 创建迭代器引用
void llIteratorInit(LinkedList* original) {

    original->curr = original->head;
}

// hasNext
int llIteratorHasNext(const LinkedList* original) {
    return original->curr == NULL ? 0 : 1;
}

// next获得内部用户数据
void* llIteratorNext(LinkedList* original) {

    if (!llIteratorHasNext(original)) {
        raise_error("LinkedList iterator is invalid or closed.");
        return NULL;
    }

    void* data = original->curr->value;
    original->curr = original->curr->nextPointer;

    return data;
}

// 关闭迭代器
void llIteratorClose(LinkedList* original) {
    original->curr = NULL;
}


/* 链表实现 */


// 创建一个list
LinkedList* llCreateList(void) {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->size = 0;
    list->head = list->tail = NULL;
    list->curr = NULL;

    return list;
}

// 增加一个element在尾部
void llAddLast(LinkedList* list, void* ele) {

    LinkedListItem* item = (LinkedListItem*) malloc(sizeof(LinkedListItem));
    item->value = ele;
    item->prePointer = NULL;
    item->nextPointer = NULL;

    // 链表为空
    if (list->size == 0) {
        list->head = item;
        list->tail = item;
        list->size++;
    }
    else {
        //链表不为空
        list->tail->nextPointer = item;
        item->prePointer = list->tail;
        list->tail = item;

        list->size++;
    }

}

// 增加一个element在首部
void llAddFirst(LinkedList* list, void* ele) {
    LinkedListItem* item = (LinkedListItem*) malloc(sizeof(LinkedListItem));
    item->value = ele;
    item->prePointer = NULL;
    item->nextPointer = NULL;

    // 链表为空
    if (list->size == 0) {
        list->head = item;
        list->tail = item;
        list->size++;
    }
    else {
        // 链表不为空
        list->head->prePointer = item;
        item->nextPointer = list->head;
        list->head = item;
        list->size++;

        
    }

}

// 获取头部第一个元素的引用
void* llGetFirst(const LinkedList* list) {
    return list->head->value;
}

// 获取尾部第一个元素的引用
void* llGetLast(const LinkedList* list) {
    return list->tail->value;
}

// 插入一个element, index < 0 等效于 index == 0, index >= size 等效于 index == size
void llInsert(LinkedList* list, int index, void* ele) {

    if (index <= 0) {
        llAddFirst(list, ele);
        return;
    }

    if (index >= list->size) {
        llAddLast(list, ele);
        return;
    }

    // find index node
    int i = 0;
    LinkedListItem* curr = list->head;
    while (i < index) {
        curr = curr->nextPointer;
        i++;
    }

    // init node
    LinkedListItem* newItem = (LinkedListItem*) malloc(sizeof(LinkedListItem));
    newItem->value = ele;
    newItem->prePointer = NULL;
    newItem->nextPointer = NULL;

    // do insert

    if (list->size == 0) {
        list->head = list->tail = newItem;
    }
    else {
        newItem->prePointer = curr->prePointer;
        newItem->nextPointer = curr;
        curr->prePointer->nextPointer = newItem;
        curr->prePointer = newItem;
    }
    list->size++;
}

// 删除首部第一个element（不会回收内部用户数据所分配的内存，只会回收节点的内存，使用时需要注意内存泄漏问题）
void llRemoveFirstElement(LinkedList* list) {
    if (list->size == 0) {
        return;
    }
    
    if (list->size == 1) {
        free(list->head);
        list->head = list->tail = NULL;
        list->size--;
        return;
    }

    LinkedListItem* orginalHead = list->head;
    
    // 更新head
    list->head = list->head->nextPointer;
    list->head->prePointer = NULL;
    
    // 释放内存
    orginalHead->nextPointer = NULL;
    free(orginalHead);

    // 处理size
    list->size--;
    if (list->size == 0) {
        list->head = list->tail = NULL;
    }
}

// 删除尾部第一个element（不会回收内部用户数据所分配的内存，只会回收节点的内存，使用时需要注意内存泄漏问题）
void llRemoveLastElement(LinkedList* list) {
    if (list->size == 0) {
        return;
    }
    
    if (list->size == 1) {
        free(list->tail);
        list->head = list->tail = NULL;
        list->size--;
        return;
    }

    LinkedListItem* newTail = list->tail->prePointer;
    
    // 释放内存
    free(list->tail);
    
    // 更新tail
    list->tail = newTail;
    list->tail->nextPointer = NULL;
    
    // 处理size
    list->size--;

}


// 删除指定e位置的元素
void llRemoveIndexElement(LinkedList* list, int index) {
    
    if (index < 0 || index >= list->size) {
        raise_error("LinkedList remove: index out of range.");
        return;
    }
    
    if (index == 0) {
        llRemoveFirstElement(list);
        return;
    }
    
    if (index == list->size - 1) {
        llRemoveLastElement(list);
        return;
    }
    
    LinkedListItem* temp = list->head;
    
    for (int i = 0; i < index; i++) {
        temp = temp->nextPointer;
    }
    
    LinkedListItem* usedPreNode = temp->prePointer;
    usedPreNode->nextPointer = temp->nextPointer;
    temp->nextPointer->prePointer = usedPreNode;
    free(temp);
    list->size--;
    if (list->size == 0) {
        list->head = list->tail = NULL;
    }

}


// 获取第index的ele, index < 0 等效于 index == 0, index >= size 等效于 index == size
void* llGet(const LinkedList* list, int index) {
    if (index < 0) {
        index = 0;
    }

    if (index >= list->size) {
        index = list->size - 1;
    }

    // find which is index
    int i = 0;
    LinkedListItem* curr = list->head;
    while (i < index) {
        curr = curr->nextPointer;
        i++;
    }

    return curr->value;
}

// 获取真实大小
int llGetSize(const LinkedList* list) {
    return list->size;
}

// 销毁一个list（不会回收内部用户数据所分配的内存，只会回收节点的内存，使用时需要注意内存泄漏问题）
void llDestory(LinkedList* list) {
    while (list->size != 0) {
        llRemoveLastElement(list);
    }

    free(list);
}

// 销毁list并释放内部用户数据
void llDestoryAndFree(LinkedList* list) {
    while (list->size != 0) {
        void* val = llGetLast(list);
        free(val);
        llRemoveLastElement(list);
    }

    free(list);
}


// 链表连接
void llAppendLinkedList(LinkedList* original, LinkedList* appendList) {

    llIteratorInit(appendList);

    while (llIteratorHasNext(appendList)) {
        llAddLast(original, llIteratorNext(appendList));
    }

    llIteratorClose(appendList);
}
