#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 计算两个数中的最大值
int max(int a, int b) {
    return a > b ? a : b;
}

// 对数组按照指定的位进行计数排序————用计数排序作为底层实现的基数排序
void CountSort(int data[], int n, int exp) {
    int i;
    int output[n]; // 输出数组
    int count[10] = {0}; // 计数数组，因为数字只有0...9十个数字

    // 统计每个位上数字出现的次数
    for (i = 0; i < n; i++) {
        // 个位数： (234 / 1) % 10 = 4
        // 十位数： (234 / 10) % 10 = 3
        // 百位数： (234 / 100) % 10 = 2
        int digit = (data[i] / exp) % 10;
        count[digit]++;
    }

    // 计算累积计数
    for (i = 1; i < 10; i++) count[i] += count[i - 1];

    // 构建输出数组（从后往前遍历以保持稳定性）
    for (i = n - 1; i >= 0; i--) {
        int digit = (data[i] / exp) % 10;
        int k = count[digit] - 1;
        output[k] = data[i];
        count[digit]--;
    }

    // 将排序后的结果复制回原数组
    for (i = 0; i < n; i++) {
        data[i] = output[i];
    }
}

// 基数排序主函数
// 时间复杂度：O(kn)
void RadixSort(int data[], int n, int k) {
    if (data == NULL || n <= 1) return;

    // 对数组按照每个元素的每位进行计数排序
    int exp = 1;
    for (int i = 1; i <= k; i++) {
        CountSort(data, n, exp);
        exp *= 10;
    }
}

// 打印数组元素
void printArray(int data[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int data[] = {4512, 4231, 31923, 2165, 1141};
    int n = sizeof(data) / sizeof(data[0]);

    printf("原始数组: ");
    printArray(data, n);

    RadixSort(data, n, 5);

    printf("排序后数组: ");
    printArray(data, n);

    return 0;
}
