#include "../GraphAM.c"
#include "SqQueue.c"

// 邻接矩阵表示的有向图的拓扑排序
// 时间复杂度：O(n^2)
bool TopologicalSort(AMGraph *G, int *topo) {
    // TODO: 实现拓扑排序算法
    // 1. 检查是否为有向图，若不是则返回 false
    if (!G->isDirected) return false;
    // 2. 计算每个顶点的入度（遍历邻接矩阵的列）
    int n = G->vertexNum;
    int inDegree[n];
    for (int i = 0; i < n; i++) inDegree[i] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G->adjMatrix[j][i])
                inDegree[i]++;
        }
    }
    // 3. 初始化队列，将入度为0的顶点入队
    SqQueue q;
    InitQueue(&q, n);
    for (int i = 0; i < n; i++) {
        // 将入度为0的顶点下标i入队
        if (inDegree[i] == 0)
            EnQueue(&q, i);
    }
    // 4. 循环出队，将顶点加入拓扑序列，并更新其邻接点的入度，入度变为0时入队
    QElemType v;
    int idx = 0;
    while (!QueueEmpty(&q)) {
        DeQueue(&q, &v);

        // 将拓扑序列的一个顶点加入进来
        topo[idx++] = v;

        for (int i = 0; i < n; i++) {
            // 表明相邻边，邻接顶点的入度要减一
            if (G->adjMatrix[v][i] > 0) {
                inDegree[i]--;
                // 若入度为0就入队
                if (inDegree[i] == 0)
                    EnQueue(&q, i);
            }
        }
    }
    // 5. 返回是否所有顶点都加入了拓扑序列（无环）
    DestroyQueue(&q);
    return idx == n;
}

int main() {
    AMGraph G;
    
    // 12 个顶点
    int vertexNum = 12;
    char* vertices[12] = {"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11", "C12"};

    // 16 条边
    int edgeNum = 16;
    char* edges[16][2] = {
        {"C1", "C2"},
        {"C1", "C3"}, 
        // {"C3", "C1"},   // 构造有环
        {"C1", "C4"},
        {"C1", "C12"},
        {"C2", "C3"},
        {"C3", "C5"},
        {"C3", "C7"},
        {"C3", "C8"},
        {"C4", "C5"},
        {"C5", "C7"},
        {"C9", "C12"},
        {"C9", "C10"},
        {"C9", "C11"},
        {"C10", "C12"},
        {"C11", "C6"},
        {"C6", "C8"}
    };

    // 初始化
    InitGraphAM(&G, true, vertexNum, vertices, edgeNum, edges);

    int n = G.vertexNum;
    // 创建一个顶点数量的数组，用于存储拓扑排序的序列
    int topo[n];
    
    if (TopologicalSort(&G, topo)) {
        printf("TopologySort Seq: ");
        for (int i = 0; i < n; i++) {
            printf("%s ", G.vertices[topo[i]]);
        }
    } else {
        printf("ERROR: graph has cycle");
    }
    
    DestroyGraphAM(&G);
    return 0;
}