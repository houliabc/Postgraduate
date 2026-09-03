
// 三元组元素
typedef struct {
    int i;      // 行号
    int j;      // 列号
    int value;  // 非零元素值
} Element;

// 三元组表
typedef struct {
    Element *table;     // 三元组表
    int length;         // 三元组表的长度

    int m;              // 矩阵总行数
    int n;              // 矩阵总列数
} TripleTable;


typedef int ElemType;

// 结点
typedef struct OLNode {
    // 非零元素的行号和列号
    int row, col; 
    ElemType val;
    // 向右域和向下域
    struct OLNode *right, *down; 
} OLNode, *OLink;

// 十字链表
typedef struct{
    // 行链表和列链表的头指针数组
    OLink *rhead, *chead; 
    // 稀疏矩阵的行数、列数和非零元素个数
    int mu, nu, tu; 
} CrossList;

