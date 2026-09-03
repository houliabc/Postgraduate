#include "../NetworkAM.c"
#include "MinHeap.c"
#include "../union&find_set/quick-union+.c"


// 无向网 G 以邻接矩阵形式存储
// 构造 G 的最小生成树 T，输出 T 的各条边    
// 空间复杂度：O(n + e)
// 时间复杂度：O(eloge)
void MiniSpanTree_Kruskal(AMNetwork *G) {
    int n = G->vertexNum;
    // 用小顶堆来选择最小的边
    MinHeap H;
    // 初始化n个边的小顶堆
    InitMinHeap(&H, G->edgeNum);
    for (int i = 0; i < n; i++) {
        // 遍历邻接矩阵上三角（列数始终大于行数，不包括主对角元素（否则就是环了））
        for (int j = i + 1; j < n; j++) {
            // 有边才加入到小顶堆中
            if (G->adjMatrix[i][j] != INT_MAX) {
                // 将每条边（v, w, weight）插入堆
                HElemType e;
                e.weight = G->adjMatrix[i][j];
                e.v = i;
                e.w = j;
                MinHeapInsert(&H, e);
            }
        }
    }

    //       3. 初始化并查集（n 个顶点）
    UF uf;
    InitUF(&uf, n);  // 表示n个联通分量的集合

    //       4. 循环：从堆中取出最小边，若顶点不连通则加入生成树（打印），合并分量
    HElemType e;
    int edgeNum = 0;
    // 取出最小边————找n-1条边，循环次数最少是n-1次
    while (MinHeapDelMin(&H, &e) && edgeNum < n - 1) {
        // 若边的两个顶点是同一集合，则跳过
        if (connectedUF(&uf, e.v, e.w))
            continue;
        // 否则就加入该边，并边数加一
        unionUF(&uf, e.v, e.w);
        edgeNum++;

        // 加入到最小生成树中，打印边
        printf("(%s, %s) weight: %d\n", G->vertices[e.v], G->vertices[e.w], e.weight);
    }
    //       5. 若生成树边数不足 n-1，则图不连通
    if (edgeNum < n - 1) {
        printf("not a MST");
        return;
    }
    //       6. 释放堆和并查集
    DestroyMinHeap(&H);
    DestroyUF(&uf);

}

int main() {
    AMNetwork G;
    
    // 7 个顶点
    int vertexNum = 7;
    char* vertices[7] = {"v0", "v1", "v2", "v3", "v4", "v5", "v6"};

    // 12 条边
    int edgeNum = 12;
    char* edges[12][3] = {
        {"v0", "v1", "2"},
        {"v0", "v3", "7"},
        {"v0", "v5", "2"},
        {"v1", "v2", "1"},
        {"v1", "v3", "4"},
        {"v1", "v4", "3"},
        {"v1", "v5", "5"},
        {"v2", "v4", "4"},
        {"v2", "v5", "4"},
        {"v3", "v4", "1"},
        {"v3", "v6", "5"},
        {"v4", "v6", "7"}
    };

    // 创建一个无向网
    InitNetworkAM(&G, false, vertexNum, vertices, edgeNum, edges);

    PrintNetworkAM(&G);

    MiniSpanTree_Kruskal(&G);

    DestroyNetworkAM(&G);
    return 0;
}