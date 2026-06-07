#include "MaxHeap.c"
#include "MinHeap.c"

typedef struct {
    MaxHeap *maxHeap;   // 大根堆（也称大顶堆）
    MinHeap *minHeap;   // 小根堆（也称小顶堆）
} MedianFinder;


MedianFinder* medianFinderCreate() {
    MedianFinder *obj = (MedianFinder *)malloc(sizeof(MedianFinder));

    // 创建并初始化大顶堆和小顶堆
    obj->maxHeap = (MaxHeap *)malloc(sizeof(MaxHeap));
    obj->minHeap = (MinHeap *)malloc(sizeof(MinHeap));

    // 题目规定了总的数据量是 50000，且大根堆比小根堆大小大 1
    InitMaxHeap(obj->maxHeap, 25001);
    InitMinHeap(obj->minHeap, 25000);

    return obj;
}

// 从数据流中添加一个整数到数据结构中
// 时间复杂度：log(n)
void medianFinderAddNum(MedianFinder* obj, int num) {
    // 如果大根堆空，则插入到大根堆
    if (MaxHeapEmpty(obj->maxHeap)) {
        MaxHeapInsert(obj->maxHeap, num);
        return;
    }

    int temp;
    extractMax(obj->maxHeap, &temp);
    if (num < temp) { // 如果插入元素小于等于大根堆堆顶元素，则插入大根堆
        MaxHeapInsert(obj->maxHeap, num);   
    } else { // 否则插入小根堆
        MinHeapInsert(obj->minHeap, num);
    }

    // 如果大根堆中的元素个数大于小根堆元素个数 + 1 的话
    // 则将大根堆堆顶元素删除，然后插入到小根堆中
    if (obj->maxHeap->heapSize > obj->minHeap->heapSize + 1) {
        MaxHeapDelMax(obj->maxHeap, &temp);
        MinHeapInsert(obj->minHeap, temp);
    } 

    // 如果大根堆中的元素格式小于小根堆元素个数
    // 将小根堆堆顶元素删除，然后插入到大根堆中
    if (obj->maxHeap->heapSize < obj->minHeap->heapSize) {
        MinHeapDelMin(obj->minHeap, &temp);
        MaxHeapInsert(obj->maxHeap, temp);
    } 
}

// 返回目前所有元素的中位数
// 时间复杂度：O(1)
double medianFinderFindMedian(MedianFinder* obj) {
    // 如果大根堆元素个数大于小根堆元素个数，则大根堆堆顶元素就是中位数
    if (obj->maxHeap->heapSize > obj->minHeap->heapSize) {
        int temp;
        extractMax(obj->maxHeap, &temp);
        return temp;
    } else { // 否则将大根堆堆顶元素和小根堆堆顶元素乘以 0.5 就是中位数
        int a, b;
        extractMax(obj->maxHeap, &a);
        extractMin(obj->minHeap, &b);
        return (a + b) * 0.5;
    }
}

void medianFinderFree(MedianFinder* obj) {
    DestoryMaxHeap(obj->maxHeap);
    DestoryMinHeap(obj->minHeap);
    free(obj);
}