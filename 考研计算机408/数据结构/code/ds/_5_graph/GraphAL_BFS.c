#include "GraphAL.c"

#include "SqQueue.c"

// 用于记录对应的顶点是否被访问过
// visited[v] = true，表示顶点 v 被访问过
// visited[v] = false，表示顶点 v 未被访问过
bool *visited;

// 广度优先遍历邻接表表示的连通图
void BFS(ALGraph *G, int v) {
    // 声明并初始化一个队列
    SqQueue queue;
    InitQueue(&queue, G->vertexNum);

    // 访问并处理当前顶点 v
    printf("%s ", G->adjList[v].data);
    visited[v] = true;
    EnQueue(&queue, v);

    QElemType w;
    while (!QueueEmpty(&queue)) {
        // 拿到队首顶点
        DeQueue(&queue, &w);

        // 遍历邻接表的第 w 个边链表
        EdgeNode *p = G->adjList[w].firstEdge;
        while (p) {
            // 判断是否有未被访问的邻接点，如果有，则访问并处理邻接点 j
            int j = p->adjvex;
            if (!visited[j]) {
                printf("%s ", G->adjList[j].data);
                visited[j] = true;
                EnQueue(&queue, j);
            }
            p = p->nextEdge;
        }
    }
}

// BFS 遍历连通图
// 空间复杂度：O(n)
// 时间复杂度：O(n + e)
void BFS_AM(ALGraph *G, int v) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    BFS(G, v);

    free(visited);
}

// 遍历整个图（包括非连通图）
// 空间复杂度：O(n)
// 时间复杂度：O(n + e)
int TraverseAMGraph(ALGraph *G) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    int res = 0; // 连通分量的数量
    for (int v = 0; v < G->vertexNum; v++) {
        if (!visited[v]) {
            res++;
            BFS(G, v);
        }
    }

    free(visited);

    return res;
}

int main() {
    ALGraph G;
    
    // 5 个顶点
    int vertexNum = 5;
    char* vertices[5] = {"v1", "v2", "v3", "v4", "v5"};

    // 5 条边
    int edgeNum = 5;
    char* edges[5][2] = {
        {"v1", "v2"},
        {"v1", "v4"},
        {"v2", "v3"},
        {"v3", "v4"},
        {"v2", "v5"}
    };

    // 初始化
    InitGraphAL(&G, false, vertexNum, vertices, edgeNum, edges);

    BFS_AM(&G, 0);

    DestroyGraphAL(&G);
}