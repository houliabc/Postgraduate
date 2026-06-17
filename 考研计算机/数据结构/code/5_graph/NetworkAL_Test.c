#include "NetworkAL.c"

int main() {
    ALGraph G;
    
    // 6 个顶点
    int vertexNum = 6;
    char* vertices[6] = {"v1", "v2", "v3", "v4", "v5", "v6"};

    // 10 条边
    int edgeNum = 10;
    char* edges[10][3] = {
        {"v1", "v2", "5"},
        {"v1", "v4", "7"},
        {"v2", "v3", "4"},
        {"v3", "v1", "8"},
        {"v3", "v6", "9"},
        {"v4", "v3", "5"},
        {"v4", "v6", "6"},
        {"v5", "v4", "5"},
        {"v6", "v1", "3"},
        {"v6", "v5", "0"}
    };

    // 创建一个有向网
    InitNetworkAL(&G, true, vertexNum, vertices, edgeNum, edges);

    PrintNetworkAL(&G);

    DestroyNetworkAL(&G);
}