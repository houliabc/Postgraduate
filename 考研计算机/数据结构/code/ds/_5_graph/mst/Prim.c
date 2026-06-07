#include "../NetworkAM.c"

// 横切边
typedef struct {
   int  u;         // 集合 U 中的顶点
   int  weight;    // 权值
} CrossEdge;

// 查找权值最小的横切边，返回横切边在数组中的下标
// 时间复杂度：O(n)
int Min(CrossEdge crossEdges[], int vexnum) {
    int minWeight = INT_MAX;  // 最小权值
    int k = -1;
    for (int i = 0; i < vexnum; i++) {
        if (crossEdges[i].weight != 0 &&    // 过滤掉无效横切边
                crossEdges[i].weight < minWeight) { // 如果横切边权值小于最小权值
            minWeight = crossEdges[i].weight;
            k = i;
        }
    }
    return k;
}

// 无向网 G 以邻接矩阵形式存储
// 从顶点 u 出发构造 G 的最小生成树 T，输出 T 的各条边
// 时间复杂度：O(n^2)，与网的边数无关，因此适用于稠密网的最小生成树
void MiniSpanTree_Prim(AMNetwork *G, VertexType u) {
    int k = LocateVex(G, u);
    if (k == -1) {
        printf("err: can not find vertex %s\n", u);
        return;
    }

    int n = G->vertexNum; // 顶点数量
    // 横切边数组，数组的下标表示集合 V- U 中的顶点
    CrossEdge crossEdges[n];

    // 初始化 crossEdges
    for (int j = 0; j < n; j++) {
        crossEdges[j].u = k;    
        crossEdges[j].weight = G->adjMatrix[k][j];
    }
    crossEdges[k].weight = 0; // 将顶点 u 放到集合 U = {u}

    // 查找 n - 1 条最小生成树的边
    // 时间复杂度：O(n)
    for (int i = 1; i < n; i++) { 
        // 拿到权值最小的横切边
        // 时间复杂度：O(n)
        k = Min(crossEdges, n);

        // 如果没有权值最小的横切边，说明图不连通，无法生成最小生成树
        if (k == -1) {
            printf("err: disconnected graph, can not generate mst\n");
            return;
        }

        // 打印这条属于最小生成树的横切边
        VertexType u0 = G->vertices[crossEdges[k].u]; // 集合 U 中的顶点
        VertexType v0 = G->vertices[k];               // 集合 V - U 中的顶点
        printf("(%s, %s) weight: %d\n", u0, v0, crossEdges[k].weight);

        crossEdges[k].weight = 0; // 顶点 k 并入 U

        // 更新 crossEdges
        // 时间复杂度：O(n)
        for (int j = 0; j < n; j++) {
            if (crossEdges[j].weight != 0 &&                 // 顶点 j 不属于集合 U
                    G->adjMatrix[k][j] != INT_MAX &&         // 顶点 j 到顶点 k 之间有边
                    G->adjMatrix[k][j] < crossEdges[j].weight) { // k-j 横切边的权值比之前的顶点 j 的横切边还要小
                crossEdges[j].u = k;
                crossEdges[j].weight = G->adjMatrix[k][j];
            }
        }
    }
}

int main() {
    AMNetwork G;
    
    // 6 个顶点
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