#include <stdio.h>
#include <stdlib.h>

#include "HuffmanTree.c"

// 打印哈夫曼树节点信息
void printHuffmanTree(HuffmanNode *ht, int m) {
    printf("index\tweight\tleft\tright\n");
    for (int i = 1; i <= m; i++) {
        printf("%d\t%d\t%d\t%d\n", i, ht[i].weight, ht[i].left, ht[i].right);
    }
}

int main() {
    int w[] = {5, 29, 7, 8, 14, 23, 3, 11};  // 权值数组
    int n = sizeof(w) / sizeof(w[0]);  // 叶子节点个数
    int m = 2 * n - 1;  // 哈夫曼树的节点总数

    HuffmanNode *ht = (HuffmanNode *)malloc((m + 1) * sizeof(HuffmanNode));

    CreateHuffmanTree(ht, w, n);

    printHuffmanTree(ht, m);

    int arr[10];
    generateCodes(ht, m, 0, arr);

    free(ht);
    return 0;
}