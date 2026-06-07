#include <limits.h>

#include "../NetworkAM.c"

// distTo[i]：表示源顶点 src 到顶点 i 的路径长度
int *distTo;
// edgeTo[i] 表示从源顶点到顶点 i 的最短路径上顶点 i 的前一个顶点
int *edgeTo;

// 求邻接矩阵表示的网 G 的 src（源） 顶点到其余顶点的最短路径 
// 空间复杂度：O(n)
// 时间复杂度：O(n^2)
void ShortestedgeTo_Dijkstra(AMNetwork *G, VertexType src) {
    int v = LocateVex(G, src);  // 得到源顶点在数组中的下标
    int n = G->vertexNum;

    // 1. 创建并初始化两个数组
    distTo = (int *) malloc (sizeof(int) * n);
    // confirmed[i]：表示顶点 i 的最短路径长度是否已经确认
    bool *confirmed = (bool *) malloc (sizeof(bool) * n);
    edgeTo = (int *) malloc (sizeof(int) * n);
    for (int w = 0; w < n; w++) {
        // 将源顶点 v 到各个顶点的最短路径初始化为顶点 v 邻接边上的权值
        distTo[w] = G->adjMatrix[v][w];
        confirmed[w] = false;   // 每个顶点的最短路径一开始都没确认

        if (distTo[w] < INT_MAX) edgeTo[w] = v;
        else edgeTo[w] = -1;
    }

    // 2. 确认源顶点 v 到达源顶点 v 的最短路径为 0
    distTo[v] = 0; 
    confirmed[v] = true; 

    // 3. 对其余 n - 1 个顶点求最短路径，每轮循环确定一个顶点的最短路径
    for (int i = 1; i < n; i++) {
        // 3.1 在 distTo 数组中，拿到还未确认最短路径中的所有路径的最小值
        int min = INT_MAX;
        for (int w = 0; w < n; w++) {
            // bug fix：这里是小于等于，如果没有等于的话，distTo 中等于 INT_MAX 对应的 confirmed 就不会改成 true 了
            if (!confirmed[w] && distTo[w] <= min) {    
                min = distTo[w];
                v = w;
            }
        }

        // 3.2 确定 distTo[v] 就是源顶点到顶点 v 的最短路径长度
        confirmed[v] = true; 

        // 3.3 从顶点 v 出发，根据顶点 v 的有效邻接边的权值，来更新 distTo 数组
        for (int w = 0; w < n; w++) {
            if (G->adjMatrix[v][w] != INT_MAX &&    // v 到 w 有边
                    !confirmed[w] &&                // w 的最短路径还未确认
                    distTo[w] > distTo[v] + G->adjMatrix[v][w]) {
                // 从源顶点经过 v 到达 w 比之前的从源顶点到 w 还要近
                distTo[w] = distTo[v] + G->adjMatrix[v][w];
                edgeTo[w] = v;
            }
        }
    }

    free(confirmed);
}

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