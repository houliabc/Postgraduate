#include <stdio.h>
#include <stdlib.h>

#include "../_3_special_line/LinkStack.c"

typedef struct BSTNode{
    int data;
    struct BSTNode*left,*right;
} BSTNode;

typedef BSTNode* Btree;

void searchX(Btree root, int k) {
    // 声明一个链式栈来保存绝对值最小的所有结点关键字
    LinkStack results;
    InitStack(&results);
    int minDiff = INT_MAX;
    BSTNode* curr = root;
    while (curr) {
        int diff = abs(curr->data - k);
        if (diff < minDiff) { // 找到更小的绝对值
            minDiff = diff;
            ClearStack(&results); // 清除之前比较大的绝对值的关键字
            Push(&results, curr->data); // 存放当前最小绝对值的关键字
        } else if (diff == minDiff) {
            // 如果绝对值相等，则直接将结点关键字放到结果集
            Push(&results, curr->data);
        }
        
        if (k < curr->data) curr = curr->left;
        else if (k > curr->data) curr = curr->right;
        else break; // 找到了最小的绝对值 0，没必要往下找了
    }
    printf("最小的绝对值：%d", minDiff);
    int key;
    while(Pop(results, &key)) printf("对应的关键字：%d", key);
}

// 声明一个链式栈来保存绝对值最小的所有结点关键字
LinkStack results;
int minDiff = INT_MAX;

// 前序遍历
void preOrder(BSTNode* node, int k) {
    int diff = abs(node->data - k);
    if (diff < minDiff) { // 找到更小的绝对值
        minDiff = diff;
        ClearStack(&results); // 清除之前比较大的绝对值的关键字
        Push(&results, node->data); // 存放当前最小绝对值的关键字
    } else if (diff == minDiff) {
        // 如果绝对值相等，则直接将结点关键字放到结果集
        Push(&results, node->data);
    }

    preOrder(node->left, k);
    preOrder(node->right, k);
}

void searchX(Btree root, int k) {
    InitStack(&results);
    // 前序遍历二叉树的每个结点
    preOrder(root, k);

    printf("最小的绝对值：%d", minDiff);
    int key;
    while(Pop(results, &key)) printf("对应的关键字：%d", key);
}