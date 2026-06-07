#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//- - - - -图的邻接矩阵存储表示- - - - -

// 假设顶点的数据类型为字符型
typedef char *VertexType;       

typedef struct {
   VertexType *vertices;       // 顶点表
   bool **adjMatrix;           // 邻接矩阵
   int vertexNum;              // 图的顶点数
   int edgeNum;                // 图的边数
   bool isDirected;            // true 表示网是有向图，否则是无向图
} AMGraph;

// 返回顶点 v 在顶点表中的下标
// 时间复杂度：O(n)
// 用散列表实现，可以将时间复杂度降低到 O(1)
int LocateVex(AMGraph *G, VertexType v) {
    for (int i = 0; i < G->vertexNum; i++) {
        if (strcmp(G->vertices[i], v) == 0) return i;
    }
    return -1;
}

// 初始化图的邻接矩阵表示，输入是图的顶点集和边集
// 时间复杂度：O(n^2)
// 空间复杂度：O(n^2)
void InitGraphAM(AMGraph *G, bool isDirected,
        int vertexNum, VertexType vertices[vertexNum],  
        int edgeNum, VertexType edges[edgeNum][2]) {
    // 初始化顶点数和边数
    G->vertexNum = vertexNum;
    G->edgeNum = edgeNum;
    G->isDirected = isDirected;

    // 创建大小为顶点个数的顶点表，用来存储每个顶点
    G->vertices = (VertexType *) malloc (sizeof(VertexType) * vertexNum);
    // 时间复杂度：O(n)
    for (int i = 0; i < vertexNum; i++) {
        G->vertices[i] = vertices[i];
    }

    // 创建邻接矩阵，大小是顶点数 * 顶点数
    G->adjMatrix = (bool **) malloc (sizeof(bool *) * vertexNum);
    // 时间复杂度：O(n^2)
    for (int i = 0; i < vertexNum; i++) {
        G->adjMatrix[i] = (bool *) malloc (sizeof(bool) * vertexNum);
        for (int j = 0; j < vertexNum; j++) 
            G->adjMatrix[i][j] = 0;     // 元素初始化为 0
    }

    // 遍历每条边，并设置到邻接矩阵相应元素中
    // 时间复杂度：O(e)，无向图 e 的最大值 n(n-1)/2，有向图 e 的最大值 n(n-1)
    for (int i = 0; i < edgeNum; i++) {
        int a = LocateVex(G, edges[i][0]);
        int b = LocateVex(G, edges[i][1]);
        if (a == -1 || b == -1) {
            printf("错误：边 %s-%s 包含不存在的顶点\n", edges[i][0], edges[i][1]);
            continue;
        }
        G->adjMatrix[a][b] = 1;
        // 如果是无向图，则需要设置对称的元素值为 1
        if (!isDirected) G->adjMatrix[b][a] = 1;
    }
}

// 销毁图操作
void DestroyGraphAM(AMGraph *G) {
    // 首先释放顶点表的存储空间
    if (G->vertices) free(G->vertices);
    if (G->adjMatrix) {
        // 然后释放邻接矩阵每一行的存储空间
        for (int i = 0; i < G->vertexNum; i++) {
            if (G->adjMatrix[i]) free(G->adjMatrix[i]);
        }
        // 最后释放邻接矩阵的存储空间
        free(G->adjMatrix);
    }
}

// 打印邻接矩阵
void PrintGraphAM(AMGraph *G) {
    printf("adj matrix graph:\n");
    for (int i = 0; i < G->vertexNum; i++) {
        for (int j = 0; j < G->vertexNum; j++) {
            printf("%d ", G->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// 判断两个顶点之间是否有边
// 时间复杂度：O(1)
bool GraphAMHasEdge(AMGraph *G, VertexType v, VertexType w) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == -1) return false;

    return G->adjMatrix[i][j];
}

// 顶点 v 的入度
// 时间复杂度：O(n)
int GraphAMInDegree(AMGraph *G, VertexType v) {
    if (!G->isDirected) return 0; // 无向图没有入度的概念
    int j = LocateVex(G, v);
    if (j == -1) return 0;
    int res = 0;
    // 在有向图的邻接矩阵中，行下标是弧的起点，而列下标是弧的终点
    // 第 j 列元素值为 1 的个数就是顶点 j 的入度（以顶点 j 为终点的弧的数量）
    for (int i = 0; i < G->vertexNum; i++) {
        if (G->adjMatrix[i][j]) res++;
    }
    return res;
}

// 顶点 v 的出度
// 时间复杂度：O(n)
int GraphAMOutDegree(AMGraph *G, VertexType v) {
    if (!G->isDirected) return 0; // 无向图没有出度的概念
    int i = LocateVex(G, v);
    if (i == -1) return 0;
    // 在有向图的邻接矩阵中，行下标是弧的起点，而列下标是弧的终点
    // 第 i 行元素值为 1 的个数就是顶点 i 的出度（以顶点 i 为起点的弧的数量）
    int res = 0;
    for (int j = 0; j < G->vertexNum; j++) {
        if (G->adjMatrix[i][j]) res++;
    }
    return res;
}

// 顶点 v 的度
// 时间复杂度：O(n)
int GraphAMDegree(AMGraph *G, VertexType v) {
    if (G->isDirected) { // 有向图顶点的度等于入度加出度
        return GraphAMInDegree(G, v) + GraphAMOutDegree(G, v);
    } else {
        // 无向图顶点的度等于邻接矩阵中对应行（或列）的非零元素个数
        int i = LocateVex(G, v);
        if (i == -1) return 0;
        int res = 0;
        // 第 i 行元素值为 1 的个数就是顶点 i 的度
        for (int j = 0; j < G->vertexNum; j++) {
            if (G->adjMatrix[i][j]) res++;
        }
        return res;
    }
}