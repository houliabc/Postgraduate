#include "../../BiTree.h"

#include "ExpTreeInit.c"

// 执行运算
int GetValue(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
    }
    return 0;
}

// 后序遍历计算表达式树的值
// 每次遍历处理完一个结点，都要返回计算结果，因此递归函数有返回值
int EvaluateExpTree(BiTree T) {
    if (T == NULL) return 0;

    // 如果是叶子结点，则直接返回结点的整数
    if (!T->left && !T->right) {
        return T->data - '0'; // 因为结点元素是 char 类型，减去字符 0 就可以得到相应的整数
    }

    // 后序遍历计算左子树的值
    int lvalue = EvaluateExpTree(T->left);
    // 后序遍历计算右子树的值
    int rvalue = EvaluateExpTree(T->right);

    // 根据当前结点的运算符，将左子树返回的值和右子树返回的值做相应的运算
    return GetValue(T->data, lvalue, rvalue);
}

// 中序遍历二叉树 T
void InOrderTraverse(BiTree T) {
    if (T == NULL) return;

    // 中序遍历左子树
    InOrderTraverse(T->left);
    // 打印根节点的值，表示访问根结点
    printf("%c", T->data);
    // 中序遍历右子树
    InOrderTraverse(T->right);
}

int main() {
    char *exp = "3 + 4 * ( 2 - 3 ) - 6 / 2";
     BiTree T = InitExpTree(exp);
    InOrderTraverse(T);

    printf("\n");

    printf("the res = %d\n", EvaluateExpTree(T));

    return 0;
}