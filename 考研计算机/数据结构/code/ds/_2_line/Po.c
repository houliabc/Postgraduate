
// 一元多项式的项
struct Polynomial {
   float  coef;         //系数
   int   expn;          //指数
};

// 将结构体 Polynomial 命名为 ElemType
typedef struct Polynomial ElemType;

// 单链表的结点
typedef struct node {
    ElemType *data;        // 数据域（存储一元多项式的项）       
    struct node *next;     // 指针域             
} LNode, * LinkList;                     


