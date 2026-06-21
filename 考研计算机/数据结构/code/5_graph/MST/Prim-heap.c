#include "../NetworkAM.c"
#include "MinHeap.c"
#include <limits.h>
#include <stdbool.h>

// typedef struct {
//     int v;
//     int w;
//     int weight;
// } Edge;

// 使用小顶堆优化的 Prim 算法（适用于稀疏图）
void MiniSpanTree_Prim(AMNetwork *G, VertexType u) {
    int start = LocateVex(G, u);
    if (start == -1) {
        printf("err: can not find vertex %s\n", u);
        return;
    }

    int n = G->vertexNum;
    // 标记顶点是否已加入集合 U
    bool *visited = (bool *)malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) visited[i] = false;

    // 初始化小顶堆（容量按边数两倍分配，避免溢出）
    MinHeap H;
    InitMinHeap(&H, G->edgeNum * 2);

    // 1. 将起点加入 U，并将其所有邻接边入堆
    visited[start] = true;
    for (int j = 0; j < n; j++) {
        if (G->adjMatrix[start][j] != INT_MAX) {
            Edge e;
            e.v = start;
            e.w = j;
            e.weight = G->adjMatrix[start][j];
            MinHeapInsert(&H, e);
        }
    }

    int edgeCount = 0; // 已选边数
    while (edgeCount < n - 1) {
        Edge e;
        // 2. 从堆中弹出权值最小的边
        if (!MinHeapDelMin(&H, &e)) {
            // 堆空，图不连通
            break;
        }

        // 3. 如果终点已在 U 中，说明是过时边，跳过
        if (visited[e.w]) continue;

        // 4. 选中该边，将终点 w 加入 U
        visited[e.w] = true;
        edgeCount++;

        // 输出该边
        printf("(%s, %s) weight: %d\n", G->vertices[e.v], G->vertices[e.w], e.weight);

        // 5. 将新顶点 e.w 的所有邻接边（指向未访问顶点的）入堆
        for (int j = 0; j < n; j++) {
            if (!visited[j] && G->adjMatrix[e.w][j] != INT_MAX) {
                Edge ne;
                ne.v = e.w;
                ne.w = j;
                ne.weight = G->adjMatrix[e.w][j];
                MinHeapInsert(&H, ne);
            }
        }
    }

    if (edgeCount < n - 1) {
        printf("err: disconnected graph, can not generate mst\n");
    }

    free(visited);
    DestroyMinHeap(&H);
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

    MiniSpanTree_Prim(&G, "v0");

    DestroyNetworkAM(&G);
    return 0;
}