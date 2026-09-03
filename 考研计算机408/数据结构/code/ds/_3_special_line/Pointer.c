#include <stdio.h>


int main() {
    int x = 10;

    int *p = &x;
    printf("%p\n", p);

    p--;
    printf("after sub 1: %p\n", p);


    double d = 10.0;

    double *q = &d;
    printf("%p\n", q);

    q--;
    printf("after sub 1: %p\n", q);

    return 0;
}