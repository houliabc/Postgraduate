#include "LinkStack.c"

int main() {
    // s是指向栈顶的指针
    LinkStack s;
    InitStack(&s);

    Push(&s, 10);
    Push(&s, 99);
    Push(&s, 23);
    Push(&s, 33);

    printf("stack size is %d\n", StackLength(s));
    StackTraverse(s);

    Elemtype x;
    Pop(&s, &x);
    printf("pop element is %d\n", x);

    printf("stack size is %d\n", StackLength(s));
    StackTraverse(s);

    ClearStack(&s);
    StackTraverse(s);

    DestroyStack(s);

    return 0;
}