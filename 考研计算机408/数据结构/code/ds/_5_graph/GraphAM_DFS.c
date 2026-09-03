#include "GraphAM.c"

// 用于记录对应的顶点是否被访问过
// visited[v] = true，表示顶点 v 被访问过
// visited[v] = false，表示顶点 v 未被访问过
bool *visited;

// 深度优先遍历邻接矩阵表示的连通图
void DFS(AMGraph *G, int v) {

    // 遍历访问当前顶点 v
    printf("%s ", G->vertices[v]);

    visited[v] = true;

    // 遍历访问当前顶点的所有邻接点
    for (int w = 0; w < G->vertexNum; w++) {
        if (G->adjMatrix[v][w] != 0 && !visited[w]) 
            DFS(G, w);
    }
}

// 遍历图
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
void DFS_AM(AMGraph *G, int v) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    DFS(G, v);

    free(visited);
}

// 遍历整个图（包括非连通图）
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
int TraverseAMGraph(AMGraph *G) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    int res = 0;
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
    AMGraph G;
    
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
    InitGraphAM(&G, true, vertexNum, vertices, edgeNum, edges);

    DFS_AM(&G, 0);

    printf("\n");

    DestroyGraphAM(&G);
}