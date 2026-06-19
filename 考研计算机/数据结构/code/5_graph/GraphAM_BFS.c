#include "GraphAM.c"
#include "SqQueue.c"

// 邻接矩阵的广度优先遍历BFS实现

// 标记数组，用于表示哪些顶点被访问过，就无需再度访问了
bool *visited;

// 广度优先遍历BFS————迭代的思想
void BFS(AMGraph *G, int v) {
    // 声明和初始化队列
    SqQueue queue;
    InitQueue(&queue, G->vertexNum);

    // 只要能进入BFS递归里的，都是符合条件，没有遍历过的，那就直接遍历输出它，同时加入到队列当中
    printf("%s-", G->vertices[v]);
    visited[v] = true;
    EnQueue(&queue, v);

    ElemType e;
    // 若队列非空则一直遍历下去
    while (!QueueEmpty(&queue)) {
        // 出队
        DeQueue(&queue, &e);
        
        // 遍历拿出来的这个顶点的邻接边
        for (int j = 0; j < G->vertexNum; j++) {
            // 若有边，且未被访问过
            if (G->adjMatrix[e][j] && !visited[j]) {
                printf("%s-", G->vertices[j]);
                visited[j] = true;
                EnQueue(&queue, j);
            }
        }
    }
}

// 广度优先遍历连通图（不适合非连通图）
void BFS_AM(AMGraph *G, int v) {
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
int TraverseAMGraph(AMGraph *G) {
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

// BFS 求无权图顶点间（src->dest）的最短路径
int ShortestPath(AMGraph *G, int src, int dest) {
    // 声明和初始化队列
    SqQueue queue;
    InitQueue(&queue, G->vertexNum);

    // 只要能进入BFS递归里的，都是符合条件，没有遍历过的，那就直接遍历输出它，同时加入到队列当中
    visited[src] = true;
    EnQueue(&queue, src);

    ElemType e;
    int pathLen = 0;
    // 若队列非空则一直遍历下去
    while (!QueueEmpty(&queue)) {
        pathLen++;
        // 像树的层序遍历一般的遍历每一层
        for (int i = 0; i < QueueLength(&queue); i++) {
            // 出队
            DeQueue(&queue, &e);
            // 找到目标结点——目标结点在当前层
            if (e == dest)
                return pathLen - 1;

            // 遍历拿出来的这个顶点的邻接边
            for (int j = 0; j < G->vertexNum; j++) {
                // 若有边，且未被访问过
                if (G->adjMatrix[e][j] && !visited[j]) {
                    visited[j] = true;
                    EnQueue(&queue, j);
                }
            }
        }
    }
    // 若无法到达
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

    printf("\n");

    // 求 v1 (0) 到 v3 (2) 的最短路径长度
    int src = 0, dest = 2;
    printf("Shortest path from %s to %s: ", vertices[src], vertices[dest]);
    int dist = ShortestPath(&G, src, dest);
    printf(" distance = %d\n", dist);

    DestroyGraphAM(&G);
}
