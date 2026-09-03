typedef struct {                     // 图的类型定义
    int numVertices, numEdges;       // 图的顶点数和有向边数
    char VerticesList[MAXV];         // 顶点表，MAXV为已定义常量
    int Edge[MAXV][MAXV];            // 邻接矩阵
} MGraph;
（1）核心思想是先判断初始时，入度为0的顶点个数是否大于1，若大于1则返回0；否则先访问初始时入度为0的顶点，依次把该元素的邻接顶点的入度减一，若其减一后入度为0，则统计，此时若有超过1个以上的顶点度为0，则肯定不是唯一的拓扑序列，返回0。否则直到最后，都没有返回0且循环的次数等于顶点个数，则说明是唯一的拓扑序列，返回1
（2）
int uniquely(MGraph G) {
    int n = G.numVertices;
    int zero = 0; // 初始化时，入度为0的顶点个数
    int inDegree[n];  // 入度表
    // 初始化每轮记录入度为0的顶点下标，若没有则-1
    int zeroIdx = -1; 
    for (int i = 0; i < n; i++) inDegree[i] = 0;  // 初始化入度表为全0
    
    // 初始化入度表
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 若有入度，则入度表个数加一
            if (G.Edge[j][i])
                inDegree[i]++;
        }
        if (inDegree[i] == 0) {
            zero++;
            zeroIdx = i;
        }
        if (zero > 1) return 0;
    }

    int num = 0;  // 统计循环次数，要求等于顶点个数
    while (zeroIdx != -1) {
        zero = 0; // 统计每轮度为0的个数，若超过1，则拓扑序列不唯一
        int t = -1; // 暂存下一轮入度为0的下标
        // 将其邻接顶点入度-1
        for (int i = 0; i < n; i++) {
            // 将当前顶点入度标记，防止统计到
            inDegree[zeroIdx] = -1;
            if (G.Edge[zeroIdx][i]) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    zero++;
                    t = i;
                }
            }
        }
        if (zero > 1) return 0;
        // 每次用完就归-1或下一个入度为0的顶点
        zeroIdx = t;
        num++;
    }
    if (num ==  n)
        return 1;
    return 0;
}   