#include<stdbool.h>

// 求 1 到 n 的累加和
long sum_n(int n) {
    long res = 0;           // (1)
    int i = 0;              // (2)

    for (; i <= n; i++) {   // (3)
        res += i;           // (4)
    }

    return res;             // (5)
}

// 求数组元素的累加和
int sum_arr(int arr[], int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += arr[i];
    }
    return res;
}

long sum_n2(int n) {
    long res = 0;               // (1)
    int i = 0;                  // (2)

    for (; i <= n; i++) {       // (3)
        int j = 0;              // (4)
        for (; j <= n; j++) {   // (5) 
            res += (i * j);     // (6)      
        }
    }

    return res;                 // (7) 
}


void print_num(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= j; k++) {
                printf("%d\n", i + j + k);
            }
        }
    }
}

int cal1(int n) {
    int x = 0;
    for (int i = 1; i <= n; i = i * 3) {
        x++;
    } 
    return x;
}

int cal2() {
    int x = 0;
    for (int i = 1; i <= 1000; i++) {
        x++;
    } 
    int s = 10;
    return x + s;
}

int sum_1(int n) {
    int sum1 = 0;
    for (int i = 1; i <= 1000; i++) {
        sum1 += i;
    }

    int sum2 = 0;
    for (int i = 1; i <= n; i++) {
        sum2 += i;
    }

    int sum3 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum3 += i;
        }
    }

    return sum1 + sum2 + sum3;
}

int sum_2(int n, int m) {
    int sum1 = 0;
    for (int i = 1; i <= 1000; i++) {
        sum1 += i;
    }

    int sum2 = 0;
    for (int i = 1; i <= n; i++) {
        sum2 += i;
    }

    int sum3 = 0;
    for (int i = 1; i <= m; i++) {
        sum3 += i;
    }

    return sum1 + sum2 + sum3;
}

long sum_3(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += sumSquare(i);
    }
    return sum;
}

long sumSquare(int n) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res += (i * i);
    }
    return res;
}

// 判断数组 arr 中是否存在目标值 target
bool contains(int arr[], int n, int target) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

// 插入排序
void InsertSort(int nums[], int n) {
    if (n <= 1) return;

    for (int i = 1; i < n; i++) {
        if (nums[i] >= nums[i - 1]) continue;
        int numsi = nums[i];
        int j = i - 1;
        for (; j >= 0 && numsi < nums[j]; j--) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = numsi;
    }
}

// 翻转数组
void reverse(int arr[], int n) {
    int i = 0;
    int temp[n];

    for (; i < n; i++) {
        temp[i] = arr[n - i - 1];
    }

    for (; i < n; i++) {
        arr[i] = temp[i];
    }
}