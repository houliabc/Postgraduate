
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int v;
    int distance;
} Index2Dis;

typedef Index2Dis HElemType;

typedef struct {  
    HElemType *data;  // 存储堆元素的数组
    int capacity;     // 堆容量
    int heapSize;     // 堆大小
} MaxHeap, MinHeap;

// 交换两个元素的值
void swap(HElemType *a, HElemType *b) {
    HElemType temp = *a;
    *a = *b;
    *b = temp;
}

// 堆的初始化
void InitMinHeap(MinHeap *H, int n) {
    H->data = (HElemType *) malloc(n * sizeof(HElemType));
    H->heapSize = 0;
    H->capacity = n;
}

// 堆的销毁
void DestoryMinHeap(MinHeap *H) {
    if (H->data) free(H->data);
}

// 堆判空操作
// 时间复杂度：O(1)
bool MinHeapEmpty(MinHeap *H) {
    return H->heapSize == 0;
}

// 查询最小元素
// 时间复杂度：O(1)
bool extractMin(MinHeap *H, HElemType *e) {
    // 堆空，查询失败
    if (MinHeapEmpty(H)) return false;

    *e = H->data[0];
    return true;
}

// 往堆中插入元素 e
bool MinHeapInsert(MinHeap *H, HElemType e) {
    // 如果数组满了，插入失败
    if (H->heapSize == H->capacity) return false;

    // 将新元素追加到数组末尾，并增加堆大小
    int k = H->heapSize;
    H->data[k] = e;
    H->heapSize++;

    // 上浮最后一个结点
    int parent;
    // 只要不是根结点，就需要判断是否需要调整
    while (k > 0) {
        parent = (k - 1) / 2;

        // 如果新插入元素大于等于父结点值，则不需要调整
        if (H->data[k].distance >= H->data[parent].distance) break;

        // 否则，将新插入元素上浮
        swap(&H->data[k], &H->data[parent]);

        // 下一轮继续判断是否需要上浮
        k = parent;
    }
    return true;
}

// 将下标为 k 的结点做下沉操作
void sink(MinHeap *H, int k) {
    // 如果当前结点不是叶子结点，就要一直尝试下沉
    while (k < H->heapSize / 2) {
        // 计算得到左右子节点的下标
        int smallest = 2 * k + 1;
        int right = 2 * k + 2;
        // 然后找出值最小的子结点
        if (right < H->heapSize &&
                H->data[right].distance <= H->data[smallest].distance)
            smallest = right;

        // 如果当前结点的值小于等于最小的子结点值，
        // 说明，已经符合小根堆的特点，直接退出循环
        if (H->data[k].distance <= H->data[smallest].distance) break;

        // 否则，将当前结点和最小子结点交换
        swap(&H->data[k], &H->data[smallest]);

        // 并且继续尝试判断要不要下沉
        k = smallest;
    }
}

// 删除堆顶最大元素
bool MinHeapDelMin(MinHeap *H, HElemType *e) {
    // 如果堆空，则删除失败
    if (MinHeapEmpty(H)) return false;

    if (e) *e = H->data[0];

    // 将数组中的最后一个元素，直接覆盖堆顶元素
    H->data[0] = H->data[H->heapSize - 1];
    // 减少堆大小
    H->heapSize--;

    // 将新的堆顶结点下沉
    sink(H, 0);

    return true;
}