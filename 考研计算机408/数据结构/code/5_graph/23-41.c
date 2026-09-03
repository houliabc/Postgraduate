typedef struct{ //图的类型定义
int numVertices,numEdges;  //图的顶点数和有向边数
char VerticesList[MAXV];  //顶点表，MAXv为己定义常量
int Edge [MAXV][MAXV];  //邻接矩阵
}MGraph;
（1）初始化K顶点个数为0。遍历顶点表里的每个顶点，分别计算该顶点的出度和入度，若出度大于入度，则将K顶点个数+1，同时输出该顶点
（2）
int printVertices(MGraph G) {
    int k = 0; // 统计k顶点个数
    for (int i = 0; i < G.numVertices; i++) {
        // 初始化入度和出度
        int out = 0, in = 0;
        for (int j = 0; j < G.numVertices; j++) {
            if (G.Edge[i][j] == 1)
                out++;
            if (G.Edge[j][i] == 1)
                in++;
        }
        // 若为K顶点
        if (out > in) {
            k++;
            // 输出K顶点
            printf("%c ", G.VerticesList[i]);
        }
    }
    return k;
}