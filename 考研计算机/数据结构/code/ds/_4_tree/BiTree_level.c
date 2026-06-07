#include <stdio.h>

#include "BiTree.h"
#include "LinkQueue.c"

// 层序遍历二叉树 T
void LevelOrderTraverse(BiTree T) {
    // 初始化一个队列，用于暂存下一层的结点
    LinkQueue queue;
    InitQueue(&queue);

    EnQueue(&queue, T);

    QElemType e;
    // 只要队列不空，就出队访问
    while (DeQueue(&queue, &e)) {
        printf("%c, ", e->data);
        // 判断将结点的左右子结点入队
        if (e->left) EnQueue(&queue, e->left);
        if (e->right) EnQueue(&queue, e->right);
    }

    DestroyQueue(&queue);
}

// 层序遍历二叉树 T
int LevelOrderTraverse_2(BiTree T) {
    // 初始化一个队列，用于暂存下一层的结点
    LinkQueue queue;
    InitQueue(&queue);

    EnQueue(&queue, T);

    int depth = 0;

    QElemType e;
    // 只要队列不空，就出队访问
    while (!QueueEmpty(&queue)) {
        int sz = QueueLength(&queue);
        for (int i = 0; i < sz; i++) {
            DeQueue(&queue, &e);
            printf("%c, ", e->data);
            // 判断将结点的左右子结点入队
            if (e->left) EnQueue(&queue, e->left);
            if (e->right) EnQueue(&queue, e->right);
        }
        depth++;
    }

    DestroyQueue(&queue);

    return depth;
}


int main() {
    BiTree T = GetTestBiTree();

    printf("LevelOrderTraverse Seq: ");
    LevelOrderTraverse(T);
    printf("\n");
}