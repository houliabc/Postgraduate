（1）定义一个长度为n的数组，全部位置初始化为0，每个位置i的的值表示当前该数组中值为i的元素个数。遍历一遍数组统计好所有元素对应的元素个数，接着从里面找到一个最大的，如果个数超过数组一半大小，则输出该元素，否则输出-1
（2）
getMain(int A[], int n) {
    int count[n] = {0}; //全部位置初始化为0，表示统计个数为0
    for (int i = 0; i < n; i++) {
        count[A[i]]++;
    }
    int c = 0, index = 0;
    // 找到count表中计数最多的
    for (int i = 0; i < n; i++) {
        if(count[i] > c) {
            c = count[i];
            index = i;
        }
    }
    if (c > n/2)
        return index;
    else
        return -1; 
}
（3）时间复杂度O（n），空间复杂度O（n）