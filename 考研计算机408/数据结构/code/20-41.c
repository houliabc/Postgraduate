（1）当 A<B<C 的时候，距离 D=2C-2A，也就意味着距离只跟最大的和最小的有关，如果要使这个距离最短，那么每次右移动最小的就可以缩短它的距离，由此就能得到最短距离。而每一轮最小的指针可能不一样，会动态变化，要根据情况去比较得到
（2）
// 比较两个数的大小，返回最大值
int max(int a, int b) {
    return a>b ? a : b;
}
// 比较两个数的大小，返回最小值
int min(int a, int b) {
    return a<b ? a : b;
}
int getMinDistance(int S1[], int S2[], int S3[], int n1, int n2, int n3) {
    int p1 = 0, p2 = 0, p3 = 0, m = 2 * (max(max(S1[p1], S2[p2]), S3[p3]) - min(min(S1[p1], S2[p2]), S3[p3])); // 初始化当前最小距离
    while (p1 < n1 && p2 < n2 && p3 < n3) {
        // 求得当前数组里距离值最小的和最大的
        int minVal = min(min(S1[p1], S2[p2]), S3[p3]), maxVal;
        // s1是最小值，且要求a<b<c
        if (S1[p1] == minVal && S1[p1] != S2[p2] && S1[p1] != S3[p3]) {
            // 表示最小指针不能继续右移了，此时找到了最小距离，则退出循环
            if (p1 == n1 - 1)  break;
            // 否则右移指针
            p1++;
        } else if (S1[p1] == minVal && S1[p1] == S2[p2]) {  // 此时最小值a和中间值b相同，不能直接移动其中一个，而是要二者都尝试一下
            if (p1 == n1 - 1 && p2 != n2 - 1) p2++;
            else if (p1 != n1 - 1 && p2 == n2 - 1) p1++;
            else {
                // p1尝试一下
                p1++;
                minVal = min(min(S1[p1], S2[p2]), S3[p3]), maxVal = max(max(S1[p1], S2[p2]), S3[p3]);
                int t = 2*(maxVal - minVal);
                if (t < m)
                    m = t;
                p1--;
                // 轮到p2
                p2++;
            }
        }
        else if (S1[p1] == minVal && S1[p1] == S2[p3]) {  // 此时最小值a和中间值b相同，不能直接移动其中一个，而是要二者都尝试一下
            if (p1 == n1 - 1 && p3 != n3 - 1) p3++;
            else if (p1 != n1 - 1 && p3 == n2 - 1) p1++;
            else {
                // p1尝试一下
                p1++;
                minVal = min(min(S1[p1], S2[p3]), S3[p3]), maxVal = max(max(S1[p1], S2[p3]), S3[p3]);
                int t = 2*(maxVal - minVal);
                if (t < m)
                    m = t;
                p1--;
                // 轮到p3
                p3++;
            }
        }
        else if (S2[p2] == minVal && S3[p3] != S2[p2]) {
            if (p2 == n2 - 1)  break;
            p2++;
        } 
        else if (S2[p2] == minVal && S2[p2] == S3[p3]) {  // 此时最小值a和中间值b相同，不能直接移动其中一个，而是要二者都尝试一下
            if (p2 == n2 - 1 && p3 != n3 - 1) p3++;
            else if (p2 != n2 - 1 && p3 == n2 - 1) p2++;
            else {
                // p1尝试一下
                p1++;
                minVal = min(min(S3[p1], S2[p3]), S3[p3]), maxVal = max(max(S3[p1], S2[p3]), S3[p3]);
                int t = 2*(maxVal - minVal);
                if (t < m)
                    m = t;
                p1--;
                // 轮到p3
                p3++;
            }
        }
        else{
            if (p3 == n3 - 1)  break;
            p3++;
        }
        // 重新计算更新后的最小值最大值，看要不要更新当前最小距离
        minVal = min(min(S1[p1], S2[p2]), S3[p3]), maxVal = max(max(S1[p1], S2[p2]), S3[p3]);
        int t = 2*(maxVal - minVal);
        if (t < m)
            m = t;
    }
    return m;
}
（3）
时间复杂度O（n），空间复杂度O（1）