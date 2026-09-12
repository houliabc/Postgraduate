（2）
sema empty = 1; // 表示缓冲区B当前是否为空
sema full = 0;  // 表示当前缓冲区B是否有内容
P1() {
    wait(empty);
    C1();
    V(full);
}
P2() {
    wait(full);
    C2();
    V(empty);
}

（3）
sema mutex = 1;  // 互斥访问缓冲区B
P1() {
    wait(mutex);
    C3();
    V(mutex);
}
P2() {
    wait(mutex);
    C3();
    V(mutex);
}