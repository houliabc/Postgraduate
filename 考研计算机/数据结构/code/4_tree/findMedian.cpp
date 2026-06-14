#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class MedianFinder {
private:
    // left  = 大顶堆, 存 较小 的一半  (堆顶是左半的最大值)
    // right = 小顶堆, 存 较大 的一半  (堆顶是右半的最小值)
    // 不变式: left.size() == right.size() 或 left.size() == right.size() + 1
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;

public:
    MedianFinder() {}

    // ---- 最优版 addNum: 每次最多 2 push + 1 pop (原版固定 3 次操作) ----
    void addNum(int num) {
        // 按值直接分配: 比左半最大值小 → 进左; 否则进右
        if (left.empty() || num <= left.top()) {
            left.push(num);
        } else {
            right.push(num);
        }
        // 平衡: 保持 left.size() >= right.size()
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {
        if (left.size() > right.size()) {
            return left.top();
        }
        return (left.top() + right.top()) / 2.0;
    }
};

int main() {
    MedianFinder mf;

    mf.addNum(1);
    mf.addNum(2);
    cout << "[1,2] median = " << mf.findMedian() << endl;       // 1.5

    mf.addNum(3);
    cout << "[1,2,3] median = " << mf.findMedian() << endl;     // 2.0

    mf.addNum(4);
    cout << "[1,2,3,4] median = " << mf.findMedian() << endl;   // 2.5

    mf.addNum(0);
    cout << "[0,1,2,3,4] median = " << mf.findMedian() << endl; // 2.0

    // 大规模随机测试
    MedianFinder big;
    srand(42);
    for (int i = 0; i < 100000; i++) {
        big.addNum(rand() % 100000);
    }
    cout << "100k rand nums median = " << big.findMedian() << endl;

    return 0;
}