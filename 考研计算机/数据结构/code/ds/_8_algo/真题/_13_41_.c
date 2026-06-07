#include "HashTable.c"

// 方法一：散列表
void mainEle_1(int A[], int n) {
    // 声明一个散列表，并初始化
    HashTable table;
    InitHashTable(&table, n);

    int val, cnt;
    for (int i = 0; i < n; i++) {
        // 对于每个 A[i] 元素
        // 如果在散列表中，表示之前出现过
        if (GetHashTable(&table, A[i], &val)) {
            // 更新这个元素出现的次数为：之前的出现次数加 1
            cnt = val + 1;
        } else {
            // 第一次出现，那么设置出现次数为 1
            cnt = 1;
        }
        if (cnt > n / 2) {
            printf("主元素是：%d\n", A[i]);
            return;
        }
        PutHashTable(&table, A[i], cnt);
    }
    // 不存在主元素
    printf("-1");
}

// 方法二：数组代替散列表
void mainEle_2(int A[], int n) {
    // 创建一个长度为 n 的数组 cnt，并将每个元素初始化为 0
    int cnt[n];
    for (int i = 0; i < n; i++) cnt[i] = 0;

    int val, cnt;
    for (int i = 0; i < n; i++) {
        int num = A[i];
        // 当前元素 A[i] 出现了 1 次
        cnt[num]++;
        // 如果元素 A[i] 出现的次数 > n/2，那么输出它，它就是主元素
        if (cnt[num] > n / 2) {
            printf("主元素 = %d\n", num);
            return;
        }
    }
    // 不存在主元素
    printf("-1");
}

// 方法三：摩尔投票
void mainEle_3(int A[], int n) {
    int candidate = -1;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] == candidate) count++;
        else if (count == 0) {
            candidate = A[i];
            count++;
        } else count--;
    }

    if (count == 0) printf("-1");
    else printf("主元素 = %d\n", candidate);
}