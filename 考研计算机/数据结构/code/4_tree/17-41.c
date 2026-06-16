（1）递归中序遍历该表达式树：若为根节点，则不加括号；若为非根结点，则先输出左括号“(”，再去中序遍历这棵子树，中序遍历完子树后输出右括号“)”。
（2）

typedef struct node {
    //存储操作数或操作符
    char data[10];
    struct node *left,*right;
}BTree;
// 中序遍历将二叉表达式树转换为中缀表达式并输出
void InRecurtion(BTree *T, BTree *parent) {  // parent表示T的父节点；根节点的父节点为NULL，也就是说第一次传入时，parent为NULL
    // 若为空
    if (!T)
        return;
    if (parent)
        printf("(");
    InRecurtion(T->left, T);
    printf("%s", T->data);
    InRecurtion(T->right, T);
    if (parent)
        printf(")");
}
