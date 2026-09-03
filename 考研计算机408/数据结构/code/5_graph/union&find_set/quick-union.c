#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// ----- quick-union 算法 -------快速合并，查找较慢
// 使用类似于树的思想
typedef struct {
    int *parent;  // 连通分量 parent 数组
    int count; // 连通分量数量
} UF;  // Union-Find 的缩写

// 初始化并查集
void InitUF(UF *uf, int n) {
    // TODO: 分配 parent 数组，初始化每个顶点为自己所在的分量，设置 count 和 length
    uf->parent = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
    }
    uf->count = n;
}

// 销毁并查集
void DestroyUF(UF *uf) {
    free(uf->parent);
}

// 查询顶点 p 所属连通分量的根节点——通过各自的根来判断顶点是否属于同一个几何
// 时间复杂度：O(h)
int findUF(UF *uf, int p) {
    while (uf->parent[p] != p) {
        p = uf->parent[p];
    }
    return p;
}

// 将顶点 p 和 q 合并到相同的连通分量中
// 时间复杂度：O(h)
void unionUF(UF *uf, int p, int q) {
    int pRoot = findUF(uf, p);
    int qRoot = findUF(uf, q);
    // 若相同，则不用合并
    if (pRoot == qRoot)
        return;
    // 否则将p所在连通分量中的所有顶点的Root都修改为q所在连通分量的Root
    uf->parent[pRoot] = qRoot;
    // 连通分量个数-1
    uf->count--;
}

// 判断顶点 p 和顶点 q 是否连结
// 时间复杂度：O(1)
bool connectedUF(UF *uf, int p, int q) {
    return findUF(uf, p) == findUF(uf, q);
}