
#include "HuffmanMinHeap.c"

// 定义哈夫曼树结点结构体
typedef struct HuffmanNode {
    int weight;  // 结点权值
    int left;    // 左孩子下标
    int right;   // 右孩子下标
} HuffmanNode, *HuffmanTree;

// 创建哈夫曼树
// ht：存储哈夫曼树的表，是一个元素类型为 HuffmanNode 的数组
// w: n 个结点的初始权值
void CreateHuffmanTree(HuffmanNode *ht, int *w, int n) {
    // 初始化小顶堆
    MinHeap H;
    InitMinHeap(&H, n);

    // 将前n个叶子节点加入堆中，并维护好初始关系
    for (int i = 1; i <= n; i++) {  // 下标从1开始
        // 初始化哈夫曼树
        ht[i].weight = w[i - 1];
        ht[i].left = 0;
        ht[i].right = 0;

        // 插入小顶堆
        ElemType e;
        e.weight = w[i - 1];
        e.i = i;
        MinHeapInsert(&H, e);
    }

    // 完成剩余的哈夫曼结点
    // 哈夫曼树总结点个数 m = 2 * n0 - 1
    int m = 2 * n - 1;
    // for (int i = n + 1; i <= m; i++) {  // 下标从1开始
    //     ht[i].weight = 0;
    //     ht[i].left = 0;
    //     ht[i].right = 0;
    // }

    for (int i = n + 1; i <= m; i++) {  // 下标从1开始
        // 从小顶堆取出两个最小元素，插入哈夫曼树中（同时也加入小顶堆中）
        ElemType e1, e2, e;
        MinHeapDelMin(&H, &e1);
        MinHeapDelMin(&H, &e2);

        ht[i].weight = e1.weight + e2.weight;
        ht[i].left = e1.i;
        ht[i].right = e2.i;

        e.weight = ht[i].weight;
        e.i = i;
        MinHeapInsert(&H, e);
    }
}

// 按照先序遍历生成哈夫曼编码：i表示当前的下标，k表示前缀长度，arr为前缀数组
void generateCodes(HuffmanTree ht, int i, int k, int arr[]) {
    // 若当前为根结点，进行输出
    if (!ht[i].left && !ht[i].right) {
        printf("node%d：",i);
        for (int j = 0; j < k; j++) {
            printf("%d", arr[j]);
        }
        printf("\n");
        return;
    }
    
    // 左
    if (ht[i].left) {
        // 注意这里k不用++
        arr[k] = 0;
        // 而是在传参进去是++，这样可以做到回溯
        generateCodes(ht, ht[i].left, k + 1, arr);
    }
    // 右
    if (ht[i].right) {
        arr[k] = 1;
        generateCodes(ht, ht[i].right, k + 1, arr);
    }
}