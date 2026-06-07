#include <stdio.h>

#include "../SqStack.c"


long fact(int n) {
    // 1：设置一个工作栈存放递归工作记录（包括实参、返回地址及局部变量等）​
    SqStack s;
    InitStack(&s);

    // 2：当不满足递归结束条件时，逐层递归，将实参、返回地址及局部变量入栈
    for (int i = n; i > 0; i--) {
        Push(&s, i);
    }
 
    // 3：递归结束条件满足，将到达递归出口的给定常数作为当前的函数值
    long res = 1;

    // 4：返回处理：在栈不空的情况下，反复退出栈顶记录，根据记录中的返回地址进行题意规定的操作
    SElemtype e;
    while (Pop(&s, &e)) {
        res *= e;
    }

    DestroyStack(&s);
    
    return res;
}

// 并不是所有的将递归函数改写成非递归函数，都要用到栈


int main() {
    int res = fact(5);
    printf("res is: %d\n", res);

    return 0;
}    