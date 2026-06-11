#include <stdio.h>
#include "BiTree.h"
#include "SqStack.c"

// ---- 迭代实现二叉树的先、中、后序遍历 --------

// 先序遍历二叉树 T
void PreOrderTraverse_Iter(BiTree T) {
    if (!T) return;
    // 先初始化一个栈
    SqStack S;
    InitStack(&S);

    // 循环去迭代T中的元素
    BiTNode *cur = T;
    // 如果cur非空或者栈中还有数据表示没有迭代完，则要继续迭代下去
    while (cur || !StackEmpty(&S)) {
        // 根-左-右
        // 如果有结点，那肯定要输出啦，不然就从栈中弹出结点出来
        if (cur) {
            printf("%c-", cur->data);
            Push(&S, cur);
            cur = cur->left;
        }
        else {
            // 如果没有结点，那必然是要从栈中拿去结点来处理的
            ElemType e;
            Pop(&S, &e);
            // 前面根和左都访问完了，那就到右了
            cur = e->right;
        }
    }
    // 销毁栈
    DestroyStack(&S);
}

// 中序遍历二叉树 T
void InOrderTraverse_Iter(BiTree T) {
    if (!T) return;
    // 先初始化一个栈
    SqStack S;
    InitStack(&S);

    // 循环去迭代T中的元素
    BiTNode *cur = T; ElemType e;
    // 如果cur非空或者栈中还有数据表示没有迭代完，则要继续迭代下去
    while (cur || !StackEmpty(&S)) {
        // 左-根-右
        // 如果有结点，先入栈，然后访问其左节点，后续才输出
        if (cur) {
            Push(&S, cur);
            cur = cur->left;
        }
        else {
            // 如果没有结点，那必然是要从栈中拿去结点来处理的
            Pop(&S, &e);
            // 前面根和左都访问完了，那就到右了
            printf("%c-", e->data);
            // 右
            cur = e->right;
        }
    }
    // 销毁栈
    DestroyStack(&S);
}

// 后序遍历二叉树 T
void PostOrderTraverse_Iter(BiTree T) {
    if (!T) return;
    // 先初始化一个栈
    SqStack S;
    InitStack(&S);

    // 循环去迭代T中的元素
    BiTNode *cur = T, *visited = NULL; 
    ElemType e;
    // 如果cur非空或者栈中还有数据表示没有迭代完，则要继续迭代下去
    while (cur || !StackEmpty(&S)) {
        // 左-右-根
        // 如果有结点，先入栈，然后访问其左节点，后续才输出
        if (cur) {
            Push(&S, cur);
            cur = cur->left;
        }
        else {
            // 如果没有结点，那必然是要从栈中拿去结点来处理的（只不过先不删除，因为根还没访问呢）
            GetTop(&S, &e);
            // 如果没有右节点，或者右节点且已被访问，就直接弹出输出了，同时更新visited
            if (!e->right || visited == e->right) {
                Pop(&S, &e);
                printf("%c-", e->data);
                visited = e;
            }
            // 若有右节点且未被访问过
            else {
                cur = e->right;
            }
        }
    }
    // 销毁栈
    DestroyStack(&S);
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