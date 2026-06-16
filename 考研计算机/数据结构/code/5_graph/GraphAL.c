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
    // TODO: 实现初始化
}

// 释放图占用的内存
void DestroyGraphAL(ALGraph *G) {
    // TODO: 释放所有动态分配的内存
}

// 打印图的邻接表表示
void PrintGraphAL(ALGraph *G) {
    // TODO: 按格式打印邻接表
}

// 判断两个顶点之间是否有边
// 时间复杂度：O(n)，一个顶点最多有 n - 1 条边
bool GraphALHasEdge(ALGraph *G, VertexType v, VertexType w) {
    // TODO: 返回 v 和 w 之间是否存在边
    return false;
}

// 顶点 v 的出度（仅对有向图有效）
// 时间复杂度：O(n)，一个顶点最多有 n - 1 条边
int GraphALOutDegree(ALGraph *G, VertexType v) {
    // TODO: 返回顶点 v 的出度
    return 0;
}

// 顶点 v 的入度（仅对有向图有效）
// 时间复杂度：O(n^2)
int GraphALInDegree(ALGraph *G, VertexType v) {
    // TODO: 返回顶点 v 的入度
    return 0;
}

// 顶点 v 的度（无向图为边数，有向图为入度+出度）
int GraphALDegree(ALGraph *G, VertexType v) {
    // TODO: 返回顶点 v 的度
    return 0;
}

// 从顶点表中，拿到顶点 v 对应的标识（即下标）
int LocateVex(ALGraph *G, VertexType v) {
    // TODO: 遍历顶点表，返回匹配的下标，否则返回 -1
    return -1;
}

// ---------- 测试主函数 ----------
int main() {
    // 测试用例：无向图
    // 顶点集合
    VertexType vertices[] = {"A", "B", "C", "D"};
    // 边集合（无向边）
    VertexType edges[][2] = {{"A", "B"}, {"A", "C"}, {"B", "D"}, {"C", "D"}};
    int vertexNum = 4;
    int edgeNum = 4;

    ALGraph G;
    // 初始化无向图
    InitGraphAL(&G, false, vertexNum, vertices, edgeNum, edges);

    printf("无向图邻接表：\n");
    PrintGraphAL(&G);

    // 测试边的存在性
    printf("A 和 C 是否有边？ %s\n", GraphALHasEdge(&G, "A", "C") ? "是" : "否");
    printf("A 和 D 是否有边？ %s\n", GraphALHasEdge(&G, "A", "D") ? "是" : "否");

    // 测试度
    printf("顶点 B 的度 = %d\n", GraphALDegree(&G, "B"));

    // 释放资源
    DestroyGraphAL(&G);

    // 测试有向图
    VertexType vertices2[] = {"V1", "V2", "V3", "V4"};
    VertexType edges2[][2] = {{"V1", "V2"}, {"V1", "V3"}, {"V2", "V4"}, {"V3", "V4"}};
    ALGraph G2;
    InitGraphAL(&G2, true, 4, vertices2, 4, edges2);

    printf("\n有向图邻接表：\n");
    PrintGraphAL(&G2);

    printf("V2 的出度 = %d\n", GraphALOutDegree(&G2, "V2"));
    printf("V2 的入度 = %d\n", GraphALInDegree(&G2, "V2"));

    DestroyGraphAL(&G2);

    return 0;
}