#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 表示单链表结点
typedef struct Node {
    char c;
    struct Node *next;
} Node, *LinkList;

typedef Node* KeyType;
typedef bool ValueType;

typedef struct {
    KeyType key;
    ValueType value;
    bool isNull;   // 该结点是否为空，true 表示空，否则表示不空
    bool deleted;   // 该结点是否标记为删除，true 表示标记这个键值对已经删除
} HashNode;

// 基于线性探测的散列表
typedef struct {
    int n;          // 散列表中键值对的数量
    int m;              // 散列表的大小
    HashNode *table;    
} HashTable;

// 初始化散列表，其长度为 m
void InitHashTable(HashTable *ht, int m) {
    ht->m = m;
    ht->n = 0;

    ht->table = (HashNode *) malloc (m * sizeof(HashNode));
    for (int i = 0; i < m; i++) {
        // 初始化所有单元为空
        ht->table[i].isNull = true;
        ht->table[i].deleted = false;
    }
}

// 销毁查找表
void DestroyHashTable(HashTable *ht) {
    free(ht->table);
}

// 散列函数：计算 key 的散列地址
int Hash(int m, KeyType key) {
    return abs(key) % m;
}

// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
bool GetHashTable(HashTable *ht, KeyType key, ValueType *val) {
    int i = Hash(ht->m, key);
    while (!ht->table[i].isNull) {
        // 当前键值对没有标记删除，并且 key 等于当前键值对的 key
        if (!ht->table[i].deleted && key == ht->table[i].key) {
            if (val != NULL) *val = ht->table[i].value;
            return true;
        }
        i = (i + 1) % ht->m;
    }
    return false;
}

// 扩容操作
void resize(HashTable *ht, int newSize) {
    HashNode *newTable = (HashNode *) malloc (newSize * sizeof(HashNode));
    for (int i = 0; i < newSize; i++) {
        // 初始化所有单元为空
        newTable[i].isNull = true;
        newTable[i].deleted = false;
    }

    for (int i = 0; i < ht->m; i++) {
        HashNode node = ht->table[i];
        if (!node.isNull && !node.deleted) {
            // 重新计算散列地址
            int hash = Hash(newSize, node.key);
            // 线性探测插入位置
            while (!newTable[hash].isNull) {
                hash = (hash + 1) % newSize;
            }
            // 键值对插入到新的散列表中
            newTable[hash].key = node.key;
            newTable[hash].value = node.value;
            newTable[hash].isNull = false;
            newTable[hash].deleted = false;
        }
    }
    free(ht->table);

    // 将散列表中的 table 指向新的散列表数组
    ht->m = newSize;
    ht->table = newTable;
}

// 将键值对存入表中
void PutHashTable(HashTable *ht, KeyType key, ValueType value) {
    // 保证散列表的装载因子不会超过 0.5
    if (ht->n >= ht->m / 2) resize(ht, 2 * ht->m);
    int i = Hash(ht->m, key);
    while (!ht->table[i].isNull) {
        if (key == ht->table[i].key) {
            ht->table[i].value = strdup(value);
            ht->table[i].deleted = false;
            return;
        }
        i = (i + 1) % ht->m;
    }

    // 插入新键值对
    ht->table[i].key = key;
    ht->table[i].value = strdup(value);
    ht->table[i].isNull = false;
    ht->table[i].deleted = false;

    ht->n++;
}

void DeleteHashTable(HashTable *ht, KeyType key) {
    int i = Hash(ht->m, key);
    while (!ht->table[i].isNull) {
        if (!ht->table[i].deleted && key == ht->table[i].key) {
            // 标记当前键值对为删除状态
            ht->table[i].deleted = true;
            free(ht->table[i].value);
            ht->n--;
            return;
        }
        i = (i + 1) % ht->m;
    }
}