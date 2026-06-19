#include "GraphAL.c"
#include "SqQueue.c"

// 邻接表的广度优先遍历BFS实现

// 标记数组，用于表示哪些顶点被访问过，就无需再度访问了
bool *visited;

// 广度优先遍历BFS————迭代的思想
void BFS(ALGraph *G, int v) {
    // 声明和初始化队列
    SqQueue queue;
    InitQueue(&queue, G->vertexNum);

    // 只要能进入BFS递归里的，都是符合条件，没有遍历过的，那就直接遍历输出它，同时加入到队列当中
    printf("%s-", G->adjList[v].data);
    visited[v] = true;
    EnQueue(&queue, v);

    ElemType e;
    // 若队列非空则一直遍历下去
    while (!QueueEmpty(&queue)) {
        // 出队
        DeQueue(&queue, &e);
        
        EdgeNode *p = G->adjList[e].firstEdge;
        // 访问这个顶点的所有邻接边
        while (p) {
            int w = p->adjvex;
            if (!visited[w]) {
                printf("%s-", G->adjList[w].data);
                visited[w] = true;
                EnQueue(&queue, w);
            }
            p = p->nextEdge;
        }
    }
}

// 广度优先遍历连通图（不适合非连通图）
void BFS_AL(ALGraph *G, int v) {
    // 初始化标记数组
    visited = (bool*)malloc(sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) {
        visited[i] = false;
    }
    //直接开始广度遍历
    BFS(G, v);

    // 释放空间
    free(visited);
}

// 遍历整个图（包括非连通图）——并返回连通分量数
int TraverseALGraph(ALGraph *G) {
    // 初始化标记数组
    visited = (bool*)malloc(sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) {
        visited[i] = false;
    }

    // 统计连通分量
    int res = 0;
    //BFS每个顶点
    for (int i = 0; i < G->vertexNum; i++) {
        if (!visited[i]) {
            res++;
            BFS(G, i);
        }
    }

    // 释放空间
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

    BFS_AL(&G, 0);

    printf("\n");

    DestroyGraphAL(&G);
}
