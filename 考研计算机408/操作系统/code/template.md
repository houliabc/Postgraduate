14-47
```c
信号量：
mutex=1：用来互斥访问环形缓冲区
empty=1000：表示当前缓冲区的空闲位置
full=0：表示当前缓冲区的使用个数

producer_i() {   // 生产者i
    生产产品
    P(empty);
    P(mutex);
    放入生成的产品进入缓冲区
    V(mutex);
    V(full);
}

consumer_i() {   // 消费者i
    // 消费者连续取出10件产品后，其他消费者才能取产品
    for (int i = 0; i < 10; i++) {
        P(full);
        P(mutex);
        取走一件商品
        V(mutex);
        V(empty);
    }
}