#include <stdio.h>
#include "HashTable_Node.c"


// 方法一：暴力解法（顺序查找）
Node* commomNode(LinkList str1, LinkList str2) {
    Node *node = str1->next;
    while (node != NULL) {  // 对于链表 str1 中的每个结点 node
        // 判断 node 指向结点是不是也是 str2 中的结点
        Node *p = str2->next;
        while (p != NULL) {
            // 结点指针 node 和结点指针 p 指向的是同一个结点
            // 那么它们指向的结点就是两个链表共同后缀的起始结点
            if (node == p) return node;
            p = p->next;
        }
        node = node->next;
    }
    // 没有共同后缀
    return NULL;
}


// 方法二：哈希查找
Node* commomNode(LinkList str1, LinkList str2) {
    // 声明并初始化哈希表
    HashTable table;
    InitHashTable(&table, 100);

    // 将 str2 中的结点指针都放到哈希表中
    Node *p = str2->next;
    while (p != NULL) {
        PutHashTable(&table, p, true);
        p = p->next;
    }

    Node *node = str1->next;
    while (node != NULL) {  // 对于链表 str1 中的每个结点 node
        // 判断 node 指向结点是不是也是 str2 中的结点
        if (GetHashTable(&table, node, NULL)) return node;
        node = node->next;
    }
    // 没有共同后缀
    return NULL;
}

// 求带有头结点的链表 list 的长度（不包括头结点）
int length(LinkList list) {
    int n = 0;
    Node *curr = list->next;
    while (curr != NULL) {
        n++;
        curr = curr->next;
    }
    return n;
}

// 方法三：降低空间复杂度
Node* commomNode(LinkList str1, LinkList str2) {
    int n = length(str1); // str1 的长度，不包括头结点
    int m = length(str2); // str2 的长度，不包括头结点

    Node *p = str1->next, *q = str2->next;
    if (n > m) {    // str1 比 str2 长
        for (int i = 1; i <= n - m; i++) p = p->next;
    } else if (m > n) {
        for (int i = 1; i <= m - n; i++) q = q->next;
    }

    while (p != NULL && q != NULL) {
        if (p == q) return p; // 找到了共同后缀起始结点
        p = p->next;
        q = q->next;
    }

    // 没有共同后缀
    return NULL;
}

/*
今天更新了 4 道顺序表相关的真题算法题总结，分别是：

2009 年第 42 题：单指针（两趟遍历）→ 双指针（快慢指针一趟遍历）

2012 年第 42 题：暴力解法（顺序查找） → 哈希查找 → 降低空间复杂度

2015 年第 41 题：暴力解法（顺序查找） → 哈希查找 → 数组代替哈希表

2019 年第 41 题：使用辅助数组实现 → 基于反转单链表实现（快慢指针）

每道题都循序渐进，从最容易的暴力解法，一步一步优化，道最优解，每一种实现都能得到相应的分数

以上内容都放在对应真题的解析中了，大家加油~
*/