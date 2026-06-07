#include <stdio.h>

typedef char TElemType;

typedef struct BiTNode {
    TElemType data;          // 数据域

    struct BiTNode *parent;  // 指向双亲的指针域
    struct BiTNode *left;    // 左指针域
    struct BiTNode *right;   // 右指针域
} BiTNode;


int main() {
    BiTNode nodeA;
    nodeA.data = 'A';

    BiTNode nodeB;
    nodeB.data = 'B';

    BiTNode nodeC;
    nodeC.data = 'C';

    BiTNode nodeD;
    nodeD.data = 'D';

    BiTNode nodeE;
    nodeE.data = 'E';

    BiTNode nodeF;
    nodeF.data = 'F';

    nodeA.parent = NULL;
    nodeA.left = &nodeB;
    nodeA.right = &nodeC;

    nodeB.parent = &nodeA;
    nodeB.left = NULL;
    nodeB.right = &nodeD; 

    nodeC.parent = &nodeA;
    nodeC.left = &nodeE;
    nodeC.right = &nodeF; 

    nodeD.parent = &nodeB;
    nodeD.left = NULL;
    nodeD.right = NULL;
    
    nodeE.parent = &nodeC;
    nodeE.left = NULL;
    nodeE.right = NULL; 

    nodeF.parent = &nodeC;
    nodeF.left = NULL;
    nodeF.right = NULL; 
}