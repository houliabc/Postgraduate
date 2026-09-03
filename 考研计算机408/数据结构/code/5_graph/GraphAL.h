#ifndef GRAPHAL_H
#define GRAPHAL_H
#include <string.h>
#include <stdbool.h>

//---------- 图的邻接表表示 --------------
// 数组+链表的实现方式
typedef char* VertexType;
typedef int ElemType;
// 边表结点
typedef struct ENode{
    int adjvex;  // 顶点下标
    ElemType weight;  // 权值
    struct ENode *nextEdge;
}EdgeNode;
// 顶点结点结构
typedef struct VNode{
    VertexType data; // 顶点的数据是一个字符串或者说是一个VertexType类型的数据
    EdgeNode *firstEdge;  // 边表的头指针
} VertexNode;
// 领接表结构——顶点数据结构
typedef struct {
    VertexNode *adjList; // 顶点数组————也就是领接表
    int edgeNum, vertexNum, isDirected;
} ALGraph;

// 从顶点表中，拿到顶点 v 对应的标识（即下标）
// 时间复杂度：O(n) 
// 可以使用散列表将其优化到 O(1) 的时间复杂度
int LocateVex(ALGraph *G, VertexType v) {
    // TODO: 遍历顶点表，返回匹配的下标，否则返回 -1
    for (int i = 0; i < G->vertexNum; i++) {
        if (strcmp(G->adjList[i].data, v) == 0) {
            return i;
        }
    }
    return -1;
}
#endif