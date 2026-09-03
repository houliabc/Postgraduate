#include <stdbool.h>
#include "../NetworkAL.c"
#include "../topo/TopologicalSortAL.c"
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// 打印邻接表表示的有向网的关键路径
// 时间复杂度：O(n + e)，n 是顶点数，e 是边数
// 空间复杂度：O(n)
bool CriticalPath(ALGraph *G) {
    int n = G->vertexNum, *topo = (int*)malloc(sizeof(int) * n);

    // 1. 调用 TopologicalSort 获取拓扑序列，若失败则返回 false
    if (!TopologicalSort(G, topo))  return false;  // 连拓扑排序都没有那肯定就没关键路径了（基于拓扑排序的正序和逆序便利）

    // 2. 按拓扑序计算每个事件的最早发生时间 ve[]
    int ve[n];
    for (int i = 0; i < n; i++) ve[i] = 0;
    for (int i = 0; i < n; i++) {
        // 并不是真正按照下标顺序访问顶点，而是按照拓扑序列
        int k = topo[i];  // 第i个拓扑排序序列
        EdgeNode *p = G->adjList[k].firstEdge;
        while (p) {
            // k -> j
            int j = p->adjvex;  // j表示终点，i是起点
            ve[j] = max(ve[j], ve[k] + p->weight);
            p = p->nextEdge;
        }
    }

    // 3. 按逆拓扑序计算每个事件的最晚发生时间 vl[]
    int vl[n];
    for (int i = 0; i < n; i++) vl[i] = ve[n - 1];  // 初始化为汇点，因为是逆拓扑排序
    // 逆序，从后往前开始访问拓扑序列
    for (int i = n - 1; i >= 0; i--) {
        int k = topo[i];  // 第i个拓扑排序序列
        EdgeNode *p = G->adjList[k].firstEdge;
        while (p) {
            // k -> j
            int j = p->adjvex;  // j表示终点，i是起点
            vl[k] = min(vl[k], vl[j] - p->weight);
            p = p->nextEdge;
        }
    }

    // 4. 遍历所有边，判断是否为关键活动（e == l），输出关键活动
    for (int i = 0; i < n; i++) {
        EdgeNode *p = G->adjList[i].firstEdge;
        while (p) {
            // i -> j
            int j = p->adjvex;  // j表示终点，i是起点
            int ae = ve[i];  // 活动的最早开始时间ae
            int al = vl[j] - p->weight;  // 活动的最迟开始时间al
            // 若活动最早时间=最迟时间，则是关键路径
            if (ae == al) 
                printf("%s-%s, ", G->adjList[i].data, G->adjList[j].data);
            p = p->nextEdge;
        }
    }
    return true;
}

int main() {
    ALGraph G;
    
    // 9 个顶点
    int vertexNum = 9;
    char* vertices[9] = {"V0", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8"};

    // 11 条边
    int edgeNum = 11;
    char* edges[11][3] = {
        {"V0", "V1", "6"},
        {"V0", "V2", "4"},
        {"V0", "V3", "5"},
        {"V1", "V4", "1"},
        {"V2", "V4", "1"},
        {"V3", "V5", "2"},
        {"V4", "V6", "9"},
        {"V4", "V7", "7"},
        {"V5", "V7", "1"},
        {"V6", "V8", "2"},
        {"V7", "V8", "4"}
    };

    // 初始化
    InitNetworkAL(&G, true, vertexNum, vertices, edgeNum, edges);
    
    CriticalPath(&G);

    DestroyNetworkAL(&G);
    return 0;
}