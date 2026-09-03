#include "../GraphAL.h"
#include "SqQueue.c"

// 邻接表表示的有向图的拓扑排序
// 时间复杂度：O(n + e)
bool TopologicalSort(ALGraph *G, int *topo) {
    // 拓扑排序的对象必须是有向图
    if (!G->isDirected) {
        printf("error: graph not directed");
        return false;
    }

    int n = G->vertexNum;

    // 计算每个顶点的入度
    int indegrees[n];
    for (int v = 0; v < n; v++) {
        indegrees[v] = 0;
    }
    // 时间复杂度：O(n + e)
    for (int v = 0; v < n; v++) {
        EdgeNode *p = G->adjList[v].firstEdge;
        while (p) {
            indegrees[p->adjvex]++;
            p = p->nextEdge;
        }
    }

    // 将入度为 0 的顶点入队
    SqQueue queue;
    InitQueue(&queue, n);
    for (int v = 0; v < n; v++) {
        if (indegrees[v] == 0) EnQueue(&queue, v);
    }

    QElemType v;
    int idx = 0;
    while (!QueueEmpty(&queue)) {
        // 出队入度为 0 的顶点
        DeQueue(&queue, &v);
        // 放到拓扑排序的序列中
        topo[idx++] = v;

        // 处理当前顶点的每个邻接点
        EdgeNode *p = G->adjList[v].firstEdge;
        while (p) {
            // 将邻接点的入度减 1
            indegrees[p->adjvex]--;
            // 如果邻接点的入度为 0，则入队
            if (indegrees[p->adjvex] == 0) EnQueue(&queue, p->adjvex);
            p = p->nextEdge;
        }
    }

    DestroyQueue(&queue);
    // 如果 idx 等于 n 说明没有环，拓扑排序成功，否则说明有向图有环
    return idx == n;
}