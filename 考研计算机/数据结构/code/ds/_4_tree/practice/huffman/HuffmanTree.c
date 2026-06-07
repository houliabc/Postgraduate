
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
    MinHeap H;
    InitMinHeap(&H, n);

    // 初始化阶段
    for (int i = 1; i <= n; i++) {  // 初始化前 n 个节点
        ht[i].weight = w[i - 1];
        ht[i].left = 0;
        ht[i].right = 0;

        // 插入小顶堆中
        HElemType e;
        e.weight = w[i - 1];
        e.i = i;
        MinHeapInsert(&H, e);
    }

    int m = 2 * n - 1;  // 哈夫曼树的节点总数
    for (int i = n + 1; i <= m; i++) {  // 初始化后 m - n 个节点
        ht[i].weight = 0;
        ht[i].left = 0;
        ht[i].right = 0;
    }

    HElemType e;
    for (int i = n + 1; i <= m; i++) {  // 构建哈夫曼树
        // 拿到并删除权值最小的两个结点
        MinHeapDelMin(&H, &e);
        int s1 = e.i;

        MinHeapDelMin(&H, &e);
        int s2 = e.i;

        ht[i].left = s1;
        ht[i].right = s2;
        ht[i].weight = ht[s1].weight + ht[s2].weight;

        // 将新结点插入小顶堆中
        HElemType e1;
        e1.weight = ht[i].weight;
        e1.i = i;
        MinHeapInsert(&H, e1);
    }
}

// 生成哈夫曼编码
void generateCodes(HuffmanTree ht, int i, int k, int arr[]) {
    // 如果当前结点是叶子结点
    if (!ht[i].left && !ht[i].right) {
        // 打印结点下标
        printf("node %d: ", i);
        // 打印结点相应的哈夫曼编码
        for (int j = 0; j < k; j++) {
            printf("%d", arr[j]);
        }
        printf("\n");
        return;
    }

    if (ht[i].left) {
        arr[k] = 0;
        generateCodes(ht, ht[i].left, k + 1, arr);
    }
    
    if (ht[i].right) {
        arr[k] = 1;
        generateCodes(ht, ht[i].right, k + 1, arr);
    }
}