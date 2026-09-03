#include <limits.h>

#include "../NetworkAM.c"
#include "DijkstraMinHeap.c"

int *disTo;

// 这里使用堆实现的 Dijkstra 还不是最优解，要看最优的代码，请看【算法 4】这本书中讲的最短路径算法
// 时间复杂度：O(n^2 * logn)
// 空间复杂度：O(n)
void ShortestPath_Dijkstra(AMNetwork *G, VertexType k) {
    int v = LocateVex(G, k);

    disTo = (int *) malloc (sizeof(int) * G->vertexNum);
    bool *comfirmed = (bool *) malloc (sizeof(bool) * G->vertexNum);
    for (int w = 0; w < G->vertexNum; w++) {
        disTo[w] = INT_MAX;
        comfirmed[w] = false;
    }

    MinHeap H;
    InitMinHeap(&H, G->vertexNum);

    disTo[v] = 0;

    // 将顶点 v 插入小根堆
    Index2Dis i2d;
    i2d.v = v;
    i2d.distance = 0;
    MinHeapInsert(&H, i2d);

    Index2Dis e;
    // 时间复杂度：O(n)
    while (!MinHeapEmpty(&H)) {

        // 时间复杂度：O(logn)
        MinHeapDelMin(&H, &e);

        // 1. 找到当前没有访问的最短路径顶点
        int curr = e.v;
        if (comfirmed[curr]) continue;

        // 2. 确认这个节点的最短路径就是当前大小
        comfirmed[curr] = true;

        // 3. 根据这个顶点的最短路径大小，更新其他顶点的路径长度
        // 时间复杂度：O(nlogn)
        for (int w = 0; w < G->vertexNum; w++) {
            if (G->adjMatrix[curr][w] != INT_MAX &&         // w 是 curr 的邻接点
                    !comfirmed[w] &&                           // v 到 w 的最短距离还没有确定
                    disTo[curr] != INT_MAX &&               // v 到 curr 有路径
                    disTo[curr] + G->adjMatrix[curr][w] < disTo[w]) { // 从 v 到 curr 再到 w 的路径比 v 到 w 的路径还要短
                // 将 v 到达 w 的路径长度，设置为从 v 到 curr 再到 w 的路径长度
                disTo[w] = disTo[curr] + G->adjMatrix[curr][w];
                
                // 将到目前为止，将顶点 w 和 v 到 w 的最短路径长度，放到小根堆中
                Index2Dis i2d;
                i2d.v = w;
                i2d.distance = disTo[w];
                MinHeapInsert(&H, i2d);
            }
        }
    }
}

int main() {
    AMNetwork G;
    
    // 6 个顶点
    int vertexNum = 6;
    char* vertices[6] = {"v0", "v1", "v2", "v3", "v4", "v5"};

    // 10 条边
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

    ShortestPath_Dijkstra(&G, "v0");

    for (int i = 0; i < vertexNum; i++) {
        if (disTo[i] == INT_MAX) {
            printf("- ");
        } else {
            printf("%d ", disTo[i]);
        }
    }

    DestroyNetworkAM(&G);
}