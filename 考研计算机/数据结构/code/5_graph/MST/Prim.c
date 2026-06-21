#include "../NetworkAM.c"
#include <limits.h>

// // 邻接矩阵存储的图结构
// typedef struct {
//     VertexType *vertices;       // 顶点表
//     ElemType **adjMatrix;           // 邻接矩阵
//     int vertexNum;              // 图的顶点数
//     int edgeNum;                // 图的边数
//     bool isDirected;            // 表明是否为有向图，1为有向图
// } AMNetwork;  // Adjacency matrix：邻接矩阵

// 横切边——充当了并查集的集合作用——权值0表示同属于一个集合，或者说已经加入，无需再加入，所以是去找那些weight不为0的顶点
typedef struct {
   int  u;         // 集合 U 中的顶点
   int  weight;    // 权值
} CrossEdge;

// 查找权值最小的横切边，返回横切边在数组中的下标
// 时间复杂度：O(n)
int Min(CrossEdge crossEdges[], int vexnum) {
    // TODO: 遍历 crossEdges，找到 weight 不为 0 且最小的元素，返回其下标
    int k = -1, minWeight = INT_MAX; // 标记最小元素的下标和权值
    for (int i = 0; i < vexnum; i++) {
        // 更新最小
        if (crossEdges[i].weight != 0 && crossEdges[i].weight < minWeight) {
            k = i;
            minWeight = crossEdges[i].weight;
        }
    }
    return k;
}

// 无向网 G 以邻接矩阵形式存储
// 从顶点 u 出发构造 G 的最小生成树 T，输出 T 的各条边
// 时间复杂度：O(n^2)，与网的边数无关，因此适用于稠密网的最小生成树
void MiniSpanTree_Prim(AMNetwork *G, VertexType u) {
    // 获取初始化从u顶点出发的下标k
    int k = LocateVex(G, u);
    // 若找不到说明是，非连通图，没有最小生成树
    if (k == -1) {
        printf("not a MST");
        return;
    }
    
    // 初始化横切边数组——顶点和对应的权值
    int n = G->vertexNum;
    CrossEdge crossEdges[n];
    for (int j = 0; j < n; j++) {
        crossEdges[j].u = k;
        crossEdges[j].weight = G->adjMatrix[k][j];
    }
    // 把已加入集合的顶点的权值设置为0
    crossEdges[k].weight = 0;

    // 执行n-1次，找出n-1条最短的边
    for (int i = 0; i < n - 1; i++) {
        // 找到当前集合的最短横切边
        k = Min(crossEdges, n);  // 最短边的下标
        // 若找不到说明是，非连通图，没有最小生成树
        if (k == -1) {
            printf("not a MST");
            return;
        }

        // 若有，则做一些更新处理以及打印最短边
        VertexType u0 = G->vertices[crossEdges[k].u];
        VertexType v0 = G->vertices[k];
        printf("(%s, %s) weight: %d\n", u0, v0, crossEdges[k].weight);

        // !!!
        crossEdges[k].weight = 0; // 顶点 k 并入 U

        // 更新crossEdges——以顶点k出发，属于它的横切边，判断其是否距离更近
        for (int j = 0; j < n; j++) {
            if (crossEdges[j].weight != 0 && G->adjMatrix[k][j] < crossEdges[j].weight) {
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