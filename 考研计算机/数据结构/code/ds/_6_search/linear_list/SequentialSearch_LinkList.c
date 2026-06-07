#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef int KeyType;
typedef char* ValueType;

// 基于单链表构建查找表
typedef struct node {
    KeyType key;
    ValueType value;
    struct node *next;
} Node, *SSTable;

// 初始化查找表
void InitSSTable(SSTable *table) {
    // 初始化一个头结点
    *table = (Node *)malloc(sizeof(Node));
    (*table)->next = NULL;
}

// 销毁查找表
void DestroySSTable(SSTable table) {
    // 第一步：先释放所有非头结点内存空间
    Node *p = table->next;
    while (p) {
        Node *q = p;
        p = p->next;
        free(q);
    }

    // 第二步：再释放头结点内存空间
    free(table);
}

// 时间复杂度：O(n)
// 在查找表中查找指定的 key，如果存在，则返回 key 所在结点，否则，返回 NULL
Node *SeqSearch(SSTable table, KeyType key) {
    // 从首元结点开始顺序查找
    Node *curr = table->next;
    while (curr) {
        if (curr->key == key) 
            return curr;
        curr = curr->next;
    }
    // 不存在 key 
    return NULL;
}

// 时间复杂度：O(n)
// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
ValueType GetSSTable(SSTable table, KeyType key) {
    Node *node = SeqSearch(table, key);
    if (node) return node->value;
    return NULL;
}

// 时间复杂度：O(n)
// 将键值对存入表中
bool PutSSTable(SSTable table, KeyType key, ValueType value) {
    Node *node = SeqSearch(table, key);
    if (node) { // 如果 key 存在，则直接更新 value
        free(node->value);
        node->value = strdup(value);
        return false;
    }

    // key 不存在，创建新节点
    Node *newNode = (Node *) malloc (sizeof(Node));
    newNode->key = key;
    newNode->value = strdup(value);

    // 插入到头结点的后面
    newNode->next = table->next;
    table->next = newNode;
    return true;
}

// 从表中删除键 key (对应的值也删掉)
// 时间复杂度：O(n)
bool DeleteSStable(SSTable table, KeyType key) {
    Node *curr = table->next;
    Node *prev = table;
    while (curr) {
        if (curr->key == key) { // key 存在，删除
            prev->next = curr->next;
            free(curr);
            return true;
        }
        // bug fix：将当前结点 curr 设置为前一个结点
        prev = curr;
        curr = curr->next;
    }
    return false;
}

/*
int main() {
    SSTable table;
    InitSSTable(&table);

    PutSSTable(table, 10, "laotang");
    PutSSTable(table, 12, "douma");
    PutSSTable(table, 13, "algo");
    PutSSTable(table, 8, "lisi");

    printf("key = 12, value = %s\n", GetSSTable(table, 12)); // 打印 douma

    PutSSTable(table, 12, "data structure");
    printf("key = 12, value = %s\n", GetSSTable(table, 12)); // 打印 data structure

    DeleteSStable(table, 12);
    printf("key = 12, value = %s\n", GetSSTable(table, 12)); // 打印空

    DestroySSTable(table);

    return 0;
}
*/