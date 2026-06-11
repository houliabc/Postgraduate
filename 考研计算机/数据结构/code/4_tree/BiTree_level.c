#include <stdio.h>
#include "BiTree.h"
#include "LinkQueue.c"

// 层序遍历二叉树 T
void LevelOrderTraverse(BiTree T) {
    if (!T)
        return;

    // 首先初始化一下队列
    LinkQueue Q;
    InitQueue(&Q);

    // 先将根去入队，之后就遍历队列不为空为止
    EnQueue(&Q, T);
    ElemType e;
    while (DeQueue(&Q, &e)) {
        printf("%c-", e->data);
        // 如果有左右孩子，则加入队列
        if (e->left)
            EnQueue(&Q, e->left);
        if (e->right)
            EnQueue(&Q, e->right);
    }
    // 别忘了销毁队列
    DestroyQueue(&Q);
}

// 层序遍历二叉树 T，并返回树的深度
int LevelOrderTraverse_2(BiTree T) {
    if (!T)
        return 0;

    // 首先初始化一下队列
    LinkQueue Q;
    InitQueue(&Q);
    int n = 0, length;

    // 先将根去入队，之后就遍历队列不为空为止
    EnQueue(&Q, T);
    ElemType e;
    while (QueueEmpty(&Q)) {
        length = QueueLength(&Q);
        // 表示每轮循环访问一层所有结点，同时高度加一
        for (int i = 0; i < length; i++) {
            DeQueue(&Q, &e);
            printf("%c-", e->data);
            // 如果有左右孩子，则加入队列
            if (e->left)
                EnQueue(&Q, e->left);
            if (e->right)
                EnQueue(&Q, e->right);
        }
        n++;
    }
    // 别忘了销毁队列
    DestroyQueue(&Q);
    return n;
}

int main() {
    BiTree T = GetTestBiTree();

    printf("LevelOrderTraverse Seq: ");
    LevelOrderTraverse(T);
    printf("\n");
}