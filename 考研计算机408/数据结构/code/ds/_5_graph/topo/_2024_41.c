#include "../GraphAM.c"
#include "SqQueue.c"

#define MAXV 100

typedef struct {  					//图的类型定义
    int numVertices, numEdges;  		//图的顶点数和有向边数
    char VerticesList[MAXV];		//顶点表，MAXV为已定义常量
    int Edge[MAXV][MAXV];			//邻接矩阵
} MGraph;

int uniquely(MGraph G) {
    int n = G.numVertices; // 顶点数量
    // 计算每个顶点的入度
    int indegrees[n];
    for (int i = 0; i < n; i++) indegrees[i] = 0;
    for (int v = 0; v < n; v++) {
        for (int w = 0; w < n; w++) 
            if (G.Edge[v][w]) indegrees[w]++;
    }

    SqQueue queue;
    InitQueue(&queue, n);
    // 将入度为 0 的顶点入队
    for (int v = 0; v < n; v++) 
        if (indegrees[v] == 0) EnQueue(&queue, v);

    int idx = 0;
    int v;
    while (!QueueEmpty(&queue)) {
        // 如果入度为 0 的顶点超过 1 个，那么拓扑序列不唯一
        if (QueueLength(&queue) > 1) return 0;

        DeQueue(&queue, &v); // 出队入度为 0 的顶点
        idx++;

        for (int w = 0; w < n; w++) {
            if (G.Edge[v][w] != 0) { // 拿到邻接点 w
                indegrees[w]--;      // 将邻接点的入度减 1
                // 如果邻接点的入度为 0，则入队
                if (indegrees[w] == 0) EnQueue(&queue, w);
            }
        }
    }

    DestroyQueue(&queue);
    // 如果出队的次数等于顶点数，说明拓扑序列唯一，否则说明图有环，不存在拓扑序列
    return idx == n;
}

int main() {
    AMGraph G;
    
    // 5 个顶点
    int vertexNum = 12;
    char* vertices[12] = {"C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11", "C12"};

    // 5 条边
    int edgeNum = 16;
    char* edges[16][2] = {
        {"C1", "C2"},
        {"C1", "C3"},
        //{"C3", "C1"},
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