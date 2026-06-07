#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----- quick-find 算法 -------

typedef struct {
    int *id;   // 连通分量 id 数组
    int count; // 连通分量数量

    // bug 修复
    int length; // id 数组的长度
} UF;

// 初始化并查集
void InitUF(UF *uf, int n) {
    // 初始化分量 id 数组
    uf->id = (int *) malloc (sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->id[i] = i;
    }
    uf->count = n;

    // bug 修复
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

    // 如果 p 和 q 已经在相同的连通分量之中，则直接返回
    if (pId == qId) return;

    // 将 p 所在的连通分量中的所有顶点的连通分量分量 id 修改为 q 所在的连通分量的连通分量 id
    // bug 修复，这里是遍历 id 整个数组
    for (int i = 0; i < uf->length; i++) {
        if (uf->id[i] == pId) uf->id[i] = qId;
    }

    // 连通分量数减少了 1 个
    uf->count--;
}

// 判断顶点 p 和顶点 q 是否连结
// 时间复杂度：O(1)
bool connectedUF(UF *uf, int p, int q) {
    return findUF(uf, p) == findUF(uf, q);
}