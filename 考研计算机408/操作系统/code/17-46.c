// 复数的结构类型定义
typedef struct {
    float a;
    float b;
} cnum;

cnum x, y, z; // 全局变量

// 计算两个复数之和
cnum add(cnum p, cnum q) {
    cnum s;
    s.a = p.a + q.a;
    s.b = p.b + q.b;
    return s;
}
sema mutex_y = 1; // 互斥访问变量y
sema mutex_z = 1; // 互斥访问变量z

thread1() {
    cnum w;
    P(mutex_y);
    w = add(x, y);
    V(mutex_y);
    ...
}

thread2() {
    cnum w;
    P(mutex_y);
    P(mutex_z);
    w = add(y, z);
    V(mutex_y);
    V(mutex_z);
    ...
}

thread3() {
    cnum w;
    w.a = 1;
    w.b = 1;
    P(mutex_z);
    z = add(z, w);
    V(mutex_z);
    P(mutex_y);
    y = add(y, w);
    V(mutex_y);
}
