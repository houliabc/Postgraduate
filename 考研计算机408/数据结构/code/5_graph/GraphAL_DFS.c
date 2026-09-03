#include "GraphAL.c"

// 邻接表的深度优先遍历DFS实现

// 标记数组，用于表示哪些顶点被访问过，就无需再度访问了
bool *visited;

// 深度优先遍历DFS
void DFS(ALGraph *G, int v) {
    // 与树不同，不在首部放入结束条件
    // 只要能进入DFS递归里的，都是符合条件，没有遍历过的，那就直接遍历输出它
    printf("%s-", G->adjList[v].data);
    visited[v] = true;

    // 接着遍历其未被访问过的邻接点——按照领接表的方式，遍历其连着的所有的边
    EdgeNode *p = G->adjList[v].firstEdge;
    while (p) {
        // 获取顶点p的下标
        int w = p->adjvex;
        // 若未被访问过，才去DFS
        if (!visited[w])
            DFS(G, w);
        p = p->nextEdge;
    }
}

// 深度优先遍历连通图（不适合非连通图）
void DFS_AM(ALGraph *G, int v) {
    // 初始化标记数组
    visited = (bool*)malloc(sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) {
        visited[i] = false;
    }
    //直接开始深度遍历
    DFS(G, v);

    // 释放空间
    free(visited);

    printf("\n");
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
    //DFS每个顶点
    for (int i = 0; i < G->vertexNum; i++) {
        if (!visited[i]) {
            res++;
            DFS(G, i);
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
    InitGraphAL(&G, true, vertexNum, vertices, edgeNum, edges);

    DFS_AM(&G, 0);

    TraverseALGraph(&G);

    printf("\n");

    DestroyGraphAL(&G);
}
