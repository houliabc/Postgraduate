#include "GraphAM.c"

int main() {
    // 无向图
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
    InitGraphAM(&G, false, vertexNum, vertices, edgeNum, edges);

    PrintGraphAM(&G);

    printf("vertex v2 Degree: %d\n", GraphAMDegree(&G, "v2"));

    DestroyGraphAM(&G);
}