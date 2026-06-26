//MAX_SIZE为已定义常量
typedef struct {
    int SqBiTNode[MAx_SIZE];   //保存二叉树结点值的数组
    int ElemNum;//实际占用的数组元素个数
} SqBiTree;
（1）从下标0开始，依次去判断其左右孩子（若有）的情况，要求左孩子的值小于当前结点值，右子树的值大于当前结点值，同时对其左右孩子也进行判断。若有任意一个顶点不满足，则不是二叉排序树，返回false；否则循环完后都没有不满足的顶点，则说明该树是一颗二叉排序树，返回true
（2）
bool isBST(SqBiTree tree, int i) {  // 传入进去当前处理的结点下标，初始值是0
    int n = tree.ElemNum;  // 数组元素个数
    // 如果当前下标超出了数组元素，则return true
    if (i >= n)
        return true;
    // 判断当前结点是否满足左孩子<该结点<右孩子（前提是有孩子）
    int left = 2 * i + 1, right = 2 * i + 2;  // 计算得到左孩子和右孩子
    if (tree.SqBiTNode[left] != -1 && tree.SqBiTNode[left] > tree.SqBiTNode[i]) // 左孩子值大于当前结点，则不符合
        return false;
    if (tree.SqBiTNode[right] != -1 && tree.SqBiTNode[right] < tree.SqBiTNode[i]) // 右孩子值小于当前结点，则不符合
        return false;
    // 递归判断左右子树是否符合二叉排序树
    bool leftTree = isBST(tree, left);
    bool rightTree = isBST(tree, right);
    // 只有说当前结点、左右子树都符合二叉排序树时，才是真的二叉排序树，返回true
    return leftTree && rightTree;
}

（2）
bool isBST(SqBiTree tree, int i) {  // 传入进去当前处理的结点下标，初始值是0
    int n = tree.ElemNum;  // 数组元素个数
    // 如果当前下标超出了数组元素，则return true
    if (i >= n)
        return true;
    // 判断当前结点是否满足左孩子<该结点<右孩子（前提是有孩子）
    int left = 2 * i + 1, right = 2 * i + 2;  // 计算得到左孩子和右孩子
    if (left < n && tree.SqBiTNode[left] != -1 && tree.SqBiTNode[left] > tree.SqBiTNode[i]) // 左孩子值大于当前结点，则不符合
        return false;
    if (tree.SqBiTNode[right] != -1 && tree.SqBiTNode[right] < tree.SqBiTNode[i]) // 右孩子值小于当前结点，则不符合
        return false;
    // 递归判断左右子树是否符合二叉排序树
    bool leftTree = isBST(tree, left);
    bool rightTree = isBST(tree, right);
    // 只有说当前结点、左右子树都符合二叉排序树时，才是真的二叉排序树，返回true
    return leftTree && rightTree;
}