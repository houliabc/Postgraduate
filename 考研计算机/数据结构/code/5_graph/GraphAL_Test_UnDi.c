#include "GraphAL.c"

int main() {
    // 无向图
    ALGraph G;
    
    // 5 个顶点
    int vertexNum = 5;
    char *vertices[5] = {"v1", "v2", "v3", "v4", "v5"};

    // 5 条边
    int edgeNum = 5;
    char *edges[5][2] = {
        {"v1", "v2"},
        {"v1", "v4"},
        {"v2", "v3"},
        {"v3", "v4"},
        {"v2", "v5"}
    };

    // 初始化
    InitGraphAL(&G, false, vertexNum, vertices, edgeNum, edges);

    PrintGraphAL(&G);

    printf("vertex v2 Degree: %d\n", GraphALDegree(&G, "v2"));

    DestroyGraphAL(&G);
}