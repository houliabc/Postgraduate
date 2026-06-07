#include "GraphAM.c"

#include "SqQueue.c"

// 用于记录对应的顶点是否被访问过
// visited[v] = true，表示顶点 v 被访问过
// visited[v] = false，表示顶点 v 未被访问过
bool *visited;

// 广度优先遍历邻接矩阵表示的连通图
void BFS(AMGraph *G, int v) {
    // 声明并初始化一个队列
    SqQueue queue;
    InitQueue(&queue, G->vertexNum);

    // 访问并处理当前顶点 v
    printf("%s ", G->vertices[v]);
    visited[v] = true;
    EnQueue(&queue, v);

    QElemType w;
    while (!QueueEmpty(&queue)) {
        // 拿到队首顶点
        DeQueue(&queue, &w);

        // 遍历邻接矩阵的第 w 行
        for (int j = 0; j < G->vertexNum; j++) {
            // 判断是否有未被访问的邻接点，如果有，则访问并处理邻接点 j
            if (G->adjMatrix[w][j] != 0 && !visited[j]) {
                printf("%s ", G->vertices[j]);
                visited[j] = true;
                EnQueue(&queue, j);
            }
        }
    }
}

// BFS 遍历连通图
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
void BFS_AM(AMGraph *G, int v) {
    visited = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int i = 0; i < G->vertexNum; i++) visited[i] = false;

    BFS(G, v);

    free(visited);
}

// 遍历整个图（包括非连通图）
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
int TraverseAMGraph(AMGraph *G) {
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

// 求顶点 src 到顶点 dest 最短路径长度
int ShortestPath(AMGraph *G, int src, int dest) {
    // 声明并初始化一个队列
    SqQueue queue;
    InitQueue(&queue, G->vertexNum);

    // 访问并处理当前顶点 src
    visited[src] = true;
    EnQueue(&queue, src);

    int level = 0; // 层

    QElemType w;
    while (!QueueEmpty(&queue)) {
        level++;
        int sz = QueueLength(&queue);
        for (int i = 0; i < sz; i++) {
            // 拿到队首顶点
            DeQueue(&queue, &w);
            // 如果目标顶点在当前层，则返回最短路径长度
            if (w == dest) return level - 1;

            // 遍历邻接矩阵的第 w 行
            for (int j = 0; j < G->vertexNum; j++) {
                // 判断是否有未被访问的邻接点，如果有，则访问并处理邻接点 j
                if (G->adjMatrix[w][j] != 0 && !visited[j]) {
                    printf("%s ", G->vertices[j]);
                    visited[j] = true;
                    EnQueue(&queue, j);
                }
            }
        }
    }

    // src 到不了 dest
    return -1;
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

    BFS_AM(&G, 0);

    DestroyGraphAM(&G);
}