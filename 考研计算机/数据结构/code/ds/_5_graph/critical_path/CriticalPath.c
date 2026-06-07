#include <stdbool.h>

#include "../NetworkAL.c"
#include "../topo/TopologicalSortAL.c"

// 打印邻接表表示的有向网的关键路径
// 时间复杂度：O(n + e)，n 是顶点数，e 是边数
// 空间复杂度：O(n)
bool CriticalPath(ALGraph *G) {
    int n = G->vertexNum;
    // 创建一个顶点数量的数组，用于存储拓扑排序的序列
    int topo[n];
    // 调用拓扑排序算法，使拓扑序列保存在 topo 中，若调用失败，则存在有向环，返回 false
    if (!TopologicalSort(G, topo)) {
        printf("ERROR: graph has cycle");
        return false;
    }

    /*-------------------- 按拓扑次序求每个事件的最早发生时间 --------------*/
    // 给每个事件的最早发生时间置初值 0
    int ve[n];
    for (int i = 0; i < n; i++) ve[i] = 0;
    for(int i = 0; i < n; i++) { 
        int k = topo[i];
        EdgeNode *p = G->adjList[k].firstEdge;
        while (p) {
            int j = p->adjvex;
            // ve(j) = Max {ve(k)+wk,j}   
            if (ve[j] < ve[k] + p->weight) {
                ve[j] = ve[k] + p->weight;
            }
            p = p->nextEdge;
        }
    }

    /*-------------------- 按逆拓扑次序求每个事件的最晚发生时间 --------------*/
    // 给每个事件的最晚发生时间置初值 ve[n-1] （汇点的最早发生时间）
    int vl[n];
    for (int i = 0; i < n; i++) vl[i] = ve[n - 1];
    for(int i = n - 1; i >= 0; i--) { 
        int k = topo[i]; 
        EdgeNode *p = G->adjList[k].firstEdge;
        while (p) {
            int j = p->adjvex;
            // k → j
            // vl(k) = Min {vl(j) − wk,j}
            if (vl[k] > vl[j] - p->weight) 
                vl[k] = vl[j] - p->weight;
            
            p = p->nextEdge;
        }
    }

    /*-------------------- 判断每一活动是否为关键活动 --------------*/
    for(int i = 0; i < n; i++) {
        EdgeNode *p = G->adjList[i].firstEdge; 
        while (p) {
            int j = p->adjvex;
            // i → j
            int e = ve[i];  // 计算活动 <vi, vj> 的最早开始时间 
            int l = vl[j] - p->weight;  // 计算活动 <vi, vj> 的最晚开始时间
            if (e == l)             // 若为关键活动，则输出 <vi, vj> 
                printf("%s-%s ", G->adjList[i].data, G->adjList[j].data);
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