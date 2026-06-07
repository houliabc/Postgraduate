#include "../NetworkAM.c"
#include "MinHeap.c"

#include "../uf/UF_3.c"


// 无向网 G 以邻接矩阵形式存储
// 构造 G 的最小生成树 T，输出 T 的各条边    
// 空间复杂度：O(n + e)
// 时间复杂度：O(eloge)
void MiniSpanTree_Kruskal(AMNetwork *G) {

    int  n = G->vertexNum; // 顶点数量
    
    // 初始化一个小根堆
    MinHeap H;
    InitMinHeap(&H, G->edgeNum);
    // 时间复杂度：O(n^2 * loge)
    // 如果只是遍历边的话，这里可以优化成 O(eloge)
    for (int v = 0; v < n; v++) {
        for (int w = v + 1; w < n; w++) { // 遍历邻接矩阵的上三角
            if (G->adjMatrix[v][w] != INT_MAX) {
                Edge edge;
                edge.v = v;
                edge.w = w;
                edge.weight = G->adjMatrix[v][w];
                MinHeapInsert(&H, edge);
            }
        }
    }

    // 初始化一个并查集
    UF uf;
    InitUF(&uf, n);

    int minEdgeNum = 0;
    Edge minEdge;
    // 如果可以的话，每次拿到最小权值边
    // 因为是连通图，所以边的数量 e 至少是 n - 1
    // 假设边的数量是 e，那么这个循环最多循环 e 次
    // 每次循环删除并拿到堆顶元素的时间复杂度 loge
    // 时间复杂度：O(eloge)
    while (MinHeapDelMin(&H, &minEdge) && minEdgeNum < n - 1) {
        int v = minEdge.v;
        int w = minEdge.w;

        // 判断顶点 v 和顶点 w 是否连通，如果连通，则不加入最小生成树
        // logn <= loge
        if (connectedUF(&uf, v, w)) continue;

        // 合并分量
        // logn <= loge
        unionUF(&uf, v, w);

        minEdgeNum++;
        // 加入到最小生成树中，打印边
        printf("(%s, %s) weight: %d\n", G->vertices[v], G->vertices[w], minEdge.weight);
    }

    // 如果最小边的数量小于 n - 1，说明图不连通，不能生成最小生成树
    if (minEdgeNum < n - 1) {
        printf("err: disconnected graph, can not generate mst\n");
    }

    DestoryMinHeap(&H);
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