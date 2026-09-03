#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----- quick-union 算法 -------

typedef struct {
    int *id;   // 连通分量 id 数组
    int count; // 连通分量数量
} UF;

// 初始化并查集
void InitUF(UF *uf, int n) {
    // 初始化分量 id 数组
    uf->id = (int *) malloc (sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->id[i] = i;
    }
    uf->count = n;
}

// 销毁并查集
void DestroyUF(UF *uf) {
    free(uf->id);
}

// 查询顶点 p 的根结点
// 时间复杂度：O(h)
int findUF(UF *uf, int p) {
    while (uf->id[p] != p) p = uf->id[p];
    return p;
}

// 将顶点 p 和 q 合并到相同的连通分量中
// 时间复杂度：O(h)
void unionUF(UF *uf, int p, int q) {
    int pRoot = findUF(uf, p);
    int qRoot = findUF(uf, q);

    // 如果 p 和 q 已经在相同的连通分量之中，则直接返回
    if (pRoot == qRoot) return;

    uf->id[pRoot] = qRoot;

    // 连通分量数减少了 1 个
    uf->count--;
}

// 判断顶点 p 和顶点 q 是否连结
// 时间复杂度：O(1)
bool connectedUF(UF *uf, int p, int q) {
    return findUF(uf, p) == findUF(uf, q);
}