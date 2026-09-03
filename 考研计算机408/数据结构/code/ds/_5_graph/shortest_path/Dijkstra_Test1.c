#include <limits.h>

#include "Dijkstra.c"

int main() {
    AMNetwork G;
    
    // 5 个顶点
    int vertexNum = 5;
    char* vertices[5] = {"0", "1", "2", "3", "4"};

    // 8 条边
    int edgeNum = 8;
    char* edges[8][3] = {
        {"0", "1", "4"},
        {"0", "2", "2"},
        {"1", "2", "1"},
        {"1", "3", "2"},
        {"1", "4", "3"},
        {"2", "3", "4"},
        {"2", "4", "5"},
        {"3", "4", "1"}
    };

    // 创建一个无向网
    InitNetworkAM(&G, false, vertexNum, vertices, edgeNum, edges);

    ShortestedgeTo_Dijkstra(&G, "0");

    PrintResult(G.vertexNum);

    DestroyNetworkAM(&G);

    free(distTo);
    free(edgeTo);
}