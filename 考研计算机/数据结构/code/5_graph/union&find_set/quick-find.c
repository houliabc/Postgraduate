#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----- quick-find 算法 -------快速查找，合并较慢
typedef struct {
    int *id;  // 连通分量 id 数组
    int count; // 连通分量数量
    int length;  // id数组长度
} UF;  // Union-Find 的缩写

// 初始化并查集
void InitUF(UF *uf, int n) {
    // TODO: 分配 id 数组，初始化每个顶点为自己所在的分量，设置 count 和 length
    uf->id = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->id[i] = i;
    }
    uf->count = n;
    uf->length = n;
}

// 销毁并查集
void DestroyUF(UF *uf) {
    free(uf->id);
}

// 查询顶点 p 所属连通分量的 id
// 时间复杂度：O(1)
int findUF(UF *uf, int p) {
    return uf->id[p];
}

// 将顶点 p 和 q 合并到相同的连通分量中
// 时间复杂度：O(n)
void unionUF(UF *uf, int p, int q) {
    int pId = findUF(uf, p);
    int qId = findUF(uf, q);
    // 若相同，则不用合并
    if (pId == qId)
        return;
    // 否则将p所在连通分量中的所有顶点的id都修改为q所在连通分量的id
    for (int i = 0; i < uf->length; i++) {
        if (uf->id[i] == pId)
            uf->id[i] = qId;
    }
    // 连通分量个数-1
    uf->count--;
}

// 判断顶点 p 和顶点 q 是否连结
// 时间复杂度：O(1)
bool connectedUF(UF *uf, int p, int q) {
    return findUF(uf, p) == findUF(uf, q);
}