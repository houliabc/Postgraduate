#include <stdio.h>

#include "BiTree.h"
#include "SqStack.c"

// ---- 迭代实现二叉树的先、中、后序遍历 --------

// 先序遍历二叉树 T
void PreOrderTraverse_Iter(BiTree T) {
    // 初始化一个栈
    SqStack stack;
    InitStack(&stack);

    // 从根结点开始
    BiTNode *curr = T;

    SElemtype e;
    // 只要 curr 不为空，或者 curr 为空，但是栈不空，那么继续遍历二叉树
    while (curr || !StackEmpty(&stack)) {
        if (curr) {
            printf("%c, ", curr->data);
            Push(&stack, curr);
            curr = curr->left;
        } else {
            Pop(&stack, &e);
            curr = e->right;
        }
    }

     DestroyStack(&stack);
}

// 中序遍历二叉树 T
void InOrderTraverse_Iter(BiTree T) {
    // 初始化一个栈
    SqStack stack;
    InitStack(&stack);

    // 从根结点开始
    BiTNode *curr = T;

    SElemtype e;
    // 只要 curr 不为空，或者 curr 为空，但是栈不空，那么继续遍历二叉树
    while (curr || !StackEmpty(&stack)) {
        if (curr) {
            Push(&stack, curr);
            curr = curr->left;
        } else {
            Pop(&stack, &e);
            printf("%c, ", e->data);
            curr = e->right;
        }
    }

     DestroyStack(&stack);
}

// 后序遍历二叉树 T
void PostOrderTraverse_Iter(BiTree T) {
    // 初始化一个栈
    SqStack stack;
    InitStack(&stack);

    // 从根结点开始
    BiTNode *curr = T;
    // lastVisited 指向的结点表示以这个结点为根的子树刚刚被遍历完
    BiTNode *lastVisited = NULL;

    SElemtype e;
    // 只要 curr 不为空，或者 curr 为空，但是栈不空，那么继续遍历二叉树
    while (curr || !StackEmpty(&stack)) {
        if (curr) {
            Push(&stack, curr);
            curr = curr->left;
        } else {
            GetTop(&stack, &e);
            // 如果右子树存在且未被访问过，就去访问右子树
            if (e->right && e->right != lastVisited) {
                curr = e->right;
            } else { // 右子树不存在，或者右子树存在，但是已经被访问
                Pop(&stack, &e);
                printf("%c, ", e->data);
                lastVisited = e;
            }
        }
    }

     DestroyStack(&stack);
}
 


int main() {
    BiTree T = GetTestBiTree();
    
    printf("PreOrderTraverse Seq: ");
    PreOrderTraverse_Iter(T);
    printf("\n");

    printf("InOrderTraverse_Iter Seq: ");
    InOrderTraverse_Iter(T);
    printf("\n");

    printf("PostOrderTraverse_Iter Seq: ");
    PostOrderTraverse_Iter(T);
    printf("\n");
}