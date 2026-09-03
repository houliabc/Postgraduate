#include "../SqStack.c"

char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E'};

// 十进制数转成十六进制数
// 空间复杂度：O(logn)
// 时间复杂度：O(logn)
void conversion(int n) {
    SqStack s;
    InitStack(&s);

    while (n) {
        Push(&s, n % 16);   // 将余数入栈
        n = n / 16;         // 得到商，做下一轮的求余
    }

    SElemtype e;
    while (Pop(&s, &e)) {
        // 打印对应的十六进制字符
        printf("%c", hex[e]);
    }

    printf("H\n");
    DestroyStack(&s);
}

int main() {
    conversion(245685179);
    return 0;
}
