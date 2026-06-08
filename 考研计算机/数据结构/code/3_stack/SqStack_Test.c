// #include "SqStack.c"
#include "SqStackArr.c"

int main() {
    SqStack s;
    InitStack(&s);

    Push(&s, 10);
    Push(&s, 99);
    Push(&s, 23);
    Push(&s, 33);

    printf("stack size is %d\n", StackLength(&s));
    StackTraverse(&s);

    ElemType x;
    Pop(&s, &x);
    printf("pop element is %d\n", x);
    printf("stack size is %d\n", StackLength(&s));
    StackTraverse(&s);

    ClearStack(&s);
    StackTraverse(&s);

    DestroyStack(&s);
    return 0;
}