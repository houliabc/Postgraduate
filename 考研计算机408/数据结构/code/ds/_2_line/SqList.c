#include <stdbool.h>
#include <stdlib.h>

// 顺序表可能达到的最大长度
# define INIT_MAX_SIZE 10

typedef int ElemType;

typedef struct {
    ElemType *data;  // 存储空间的首地址
    int length;      // 当前长度
} SqList;

// 构造一个空的线性表 L
void InitList(SqList *L) {
    // 为顺序表分配一个大小为 INIT_MAX_SIZE 的数组空间
    L->data = (ElemType*)malloc(sizeof(ElemType) * INIT_MAX_SIZE);

    // 空表长度为 0
    L->length = 0;
}

// 销毁线性表 L
void DestroyList(SqList *L) {
    if (L) {
        // 释放回收数组存储空间
        free(L->data);
    }
}

// 在线性表 L 中第 i 个位置之前插入新的数据元素 e
bool ListInsert(SqList *L, int i, ElemType e) {
    // 如果 i 的范围是无效，则不能插入
    if (i < 1 || i > L->length + 1) 
        return false;
    // 如果当前存储空间满了，则不能插入
    if (L->length >= INIT_MAX_SIZE) 
        return false;
     // 将第 i 个元素及之后的元素后移
    for (int j = L->length; j >= i; j--)
        L->data[j] = L->data[j - 1];
    // 在位置 i 处存放 e
    L->data[i - 1] = e;
    // 顺序表长度加 1
    L->length++;
    return true;
}

// 删除线性表 L 的第 i 个数据元素
bool ListDelete(SqList *L, int i, ElemType *e) {
    // 如果 i 的范围是无效，则删除失败
    if (i < 1 || i > L->length) 
        return false;
    // 将被删除的元素赋值给指针 e 指向的存储单元
    if (e) *e = L->data[i - 1];
    // 将第 i 个位置后的元素前移
    for (int j = i; j <= L->length - 1; j++)
        L->data[j - 1] = L->data[j];
    // 顺序表长度减 1
    L->length--;
    return true;
}

// 修改线性表 L 的第 i 个数据元素为 e
// 时间复杂度：O(1)
bool ListUpdate(SqList *L, int i, ElemType e) {
    // 如果 i 的范围是无效，则修改失败
    if (i < 1 || i > L->length) 
        return false;
    // data[i - 1] 存储的是第 i 个元素
    L->data[i - 1] = e;
    return true;
}

// 查询线性表 L 是否为空
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool ListEmpty(SqList *L) {
    return L->length == 0;
}

// 查询线性表 L 的长度
// 时间复杂度：O(1)
// 空间复杂度：O(1)
int ListLength(SqList *L) {
    return L->length;
}

// 用 e 返回线性表 L 中第 i 个数据元素的值
// 时间复杂度：O(1)
// 空间复杂度：O(1)
bool GetElem(SqList *L, int i, ElemType *e) {
    // 如果 i 的范围是无效，则查询失败
    if (i < 1 || i > L->length) 
        return false;
    // data[i - 1] 存储的是第 i 个元素
    *e = L->data[i - 1];
    return true;
}

// 返回线性表 L 中第 1 个值与 e 相同的元素在 L 中的位置
// 时间复杂度：
    // 最好时间复杂度：O(1)
    // 最差时间复杂度：O(n)
    // 平均时间复杂度：O(n)
// 空间复杂度：O(1)
int LocateElem(SqList *L, ElemType e) {
    for (int i = 0; i < L->length; i++) {
        if (L->data[i] == e) 
            return i + 1; // 下标为 i 的元素值等于 e，返回其位序 i + 1
    }
    return 0;
}

// 对线性表 L 进行遍历打印每个元素
void TraverseList(SqList *L) {
    printf("curr SqList: ");
    for (int i = 0; i < L->length; i++) {
        if (i == 0) printf("(%d,", L->data[i]);
        else if (i == L->length - 1) printf("%d)\n", L->data[i]);
        else printf("%d,", L->data[i]);
    }
}