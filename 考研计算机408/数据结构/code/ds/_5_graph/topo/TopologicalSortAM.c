#include "../GraphAM.c"
#include "SqQueue.c"

// 邻接矩阵表示的有向图的拓扑排序
// 时间复杂度：O(n^2)
bool TopologicalSort(AMGraph *G, int *topo) {
    // 拓扑排序的对象必须是有向图
    if (!G->isDirected) {
        printf("error: graph not directed");
        return false;
    }

    int n = G->vertexNum;

    // 计算每个顶点的入度
    int indegrees[n];
    for (int i = 0; i < n; i++) indegrees[i] = 0;
    // 时间复杂度：O(n^2)
    for (int v = 0; v < n; v++) {
        // 遍历顶点 v 对应的列，求顶点 v 的入度
        for (int w = 0; w < n; w++) {
            if (G->adjMatrix[w][v]) indegrees[v]++;
        }
    }

    SqQueue queue;
    InitQueue(&queue, n);
    // 将入度为 0 的顶点入队
    for (int v = 0; v < n; v++) {
        if (indegrees[v] == 0) EnQueue(&queue, v);
    }

    QElemType v;
    int idx = 0;
    // 时间复杂度：O(n^2)
    while (!QueueEmpty(&queue)) {
        // 出队入度为 0 的顶点
        DeQueue(&queue, &v);

        // 放到拓扑排序的序列中
        topo[idx++] = v;

        // 处理当前顶点的每个邻接点
        for (int w = 0; w < n; w++) {
            if (G->adjMatrix[v][w] != 0) {
                // 将邻接点的入度减 1
                indegrees[w]--;
                // 如果邻接点的入度为 0，则入队
                if (indegrees[w] == 0) EnQueue(&queue, w);
            }
        }
    }

    DestroyQueue(&queue);
    // 如果 idx 等于 n 说明没有环，拓扑排序成功，否则说明有向图有环
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
        // {"C1", "C3"},
        {"C3", "C1"},
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
}