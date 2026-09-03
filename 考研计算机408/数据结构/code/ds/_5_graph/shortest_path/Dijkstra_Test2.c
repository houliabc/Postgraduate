#include <limits.h>

#include "Dijkstra.c"

int main() {
    AMNetwork G;
    
    // 6 个顶点
    int vertexNum = 6;
    char* vertices[6] = {"v0", "v1", "v2", "v3", "v4", "v5"};

    // 8 条边
    int edgeNum = 8;
    char* edges[8][3] = {
        {"v0", "v2", "10"},
        {"v0", "v4", "30"},
        {"v0", "v5", "100"},
        {"v1", "v2", "5"},
        {"v2", "v3", "50"},
        {"v3", "v5", "10"},
        {"v4", "v3", "20"},
        {"v4", "v5", "60"}
    };

    // 创建一个有向网
    InitNetworkAM(&G, true, vertexNum, vertices, edgeNum, edges);

    ShortestedgeTo_Dijkstra(&G, "v0");

    PrintResult(G.vertexNum);

    DestroyNetworkAM(&G);

    free(distTo);
    free(edgeTo);
}