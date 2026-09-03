#include "../NetworkAM.c"

//  distTo[i][j] 表示从顶点 i 到顶点 j 之间的最短路径
int **distTo;
// edgeTo[i][j] 表示最短路径上顶点 j 的前一顶点的序号
int **edgeTo;

// 用 Floyd 算法求有向网 G 中各对顶点 i 和 j 之间的最短路径 
void ShortestedgeTo_Floyd(AMNetwork *G) { 
    // 状态定义
    distTo = (int **) malloc (sizeof(int*) * G->vertexNum);
    edgeTo = (int **) malloc (sizeof(int*) * G->vertexNum);

    // 状态初始化
    for(int v = 0; v < G->vertexNum; v++) {                
        distTo[v] = (int *) malloc (sizeof(int) * G->vertexNum);
        edgeTo[v] = (int *) malloc (sizeof(int) * G->vertexNum);
        for(int w = 0; w < G->vertexNum; w++) {  
            distTo[v][w] = G->adjMatrix[v][w]; 
            if (v == w) distTo[v][w] = 0;
             // 如果 v 和 w 之间有弧，则将 w 的前驱置为 v 
            if (G->adjMatrix[v][w] != INT_MAX) {
                edgeTo[v][w] = v;
            } else { // 如果 v 和 w 之间没有弧，则将 w 的前驱置为 -1 
                edgeTo[v][w] = -1; 
            }                    
        } 
    }

    // 状态转移
    // 在顶点 i 和顶点 j 之间加入顶点 k
    for (int k = 0; k < G->vertexNum; k++) {
        for (int i = 0; i < G->vertexNum; i++) {
            for (int j = 0; j < G->vertexNum; j++) {
                if (i != j && k != i && k != j &&
                        distTo[i][k] != INT_MAX && 
                        distTo[k][j] != INT_MAX && 
                        distTo[i][k] + distTo[k][j] < distTo[i][j]) { 
                    // 从 i 经 k 到 j 的一条路径更短 
                    distTo[i][j] = distTo[i][k] + distTo[k][j];
                    edgeTo[i][j] = edgeTo[k][j];  //更改 j 的前驱为 k 
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

    printf("--------------------\n");

    ShortestedgeTo_Floyd(&G);

    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            printf("%d ", distTo[i][j]);
        }
        printf("\n");
    }

    printf("--------------------\n");

    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            printf("%d ", edgeTo[i][j]);
        }
        printf("\n");
    }

    DestroyNetworkAM(&G);
}