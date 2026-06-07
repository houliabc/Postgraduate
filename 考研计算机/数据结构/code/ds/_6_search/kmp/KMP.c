#include <stdio.h>

// 对 next 修正，得到修正之后的 nextval
void GetNextVal(char* p, int m, int next[], int nextval[]) {
    nextval[1] = next[1];
    for (int j = 2; j <= m; j++) {
        if (p[j] == p[next[j]]) 
            nextval[j] = nextval[next[j]];
        else 
            nextval[j] = next[j];
    }
}

void GetNextVal_2(char* p, int m, int nextval[]) {
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < m) {
        if (j == 0 || p[i] == p[j]) {
            ++i;
            ++j;
            if (p[i] != p[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
}

void GetNext(char* p, int m, int next[]) {
    int i = 1, j = 0;
    next[1] = 0;
    while (i < m) {
        if (j == 0 || p[i] == p[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// s 和 p 的第一个元素都没有用到，而是从下标为 1 的元素开始的
int IndexOf(char *s, int n, char *p, int m) {

    int next[m];
    GetNext(p, m, next);

    int i = 1, j = 1;
    while (i < n && j < m) {
        if (j == 0 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            // i 不动
            // j 回退到 next[j]
            j = next[j];
        }
    }
    if (j == m) return i - m + 1;
    else return -1;
}

int main() {
    char s[] = "-bacbababaababac";
    char p[] = "-ababac";
    printf("%d\n", IndexOf(s, 16, p, 7));
    return 0;
}