#include <stdio.h>

#include "HashTable.c"

// 表示单链表结点
typedef struct Node {
    int data;
    struct Node *link;
} Node, *LinkList;

// 求整数 a 的绝对值
int abs(int a) {
    if (a < 0) return -a;
    return a;
}

// 方法一：暴力解法
void delSameData(LinkList HEAD) {
    Node *node = HEAD->link;
    while (node != NULL) {
        Node *p = node;
        Node *q = node->link;
        while (q != NULL) {
            // 判断 q 结点和 node 结点的值的绝对值是否相等
            if (abs(q->data) == abs(node->data)) {
                // 如果相等，则删除结点 q
                p->link = q->link;
                free(q);

                q = p->link;
            } else { // 否则，p 和 q 同时往前走一步
                p = p->link;
                q = q->link;
            }
        }
        node = node->link;
    }
}

// 方法二：哈希查找
void delSameData(LinkList HEAD) {
    // 声明和初始化一个哈希表
    HashTable table;
    InitHashTable(&table, 100);

    Node *p = HEAD;
    Node *node = HEAD->link;
    while (node != NULL) {
        // 判断结点 node 的值的绝对值是否存在于哈希表
        if (GetHashTable(&table, abs(node->data), NULL)) {
            // 如果存在，则删除结点 node
            p->link = node->link;
            free(node);

            node = p->link;
        } else { // 如果不存在，node 值绝对值是第一次出现
            p = p->link;
            node = node->link;
            PutHashTable(&table, abs(node->data), 1);
        }
    }
}


// 方法三：使用数组代替哈希表
void delSameData(LinkList HEAD, int n) {
    // 声明和初始化长度为 n + 1 的数组
    // visited[i] = true 表示正整数 i 之前出现过
    bool visited[n + 1];
    // 初始化所有的正整数 0 ~ n 都没有出现过
    for (int i = 0; i <= n; i++) visited[i] = false;

    Node *p = HEAD;
    Node *node = HEAD->link;
    while (node != NULL) {
        // 判断结点 node 的值的绝对值之前是否出现过
        if (visited[abs(node->data)]) {
            // 如果存在，则删除结点 node
            p->link = node->link;
            free(node);

            node = p->link;
        } else { // 如果不存在，node 值绝对值是第一次出现
            p = p->link;
            node = node->link;
            visited[abs(node->data)] = true;  // 设置为出现过
        }
    }
}