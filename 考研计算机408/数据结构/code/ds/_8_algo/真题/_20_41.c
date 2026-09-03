
#include <stdlib.h>
#include <stdbool.h>

// 方法一：暴力解法
int minDistance(int s1[], int n1, int s2[], int n2, int s3[], int n3) {
    int Dmin = INT_MAX;
    int a, b, c;

    // 枚举所有的三元组 (a, b, c)
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            for (int k = 0; k < n3; k++) {
                a = s1[i];
                b = s2[j];
                c = s3[k];
                // 计算三元组的距离
                int d = abs(a - b) + abs(b - c) + abs(c - a);
                // 如果三原则距离更小，则更新为更小的距离
                if (d < Dmin) Dmin = d;
            }
        }
    }

    // 返回最小距离
    return Dmin;
}

// 判断 a 是否是最小值，如果是则返回 true
bool isMin(int a, int b, int c) {
    return a <= b && a <= c;
}

// 方法二：缩小查找空间
int minDistance(int s1[], int n1, int s2[], int n2, int s3[], int n3) {
    int Dmin = INT_MAX;
    int a, b, c;

    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2 && k < n3) {
        a = s1[i];
        b = s2[j];
        c = s3[k];
        // 计算三元组的距离
        int d = abs(a - b) + abs(b - c) + abs(c - a);
        if (d < Dmin) Dmin = d;

        // 将最小值对应的下标往前移动 1 位
        if (isMin(a, b, c)) i++;
        else if (isMin(b, a, c)) j++;
        else k++;
    }

    return Dmin;
}

