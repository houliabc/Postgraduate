#ifndef GRAPHAL_H
#define GRAPHAL_H

#include <string.h>
#include <stdbool.h>

typedef char* VertexType;
typedef int EdgeType;

// 边表结点
typedef struct ENode {
    int adjvex;              // 邻接顶点——下标
    EdgeType weight;         // 边的权值
    struct ENode *nextEdge;  // 指向下一条边的指针
} EdgeNode;

// 顶点结点
typedef struct VNode {
    VertexType data;     // 顶点存储的数据
    EdgeNode *firstEdge; // 指向第一条依附该顶点的边的指针
} VertexNode;

// 图的邻接表表示
typedef struct {
    VertexNode *adjList;   // 邻接表
    int vertexNum;         // 图的顶点数
    int edgeNum;           // 图的边数
    bool isDirected;        // true 表示网是有向图，否则是无向图
} ALGraph;

// 从顶点表中，拿到顶点 v 对应的标识（即下标）
// 时间复杂度：O(n) 
// 可以使用散列表将其优化到 O(1) 的时间复杂度
int LocateVex(ALGraph *G, VertexType v) {
    for (int i = 0; i < G->vertexNum; i++) {
        if (strcmp(G->adjList[i].data, v) == 0) return i;
    }
    return -1;
}

#endif