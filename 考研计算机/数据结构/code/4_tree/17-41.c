（1）
中序遍历给定的二叉树，对左子树的遍历在其遍历内容的左右两侧加上括号，对右子树的遍历也在其遍历内容的左右两侧加上括号；
（2）

typedef struct node {
    //存储操作数或操作符
    char data[10];
    struct node *left,*right;
}BTree;
// 中序遍历将二叉表达式树转换为中缀表达式并输出
void InRecurtion(BTree *T) {
    if (T == NULL)
        return;
    
}
