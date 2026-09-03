#include <limits.h>
#include "../NetworkAM.c"

// distTo[i]：表示源顶点 src 到顶点 i 的路径长度
int *distTo;
// edgeTo[i] 表示从源顶点到顶点 i 的最短路径上顶点 i 的前一个顶点
int *edgeTo;

// 求邻接矩阵表示的网 G 的 src（源）顶点到其余顶点的最短路径 
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
void ShortestedgeTo_Dijkstra(AMNetwork *G, VertexType src) {
    // 1. 获取源顶点下标 v，顶点数 n
    int n = G->vertexNum, v = LocateVex(G, src);
    // 2. 分配并初始化 distTo、edgeTo 和 confirmed 数组
    distTo = (int*)malloc(sizeof(int) * n);
    edgeTo = (int*)malloc(sizeof(int) * n);
    bool *confirmed = (bool*)malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        confirmed[i] = false;
        distTo[i] = G->adjMatrix[v][i];
        // 根据是否有边来更新edgeTo
        if (distTo[i] < INT_MAX)
            edgeTo[i] = v;
        else
            edgeTo[i] = -1;
    }
    // 3. 设置源顶点 distTo[v]=0，confirmed[v]=true
    distTo[v] = 0;
    confirmed[v] = true;

    // 4. 循环 n-1 次，每次选择未确认顶点中 distTo 最小的顶点，确认它，然后松弛其邻接边
    for (int i = 0; i < n - 1; i++) {
        int min = INT_MAX , k = -1;
        // 找最小的未确认顶点
        for (int j = 0; j < n; j++) {
            // bug fix：这里是小于等于，如果没有等于的话，distTo 中等于 INT_MAX 对应的 confirmed 就不会改成 true 了
            if (!confirmed[j] && distTo[j] <= min) {
                k = j;
                min = distTo[j];
            }
        }

        // 找到了最小的未确认顶点，将其确认，然后基于此顶点，尝试更新别的顶点的暂时最短路径
        confirmed[k] = true;
        for (int j = 0; j < n; j++) {
            if (!confirmed[j] && G->adjMatrix[k][j] !=INT_MAX && distTo[j] > distTo[k] + G->adjMatrix[k][j]) {
                distTo[j] = distTo[k] + G->adjMatrix[k][j];
                edgeTo[j] = k;
            }
        }
    }
    // 5. 释放 confirmed 数组
    free(confirmed);
}

// 打印结果（无需修改）
void PrintResult(int vertexNum) {
    printf("distTo: ");
    for (int i = 0; i < vertexNum; i++) {
        if (distTo[i] == INT_MAX) {
            printf("- ");
        } else {
            printf("%d ", distTo[i]);
        }
    }

    printf("\n-------------------\n");
    printf("edgeTo: ");
    for (int i = 0; i < vertexNum; i++) {
        printf("%d ", edgeTo[i]);
    }
}
// int main() {
//     AMNetwork G;
    
//     // 5 个顶点
//     int vertexNum = 5;
//     char* vertices[5] = {"0", "1", "2", "3", "4"};

//     // 8 条边
//     int edgeNum = 8;
//     char* edges[8][3] = {
//         {"0", "1", "4"},
//         {"0", "2", "2"},
//         {"1", "2", "1"},
//         {"1", "3", "2"},
//         {"1", "4", "3"},
//         {"2", "3", "4"},
//         {"2", "4", "5"},
//         {"3", "4", "1"}
//     };

//     // 创建一个无向网
//     InitNetworkAM(&G, false, vertexNum, vertices, edgeNum, edges);

//     ShortestedgeTo_Dijkstra(&G, "0");

//     PrintResult(G.vertexNum);

//     DestroyNetworkAM(&G);

//     free(distTo);
//     free(edgeTo);
// }


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