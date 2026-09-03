#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int KeyType;
typedef char* ValueType;

// 单链表结点
typedef struct node {
    KeyType key;
    ValueType value;
    struct node *next;
} LNode, *LinkList;

// 索引表中的分块索引
typedef struct {
    KeyType maxKey; // 分块中的最大关键字
    LNode *head;    // 指向分块单链表头结点
} BlockIndex;   // 分块索引类型

// 分块查找表
typedef struct {
    BlockIndex *blocks; // 索引表
    int blkCnt;         // 分块的数量
} BSTable;     // Block Search Table   

// 折半查找：在索引表中找到第一个大于等于 key 的最大关键字所在的分块索引
int BinarySearch(BSTable *table, KeyType key) {
    int low = 0, high = table->blkCnt - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key < table->blocks[mid].maxKey) {  // 找到大于 key 的最大关键字
            if (mid == 0 || key > table->blocks[mid - 1].maxKey) return mid;
            else high = mid - 1;    // 不是第一个大于 key 的最大关键字，则继续去左边找
        } else if (key > table->blocks[mid].maxKey) {
            low = mid + 1;
        } else return mid;
    }

    // 找不到大于等于 key 的最大关键字，返回 -1
    return -1;
}


// 在分块查找表中分块查找一个 key
// 如果存在则返回这个关键字所在的结点，如果不存在，则返回 NULL
LNode *BlockSearch(BSTable *table, KeyType key) {
    // 1. 根据索引表确定待查关键字所在的分块

    int blockIdx = BinarySearch(table, key);

    // 顺序查找索引表中第一个大于等于 key 的最大关键字所在的分块索引
    /*for (int i = 0; i < table->blkCnt; i++) {
        if (table->blocks[i].maxKey >= key) {
            blockIdx = i;
            break;
        }
    }*/

    // 如果所有块的最大关键字都小于 key，则未找到
    if (blockIdx == -1) return NULL;

    // 2. 在确定分块中顺序查找关键字
    LNode *p = table->blocks[blockIdx].head->next;
    while (p) {
        if (key == p->key) return p;
        p = p->next;
    }

    return NULL;
}

// 获取指定 key 的值
ValueType Get(BSTable *table, KeyType key) {
    
}

// 插入或更新键值对
void Put(BSTable *table, KeyType key, ValueType value) {
    
}


// 删除指定 key 的节点
void Delete(BSTable *table, KeyType key) {
    
}