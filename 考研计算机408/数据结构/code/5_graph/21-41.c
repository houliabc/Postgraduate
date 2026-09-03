// （1）
// 遍历顶点表，先计算出每个顶点的度。若度为奇数的个数不是0或2个的话直接返回0；否则从任意一个顶点出发，访问其某一个邻接点，并统计经过边的个数且以此邻接点作为新的出发点，访问其某一个不属于上一个顶点的顶点，若不存在这样的顶点且边的个数和E不相同则返回0；当统计到边的个数为E时返回1。
// （2）
// int count = 0;
// int IsExistEL(MGraph G) {
//     int odd = 0; // 度为奇数的顶点个数
//     // 遍历顶点表来计算各顶点的度
//     for (int i = 0; i < G.numVertices; i++) {
//         int degree = 0;
//         for (int j = 0; j < G.numVertices; j++) {
//             if (G.Edge[i][j] == 1)
//                 degree++;
//         }
//         // 若是奇数的度，则度为奇数的统计个数+1
//         if (degree % 2 == 1)
//             odd++;
//     }
//     if (odd != 2 || odd != 0)
//         return 0;
//     int i = 0; // 表示从哪个顶点出发，初始时，先从第一个顶点出发
//     int pre = -1; // 表示上一个顶点是哪个，不能重复访问到上一个顶点处
//     // 循环次数为边的个数
//     for (int w = 0; w < G.numEdges; w++) {
//         for (int j = 0; j < G.numVertices; j++) {
//             if (G.Edge[i][j] == 1 && j != pre) {
//                 // 更新上一个的顶点，和当前出发的顶点
//                 i = j;
//                 pre = i;
//                 // 边个数+1
//                 count++;
//                 break;
//             }
//         }
//     }
//     if (count != G.numEdges)
//         return 0;
//     return 1;
// }
// （3）
// 时间复杂度为O(|VE|)，空间复杂度为O(1)


（1）
遍历顶点表，先计算出每个顶点的度。若度为奇数的个数不是0或2个的话直接返回0；否则返回1。
（2）
int IsExistEL(MGraph G) {
    int odd = 0; // 度为奇数的顶点个数
    // 遍历顶点表来计算各顶点的度
    for (int i = 0; i < G.numVertices; i++) {
        int degree = 0;
        for (int j = 0; j < G.numVertices; j++) {
            if (G.Edge[i][j] == 1)
                degree++;
        }
        // 若是奇数的度，则度为奇数的统计个数+1
        if (degree % 2 == 1)
            odd++;
    }
    if (odd != 2 && odd != 0)
        return 0;
    return 1;
}
（3）
时间复杂度为O(|V|^2)，空间复杂度为O(1)