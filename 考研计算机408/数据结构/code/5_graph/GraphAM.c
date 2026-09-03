#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//- - - - -图的邻接矩阵存储表示- - - - -

// 假设顶点的数据类型为字符型指针
typedef char *VertexType;

// 邻接矩阵存储的图结构
typedef struct {
    VertexType *vertices;       // 顶点表
    bool **adjMatrix;           // 邻接矩阵
    int vertexNum;              // 图的顶点数
    int edgeNum;                // 图的边数
    bool isDirected;            // 表明是否为有向图，1为有向图
} AMGraph;  // Adjacency matrix：邻接矩阵

// ---------- 函数声明 ----------

// 返回顶点 v 在顶点表中的下标
int LocateVex(AMGraph *G, VertexType v) {
    for (int i = 0; i < G->vertexNum; i++) {
        if (strcmp(G->vertices[i], v) == 0)   // ==0表示二者字符串相同
            return i;
    }
    return -1;
}

// 初始化图的邻接矩阵表示
void InitGraphAM(AMGraph *G, bool isDirected, 
        int vertexNum, VertexType vertices[vertexNum],  
        int edgeNum, VertexType edges[edgeNum][2]) {
            G->vertexNum = vertexNum;
            G->edgeNum = edgeNum;
            // ！！！有向图和无向图的唯二两个区别
            G->isDirected = isDirected;
            // 先开辟空间：创建大小为v的顶点表用于存放每个顶点
            G->vertices = (VertexType*)malloc(sizeof(VertexType) * vertexNum);
            for (int i = 0; i < vertexNum; i++) {
                G->vertices[i] = vertices[i];
            }

            //创建邻接矩阵，邻接矩阵是一个二重指针，bool类型
            G->adjMatrix = (bool**)malloc(sizeof(bool*) * vertexNum);
            // 根据v个顶点，创建对应的v个数组
            for (int i = 0; i < vertexNum; i++) {
                // 而每个数组大小又都是v
                G->adjMatrix[i] = (bool*)malloc(sizeof(bool) * vertexNum);
                for (int j = 0; j < vertexNum; j++) {
                    // 每个元素初始化为0
                    G->adjMatrix[i][j] = 0;
                }
            }

            // 遍历每条边，将每条边加入到邻接矩阵当中
            for (int i = 0; i < edgeNum; i++) {
                // 获取每条边对应的两个顶点下标
                int a = LocateVex(G, edges[i][0]);
                int b = LocateVex(G, edges[i][1]);
                // 处理边找不到顶点的情况：
                if (a == -1 || b == -1) {
                    printf("错误：边 %s-%s 包含不存在的顶点\n", edges[i][0], edges[i][1]);
                    continue;
                }
                // 将相邻顶点的边标记为1
                G->adjMatrix[a][b] = 1;
                // ！！！有向图和无向图的唯二两个区别：有向图不是对称矩阵
                if (!G->isDirected)
                    G->adjMatrix[b][a] = 1;
            }
        }

// 销毁图
void DestroyGraphAM(AMGraph *G) {
    if (G->vertices)
        free(G->vertices);
    
    if (G->adjMatrix) {
        for (int i = 0; i < G->vertexNum; i++) {        
            if (G->adjMatrix[i])
                free(G->adjMatrix[i]);
        }
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
bool GraphAMHasEdge(AMGraph *G, VertexType v, VertexType w) {
    // 先得到两个顶点的下标
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == -1)
        return false;
    return G->adjMatrix[i][j];
}

// 顶点 v 的入度（仅对有向图有效）
int GraphAMInDegree(AMGraph *G, VertexType v) {
    int j = LocateVex(G, v);
    if (j == -1 || !G->isDirected)
        return 0;
    int res = 0;
    for (int i = 0; i < G->vertexNum; i++) {
        // v的入度表示终点为v，即列是固定的
        if (G->adjMatrix[i][j])
            res++;
    }
    return res;
}

// 顶点 v 的出度（仅对有向图有效）
int GraphAMOutDegree(AMGraph *G, VertexType v) {
    int i = LocateVex(G, v);
    if (i == -1 || !G->isDirected)
        return 0;
    int res = 0;
    for (int j = 0; j < G->vertexNum; j++) {
        // v的出度表示起点为v，即行是固定的
        if (G->adjMatrix[i][j])
            res++;
    }
    return res;
}

// 顶点 v 的度（无向图为邻接边数，有向图为入度+出度）
int GraphAMDegree(AMGraph *G, VertexType v) {
    int i = LocateVex(G, v);
    if (i == -1)
        return 0;
    // 有向图的度=入度加出度
    if (G->isDirected) {
        return GraphAMInDegree(G, v) + GraphAMOutDegree(G, v);
    }
    else {
        int res = 0;
        for (int j = 0; j < G->vertexNum; j++) {
            if (G->adjMatrix[i][j])
                res++;
        }
        return res;
    }
}