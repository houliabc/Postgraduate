#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "GraphAL.h"

//---------- 图的邻接表表示 --------------

// 初始化邻接表表示的图
// 时间复杂度：O(n + e)
// 空间复杂度：O(n + e)
void InitGraphAL(ALGraph *G, bool isDirected,
        int vertexNum, VertexType vertices[vertexNum],  
        int edgeNum, VertexType edges[edgeNum][2]) {
    // 初始化图的顶点数和边数
    G->vertexNum = vertexNum;
    G->edgeNum = edgeNum;
    G->isDirected = isDirected;

    // 创建表头结点表，并初始化每个表头结点
    G->adjList = (VertexNode *) malloc(sizeof(VertexNode) * vertexNum);
    // 时间复杂度：O(n)
    for (int i = 0; i < vertexNum; i++) {
        // 设置顶点数据
        G->adjList[i].data = vertices[i];
        // 设置第一条边指向空
        G->adjList[i].firstEdge = NULL;
    }

    // 遍历每条边，创建每个顶点的边链表
    // 时间复杂度：O(e)
    for (int i = 0; i < edgeNum; i++) {
        // 拿到这条边的两个顶点序号
        int a = LocateVex(G, edges[i][0]);
        int b = LocateVex(G, edges[i][1]);
        if (a == -1 || b == -1) {
            printf("错误：边 %s-%s 包含不存在的顶点\n", edges[i][0], edges[i][1]);
            continue;
        }

        // 创建一个边结点，并插入到顶点 a 的边链表中
        EdgeNode *p1 = (EdgeNode *) malloc(sizeof(EdgeNode));
        p1->adjvex = b;
        p1->nextEdge = G->adjList[a].firstEdge;
        G->adjList[a].firstEdge = p1;

        if (!G->isDirected) {
            // 创建另一个边结点，并插入到顶点 b 的边链表中
            EdgeNode *p2 = (EdgeNode *) malloc(sizeof(EdgeNode));
            p2->adjvex = a;
            p2->nextEdge = G->adjList[b].firstEdge;
            G->adjList[b].firstEdge = p2;
        }
    }
}

// 释放图占用的内存
void DestroyGraphAL(ALGraph *G) {
    // 释放所有顶点的边链表结点占用的内存
    for (int i = 0; i < G->vertexNum; i++) {
         // 从每个顶点的第一条边开始释放每一个边结点
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            EdgeNode *temp = p;
            p = p->nextEdge;
            free(temp);
        }
    }

    // 释放表头结点占用的内存
    free(G->adjList);
}

// 打印图的邻接表表示
void PrintGraphAL(ALGraph *G) {
    printf("curr graph adjList:\n");
    for (int i = 0; i < G->vertexNum; i++) {
        // 打印当前顶点的信息
        // printf("%d: ", i);
        printf("%s: ", G->adjList[i].data);
        // 从顶点的第一条边开始，打印这个顶点的所有的边结点
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            // 打印当前边的邻接顶点信息
            // printf("-> %d ", p->adjvex);
            printf("-> %s ", G->adjList[p->adjvex].data);
            p = p->nextEdge;
        }
        printf("\n");
    }
}

// 判断两个顶点之间是否有边
// 时间复杂度：O(n)，一个顶点最多有 n - 1 条边
bool GraphALHasEdge(ALGraph *G, VertexType v, VertexType w) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == -1) return false;

    // 遍历顶点 i 的边链表
    EdgeNode *p = G->adjList[i].firstEdge;
    while (p) {
        // 如果在边链表中找到 j，说明 i 和 j 之间有边
        if (j == p->adjvex) return true;
        p = p->nextEdge;
    }
    return false;
}

// 顶点 v 的出度
// 时间复杂度：O(n)，一个顶点最多有 n - 1 条边
int GraphALOutDegree(ALGraph *G, VertexType v) {
    if (!G->isDirected) return 0; // 无向图没有出度的概念
    int i = LocateVex(G, v);
    if (i == -1) return 0;
    int res = 0;
    // 顶点 i 的边链表结点数量就是顶点 i 的出度
    EdgeNode *p = G->adjList[i].firstEdge;
    while (p) {
        res++;
        p = p->nextEdge;
    }
    return res;
}

// 顶点 v 的入度
// 时间复杂度：O(n^2)
int GraphALInDegree(ALGraph *G, VertexType v) {
    if (!G->isDirected) return 0; // 无向图没有入度的概念
    int j = LocateVex(G, v);
    if (j == -1) return 0;

    int res = 0;
    // 遍历所有顶点
    for (int i = 0; i < G->vertexNum; i++) {
        // 遍历当前顶点的边链表的所有结点，从第一条边开始
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            // 如果边结点的邻接点是 j，那么入度加 1
            if (p->adjvex == j) res++;
            p = p->nextEdge;
        }
    }
    return res;
}

// 顶点 v 的度
int GraphALDegree(ALGraph *G, VertexType v) {
    // 有向图的度等于入度加出度
    if (G->isDirected) return GraphALInDegree(G, v) + GraphALOutDegree(G, v);
    else {
        int i = LocateVex(G, v);
        if (i == -1) return 0;
        int res = 0;
        // 顶点 i 的边链表结点数量就是顶点 i 的度
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            res++;
            p = p->nextEdge;
        }
        return res;
    }
}