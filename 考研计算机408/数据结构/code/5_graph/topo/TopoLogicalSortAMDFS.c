#include "../GraphAM.c"
#include "SqQueue.c"
// 邻接矩阵的深度优先遍历DFS实现

// 标记数组，用于表示哪些顶点被访问过，就无需再度访问了
bool *visited;
// 拓扑排序
int *topo;
int idx;

// 深度优先遍历DFS
void DFS(AMGraph *G, int v) {
    // 与树不同，不在首部放入结束条件
    // 只要能进入DFS递归里的，都是符合条件，没有遍历过的，那就直接遍历输出它
    // printf("%s-", G->vertices[v]);
    visited[v] = true;

    // 接着遍历其未被访问过的邻接点
    for (int i = 0; i < G->vertexNum; i++) {
        if (G->adjMatrix[v][i] == 1 && !visited[i])
            DFS(G, i);
    }

    // 后序打印结点————就是拓扑排序的结果
    // printf("%s ", G->vertices[v]);
    // 逆后序存放dfs结果就是拓扑排序
    topo[idx--] = v;
}

// 深度优先遍历连通图（不适合非连通图）
void DFS_AM(AMGraph *G, int v) {
    // 初始化标记数组
    visited = (bool*)malloc(sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) {
        visited[i] = false;
    }
    //直接开始深度遍历
    DFS(G, v);

    // 释放空间
    free(visited);
}

// 遍历整个图（包括非连通图）——并返回连通分量数
int TopologySortDFS(AMGraph *G) {
    int n = G->vertexNum;
    // 初始化标记数组
    visited = (bool*)malloc(sizeof(bool) * n);
    topo = (int*)malloc(sizeof(int) * n);
    idx = n - 1;
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // 统计连通分量
    int res = 0;
    //DFS每个顶点
    for (int i = 0; i < n; i++) {
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

    for (int i = 0; i < G.vertexNum; i++) {
        printf("%s ", G.vertices[topo[i]]);
    }

    printf("\n");

    free(topo);

    DestroyGraphAM(&G);
}