#include <stdio.h>


typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;


// 打印单链表 L【递归】
void TraverseList(LinkList L) {
    if (L == NULL) return;
    printf("%d\n", L->data);
    TraverseList(L->next);
}

// 打印单链表 L【非递归】
void TraverseList(LinkList L) {
    LNode *p = L->next;
    while (p) {
        printf("%d\n", p->data);
        p = p->next;
    }
}




// 计算 n 的阶乘【递归】
long fact(int n) {
    if (n == 0) return 1;
    return n * fact(n - 1); 
}

// 计算 n 的阶乘【非递归】
long fact(int n) {
    long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}


// 计算第 n 个斐波那契数
long fib(long n) {
    if(n==1 || n==2) return 1;                   //递归终止的条件
    
    return fib(n-1) + fib(n-2);        
    
}



int second(int a, int b) {
    int i = a + b;
    int j = a - b;
    return i + j;
}

int first(int m) {
    int a = m * m;
    int b = m * 4;
    int res = second(a, b);
    return res;
}

int main() {
    int m = 10;
    int n = first(m);

    printf("n = %d\n", n);
    return 1;
}