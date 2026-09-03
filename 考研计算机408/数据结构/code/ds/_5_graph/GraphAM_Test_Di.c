#include "GraphAM.c"

int main() {
    // 有向图
    AMGraph G;
    
    // 4 个顶点
    int vertexNum = 4;
    char* vertices[4] = {"v1", "v2", "v3", "v4"};

    // 4 条边
    int edgeNum = 4;
    char* edges[4][2] = {
        {"v1", "v2"},
        {"v1", "v3"},
        {"v3", "v4"},
        {"v4", "v1"}
    };

    InitGraphAM(&G, true, vertexNum, vertices, edgeNum, edges);

    PrintGraphAM(&G);

    printf("vertex v3 InDegree: %d\n", GraphAMInDegree(&G, "v3"));
    printf("vertex v1 OutDegree: %d\n", GraphAMOutDegree(&G, "v1"));


    DestroyGraphAM(&G);
}