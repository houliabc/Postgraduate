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

// 创建新节点
LNode* CreateNode(KeyType key, ValueType value) {
    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->key = key;
    node->value = strdup(value); // 复制字符串
    node->next = NULL;
    return node;
}

// 初始化分块查找表
void InitTable(BSTable *table, int blkCnt) {
    table->blkCnt = blkCnt;
    table->blocks = (BlockIndex*)malloc(sizeof(BlockIndex) * blkCnt);
    
    // 初始化每个分块的链表头节点
    for (int i = 0; i < blkCnt; i++) {
        table->blocks[i].head = CreateNode(-1, "HEAD"); // 头节点
        table->blocks[i].maxKey = INT_MIN;
    }
}

// 释放表内存
void DestroyTable(BSTable* table) {
    for (int i = 0; i < table->blkCnt; i++) {
        LNode* p = table->blocks[i].head;
        while (p) {
            LNode* temp = p;
            p = p->next;
            if (temp->value) free(temp->value);
            free(temp);
        }
    }
    
    free(table->blocks);
}

// 折半查找：在索引表中找到第一个大于等于 key 的最大关键字所在的分块索引
int BinarySearch(BSTable *table, KeyType key) {
    int low = 0, high = table->blkCnt - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key < table->blocks[mid].maxKey) { // 找到大于 key 的最大关键字
            // 如果这个最大关键字是索引表的第一个分块索引的，直接返回 mid
            // 否则，如果 key 大于这个最大关键字前面的最大关键字，直接返回 mid
            if (mid == 0 || key > table->blocks[mid - 1].maxKey) return mid;
            else high = mid - 1;    // 不是第一个大于等于 key 的最大关键字，则继续去左边找
        } else if (key > table->blocks[mid].maxKey) low = mid + 1;
        else return mid;
    }
    // 找不到大于等于 key 的最大关键字，返回 -1
    return -1;
}


// 在分块查找表中分块查找一个 key
// 如果存在则返回这个关键字所在的结点，如果不存在，则返回 NULL
// 总时间复杂度：O(logb + n/b)
LNode *BlockSearch(BSTable *table, KeyType key, LNode **prev) {
    // 1. 根据索引表确定待查关键字所在的分块
    int blockIdx = BinarySearch(table, key);

    // 如果所有块的最大关键字都小于 key，则未找到
    if (blockIdx == -1) return NULL;

    // 2. 在确定分块中顺序查找关键字
    // 时间复杂度：O(n/b)，其中 n 是所有元素的总数，n/b 是平均每个分块的元素数量
    LNode *p = table->blocks[blockIdx].head->next;
    // 前一个结点
    LNode *q = table->blocks[blockIdx].head;
    while (p) {
        if (p->key == key) {
            if (prev) *prev = q;
            return p;
        }
        q = p; // 设置 p 为前一个结点
        p = p->next;
    }

    if (prev) *prev = q;
    return NULL;
}

// 获取指定 key 的值
ValueType Get(BSTable *table, KeyType key) {
    LNode *curr = BlockSearch(table, key, NULL);
    if (curr && curr->key == key) return curr->value;
    else return NULL;
}

// 插入或更新键值对
void Put(BSTable *table, KeyType key, ValueType value) {
    LNode *curr = BlockSearch(table, key, NULL);
    
    // 更新已有键的值
    if (curr) {
        free(curr->value);
        curr->value = strdup(value);
        return;
    }
    
    // 确定插入位置对应的分块索引
    int blockIdx = BinarySearch(table, key);
    if (blockIdx == -1) blockIdx = table->blkCnt - 1;
    
    // 插入新节点到头结点的后面
    LNode *newNode = CreateNode(key, value);
    LNode *head = table->blocks[blockIdx].head;
    newNode->next = head->next;
    head->next = newNode;
    
    // 更新块的最大 key
    if (key > table->blocks[blockIdx].maxKey) {
        table->blocks[blockIdx].maxKey = key;
    }
}


// 删除指定 key 的节点
void Delete(BSTable *table, KeyType key) {
    LNode *prev;
    LNode *curr = BlockSearch(table, key, &prev);
    
    // 未找到该 key
    if (!curr) return;
    
    // 从链表中删除结点
    prev->next = curr->next;
    free(curr->value);
    free(curr);
    
    // 可能需要更新块的 maxKey
    int blockIdx = BinarySearch(table, key);
    
    // 如果删除的是最大 key，需要重新计算
    if (key == table->blocks[blockIdx].maxKey) {
        LNode* p = table->blocks[blockIdx].head->next;
        KeyType newMaxKey = -1;
        while (p) {
            if (p->key > newMaxKey) newMaxKey = p->key;
            p = p->next;
        }
        table->blocks[blockIdx].maxKey = newMaxKey;
    }
}

int main() {
    BSTable table;
    InitTable(&table, 3);

    // 插入一些数据
    Put(&table, 10, "Value10");
    Put(&table, 20, "Value20");
    Put(&table, 5, "Value5");
    Put(&table, 25, "Value25");
    Put(&table, 15, "Value15");
    
    // 查询测试
    printf("Key 10: %s\n", Get(&table, 10)); // 输出: Value10
    printf("Key 25: %s\n", Get(&table, 25)); // 输出: Value25
    
    // 更新测试
    Put(&table, 10, "Updated10");
    printf("Key 10: %s\n", Get(&table, 10)); // 输出: Updated10
    
    // 删除测试
    Delete(&table, 20);
    printf("Key 20: %s\n", Get(&table, 20)); // 输出: (null)
    
    // 清理内存
    DestroyTable(&table);
    
    return 0;
}