#include "../NetworkAM.c"
#include <limits.h>

//  distTo[i][j] 表示从顶点 i 到顶点 j 之间的最短路径
int **distTo;
// edgeTo[i][j] 表示最短路径上顶点 j 的前一顶点的序号
int **edgeTo;

// 用 Floyd 算法求有向网 G 中各对顶点 i 和 j 之间的最短路径 
void ShortestedgeTo_Floyd(AMNetwork *G) { 
    // 1. 分配 distTo 和 edgeTo 二维数组
    int n = G->vertexNum;
    distTo = (int**)malloc(sizeof(int*) * n);
    edgeTo = (int**)malloc(sizeof(int*) * n);
    // 2. 初始化 distTo 为邻接矩阵，edgeTo 为前驱
    for (int i = 0; i < n; i++) {
        distTo[i] = (int*)malloc(sizeof(int) * n);
        edgeTo[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            distTo[i][j] = G->adjMatrix[i][j];
            if (i == j)
                distTo[i][j] = 0;
            // 如果有弧，则前一个顶点设置为i
            edgeTo[i][j] = G->adjMatrix[i][j] != INT_MAX ? i : -1;
        }
    }
    // 3. 三重循环进行松弛
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // 动态规划更新任意顶点的最短路径
                if (i != j && k != i && k !=j &&
                G->adjMatrix[i][k] != INT_MAX && G->adjMatrix[k][j] != INT_MAX && 
                distTo[i][j] > distTo[i][k] + distTo[k][j]) {
                    distTo[i][j] = distTo[i][k] + distTo[k][j];
                    edgeTo[i][j] = edgeTo[k][j];
                }
            }
        }
    }
}

int main() {
    AMNetwork G;
    
    // 4 个顶点
    int vertexNum = 4;
    char* vertices[4] = {"v0", "v1", "v2", "v3"};

    // 8 条边
    int edgeNum = 8;
    char* edges[8][3] = {
        {"v0", "v1", "1"},
        {"v0", "v3", "4"},
        {"v1", "v2", "9"},
        {"v1", "v3", "2"},
        {"v2", "v0", "3"},
        {"v2", "v1", "5"},
        {"v2", "v3", "8"},
        {"v3", "v2", "6"}
    };

    // 创建一个有向网
    InitNetworkAM(&G, true, vertexNum, vertices, edgeNum, edges);

    PrintNetworkAM(&G);

    printf("--------------------\ndistTo：\n");

    ShortestedgeTo_Floyd(&G);

    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            printf("%d ", distTo[i][j]);
        }
        printf("\n");
    }

    printf("--------------------\nedgeTo：\n");

    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            printf("%d ", edgeTo[i][j]);
        }
        printf("\n");
    }

    DestroyNetworkAM(&G);
    return 0;
}