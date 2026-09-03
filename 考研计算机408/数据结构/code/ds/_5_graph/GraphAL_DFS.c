#include "GraphAL.c"

// 用于记录对应的顶点是否被访问过
// visited[v] = true，表示顶点 v 被访问过
// visited[v] = false，表示顶点 v 未被访问过
bool *visited;

// 深度优先遍历邻接表表示的连通图
void DFS(ALGraph *G, int v) {

    // 遍历访问当前顶点 v
    printf("%s ", G->adjList[v].data);

    visited[v] = true;

    // 遍历访问当前顶点的所有邻接点
    EdgeNode *p = G->adjList[v].firstEdge;
    while (p) {
        int w = p->adjvex;
        if (!visited[w]) DFS(G, w);
        p = p->nextEdge;
    }
}

// 遍历图
// 空间复杂度：O(n)
// 时间复杂度：O(n + e)，n 是顶点数量，e 是边的数量
void DFS_AM(ALGraph *G, int v) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    DFS(G, v);

    free(visited);
}

// 遍历整个图（包括非连通图）
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
int TraverseAMGraph(ALGraph *G) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    int res = 0;    // 连通分量的数量
    for (int v = 0; v < G->vertexNum; v++) {
        if (!visited[v]) {
            res++;
            DFS(G, v);
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

    DFS_AM(&G, 0);

    printf("\n");

    DestroyGraphAL(&G);
}