#include "../GraphAM.c"
#include "SqQueue.c"

int *topo;
int idx;
bool *visited;

// 深度优先遍历邻接矩阵表示的连通图
void DFS(AMGraph *G, int v) {
    // 打印先序序列
    // printf("%s ", G->vertices[v]);
    visited[v] = true;

    // 遍历访问当前顶点的所有邻接点
    for (int w = 0; w < G->vertexNum; w++) {
        if (G->adjMatrix[v][w] != 0 && !visited[w]) 
            DFS(G, w);
    }

    // 打印后序序列
    // printf("%s ", G->vertices[v]);

    // 逆后序
    topo[idx--] = v;
}

// 遍历图
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
void TopologySortDFS(AMGraph *G) {
    int n = G->vertexNum;
    // 创建一个顶点数量的数组，用于存储拓扑排序的序列
    topo = (int *) malloc (sizeof(int) * n);

    visited = (bool *) malloc (sizeof(bool) * n);
    for (int i = 0; i < n; i++) visited[i] = false;

    idx = n - 1;

    for (int v = 0; v < n; v++) {
        if (!visited[v]) {
            DFS(G, v);
        }
    }

    free(visited);
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

    TopologySortDFS(&G);

    printf("\n");

    for (int i = 0; i < G.vertexNum; i++) {
        printf("%s ", G.vertices[topo[i]]);
    }

    printf("\n");

    free(topo);

    DestroyGraphAM(&G);
}