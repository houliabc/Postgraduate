#ifndef GRAPHAL_H
#define GRAPHAL_H
#include <string.h>
#include <stdbool.h>
// ----------------领接表的类型-------------


// 从顶点表中，拿到顶点 v 对应的标识（即下标）
// 时间复杂度：O(n) 
// 可以使用散列表将其优化到 O(1) 的时间复杂度
int LocateVex(ALGraph *G, VertexType v);

#endif