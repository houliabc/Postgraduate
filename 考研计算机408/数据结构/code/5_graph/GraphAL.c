#include <stdlib.h>
#include <stdio.h>
#include "GraphAL.h"

// 初始化邻接表表示的图
// 时间复杂度：O(n + e)
// 空间复杂度：O(n + e)
void InitGraphAL(ALGraph *G, bool isDirected,
        int vertexNum, VertexType vertices[vertexNum],  
        int edgeNum, VertexType edges[edgeNum][2]) {
    G->isDirected = isDirected;
    G->vertexNum = vertexNum;
    G->edgeNum = edgeNum;
    // 开辟空间————创建表头结点表
    G->adjList = (VertexNode*)malloc(sizeof(VertexNode) * vertexNum);
    // 并初始化每个表头结点
    for (int i = 0; i < vertexNum; i++) {
        // G->adjList[i].data = (VertexType)malloc(sizeof(VertexType));  // 在下面已初始化为传入进来的参数结点
        // G->adjList[i].firstEdge = (EdgeNode*)malloc(sizeof(EdgeNode));  // 在下面已初始化为NULL
        // 初始化顶点数据和边表头指针（第一条边为空）
        G->adjList[i].data = vertices[i];
        G->adjList[i].firstEdge = NULL;
    }
    // 初始化边表
    for (int i = 0; i < edgeNum; i++) {
        int a = LocateVex(G, edges[i][0]);
        int b = LocateVex(G, edges[i][1]);
        if (a == -1 || b == -1) {
            printf("错误：边 %s-%s 包含不存在的顶点\n", edges[i][0], edges[i][1]);
            continue;
        }
        // 将a作为弧尾的出度加入对应顶点的边表中
        // 新建一个边表结点，插入到顶点 a 的边链表中
        EdgeNode *e = (EdgeNode*)malloc(sizeof(EdgeNode));
        e->adjvex = b;  // 出度指向的结点，也就是弧头
        e->nextEdge = G->adjList[a].firstEdge;
        G->adjList[a].firstEdge = e;

        // 针对无向图的来回算两条边
        if (!G->isDirected) {
            EdgeNode *e2 = (EdgeNode*)malloc(sizeof(EdgeNode));
            // 插入到顶点 b 的边链表中
            e2->adjvex = a;  // 入度指向的结点，也就是弧尾
            e2->nextEdge = G->adjList[b].firstEdge;
            G->adjList[b].firstEdge = e2;
        }
    }
}

// 释放图占用的内存
void DestroyGraphAL(ALGraph *G) {
    // 主要是释放所有的边结点
    for (int i = 0; i < G->vertexNum; i++) {
        EdgeNode *p = G->adjList[i].firstEdge, *t;
        while (p) {
            t = p;
            p = p->nextEdge;
            free(t);
        }
    }
    // 再释放分配的顶点数组
    free(G->adjList);
}

// 打印图的邻接表表示
void PrintGraphAL(ALGraph *G) {
    printf("curr graph adjList:\n");
    for (int i = 0; i < G->vertexNum; i++) {
        EdgeNode *p = G->adjList[i].firstEdge;
        // 打印当前顶点的信息
        // printf("%d: ", i);
        printf("%s: ", G->adjList[i].data);
        while (p) {
        printf("-> %s ", G->adjList[p->adjvex].data);
            p = p->nextEdge;
        }
        printf("\n");
    }
}

// 判断两个顶点之间是否有边，即v能不能到达w（是否有出度的问题）
// 时间复杂度：O(n)，一个顶点最多有 n - 1 条边
bool GraphALHasEdge(ALGraph *G, VertexType v, VertexType w) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == -1)
        return false;
    EdgeNode *p = G->adjList[i].firstEdge;
    while (p) {
        if (p->adjvex == j)
            return true;
        p = p->nextEdge;
    }
    return false;
}

// 顶点 v 的出度（仅对有向图有效）
// 时间复杂度：O(n)，一个顶点最多有 n - 1 条边
int GraphALOutDegree(ALGraph *G, VertexType v) {
    if (!G->isDirected) 
        return 0; // 无向图没有入度的概念
    int i = LocateVex(G, v), res = 0;
    if (i == -1)
        return 0;
    EdgeNode *p = G->adjList[i].firstEdge;
    while (p) {
        res++;
        p = p->nextEdge;
    }
    return res;
}

// 顶点 v 的入度（仅对有向图有效）
// 时间复杂度：O(n^2)
int GraphALInDegree(ALGraph *G, VertexType v) {
    if (!G->isDirected) 
        return 0; // 无向图没有入度的概念
    int j = LocateVex(G, v), res = 0;
    if (j == -1)
        return 0;
    // 遍历每个顶点的边链表
    for (int i = 0; i < G->vertexNum; i++) {
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            if (p->adjvex == j)
                res++;
            p = p->nextEdge;
        }
        
    }
    return res;
}

// 顶点 v 的度（无向图为边数，有向图为入度+出度）
int GraphALDegree(ALGraph *G, VertexType v) {
    int i = LocateVex(G, v);
    if (i == -1)
        return 0;
    if (G->isDirected)
        return GraphALInDegree(G, v) + GraphALOutDegree(G, v);
    else {
        // 无向图
        int res = 0;
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            res++;
            p = p->nextEdge;
        }
        return res;
    }
}

