#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "GraphAL.h"

//---------- 网的邻接表表示 --------------

// 初始化邻接表表示的网
void InitNetworkAL(ALGraph *G, bool isDirected,
        int vertexNum, VertexType vertices[vertexNum],  
        int edgeNum, VertexType edges[edgeNum][3]) {
    // 初始化图的顶点数和边数
    G->vertexNum = vertexNum;
    G->edgeNum = edgeNum;
    G->isDirected = isDirected;

    // 创建表头结点表，并初始化每个表头结点
    G->adjList = (VertexNode *) malloc(sizeof(VertexNode) * vertexNum);
    for (int i = 0; i < vertexNum; i++) {
        // 设置顶点数据
        G->adjList[i].data = vertices[i];
        // 设置第一条边指向空
        G->adjList[i].firstEdge = NULL;
    }

    // 遍历每条边，创建每个顶点的边链表
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
        p1->weight = atoi(edges[i][2]);
        p1->nextEdge = G->adjList[a].firstEdge;
        G->adjList[a].firstEdge = p1;

        if (!G->isDirected) {
            // 创建另一个边结点，并插入到顶点 b 的边链表中
            EdgeNode *p2 = (EdgeNode *) malloc(sizeof(EdgeNode));
            p2->adjvex = a;
            p2->weight = atoi(edges[i][2]);
            p2->nextEdge = G->adjList[b].firstEdge;
            G->adjList[b].firstEdge = p2;
        }
    }
}

// 释放图占用的内存
void DestroyNetworkAL(ALGraph *G) {
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
void PrintNetworkAL(ALGraph *G) {
    printf("curr Network adjList:\n");
    for (int i = 0; i < G->vertexNum; i++) {
        // 打印当前顶点的信息
        // printf("%d: ", i);
        printf("%s: ", G->adjList[i].data);
        // 从顶点的第一条边开始，打印这个顶点的所有的边结点
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            // 打印当前边的邻接顶点信息
            // printf("-> %d ", p->adjvex);
            printf("-> %s(weight: %d) ", G->adjList[p->adjvex].data, p->weight);
            p = p->nextEdge;
        }
        printf("\n");
    }
}

// 判断两个顶点之间是否有边
bool GraphALHasEdge(ALGraph *G, VertexType v, VertexType w) {
    // TODO
    return false;
}

// 顶点 v 的出度
int GraphALOutDegree(ALGraph *G, VertexType v) {
    return 0;
}

// 顶点 v 的入度
int GraphALInDegree(ALGraph *G, VertexType v) {
    return 0;
}

// 顶点 v 的度
int GraphALDegree(ALGraph *G, VertexType v) {
    return 0;
}