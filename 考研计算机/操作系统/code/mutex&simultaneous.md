————————综合题一——————————
20-43
```c
https://houlir2.dpdns.org/2026/05/4062f411a47987da4550e5a73e50163c.png
semaphore sem_AC=0; // 用于表示操作A和C的执行顺序
semaphore sem_BC=0; // 用于表示操作B和C的执行顺序
semaphore sem_CE=0; // 用于表示操作C和E的执行顺序
semaphore sem_DE=0; // 用于表示操作D和E的执行顺序
A() {
    A的操作;
    V(sem_AC);
}
B() {
    B的操作;
    V(sem_BC);
}
C() {
    P(sem_AC);
    P(sem_BC);
    C的操作;
    V(sem_CE);
}
D() {
    D的操作;
    V(sem_DE);
}
E() {
    P(sem_CE);
    P(sem_DE);
    E的操作;
}
```

20-43
```c
semaphore sem_AC=0; // 用于表示操作A和C的执行顺序
semaphore sem_BC=0; // 用于表示操作B和C的执行顺序
semaphore sem_CD=0; // 用于表示操作C和D的执行顺序
semaphore sem_CE=0; // 用于表示操作C和E的执行顺序
semaphore sem_EF=0; // 用于表示操作E和F的执行顺序
A() {
    A的操作;
    V(sem_AC);
}
B() {
    B的操作;
    V(sem_BC);
}
C() {
    P(sem_AC);
    P(sem_BC);
    C的操作;
    V(sem_CD);
    V(sem_CE);
}
D() {
    P(sem_CD);
    D的操作;
}
E() {
    P(sem_CE);
    E的操作;
    V(sem_EF);
}
F() {
    P(sem_EF);
    F的操作;
}
```

————————综合题二——————————
09-45
```c
semaphore mutex=1; // 用于控制P1,P2和P3互斥访问缓存区
semaphore empty=N; // 表示缓存区中空单元的数量
semaphore even=0; // 表示缓存区中偶数数量
semaphore odd=0; // 表示缓存区中奇数数量
P1() {
    while (1) {
        int i = produce();
        P(empty);
        P(mutex);
        put(i);
        V(mutex);
        if (i % 2 == 0) // 偶数
            V(even);
        else  // 奇数
            V(odd);
    }
}
P2() {
    while (1) {
        P(odd);
        P(mutex);
        getodd();  // 取出一个奇数
        countodd();  // 统计奇数个数
        V(mutex);
        V(empty);
    }
}
P3() {
    while (1) {
        P(even);
        P(mutex);
        geteven();  // 取出一个偶数
        counteven();  // 统计偶数个数
        V(mutex);
        V(empty);
    }
}
```

11-45
```c
semaphore empty=10; // 表示供客户等待的座位
semaphore num=1; // 用于控制顾客互斥访问取号机
semaphore server=0; // 营业员等待顾客的同步
semaphore customer=0; // 顾客等待叫号的同步

cobegin {
    process 顾客 i {
        P(empty);
        P(num);
        从取号机获取一个号码;
        V(num);

        V(customer);
        等待叫号;

        P(server);
        获取服务;
        V(empty);
    }

    process 营业员 {
        while (TRUE) {
            P(customer);
            叫号;
            V(server);
            为客户服务;
        }
    }
} coend
```

————————综合题四——————————
13-45
```c
mutex=1：表示同时只能进门1个或出门一个人
empty=500：表示最多可容纳500人参观
full=0：表示当前已容纳了多少人
cobegin
    参观者进程 i:
    {
        P(empty);
        P(mutex);
        进门;
        V(mutex);
        V(full);
        参观
        P(full);
        P(mutex);
        出门;
        V(mutex);
        V(empty);
    }
coend
```

25-45
```c
mutex1=1：用于互斥访问铁楸
mutex2=1：用于互斥访问树坑
mutex3=1：用于互斥访问树苗
mutex4=1：用于互斥访问水桶
empty1=n：表示最多可以有n个树坑
empty2=m：表示最多可以有m个树苗
full1=0：表示当前已有几个树坑
full2=0：表示当前已有几个树苗
甲() {
    if(full1 < 3) {
        wait(mutex1);
        拿铁楸;
        wait(empty1);
        wait(mutex2);
        挖树坑;
        signal(mutex2);
        signal(mutex1);
    }
}
乙() {
    //1.拿到树苗
    wait(empty2);
    wait(mutex3);
    拿树苗;
    signal(mutex3);
    signal(full2);

    // 2.放入树坑
    wait(empty1);
    wait(mutex2);
    把树苗放入树坑
    signal(mutex2);
    signal(full1);

    //3.填土
    wait(mutex1);
    拿铁楸填土;
    signal(mutex1);
}
丙() {
    wait(mutex4);
    拿水桶给树苗浇水;
    signal(mutex4);
}
```

————————综合题五——————————
7-46
mutexX=1：表示互斥访问全局变量x
mutexY=1：表示互斥访问全局变量y
mutexZ=1：表示互斥访问全局变量z
```c
thread1() {
    cnum w;
    P(mutexX);
    P(mutexY);
    w = add(x, y);
    V(mutexX);
    V(mutexY);
    ...
}

thread2() {
    cnum w;
    P(mutexZ);
    P(mutexY);
    w = add(y, z);
    V(mutexZ);
    V(mutexY);
    ...
}

thread3() {
    cnum w;
    w.a = 1;
    w.b = 1;
    P(mutexZ);
    z = add(z, w);
    V(mutexZ);
    P(mutexY);
    y = add(y, w);
    V(mutexY);
    ...
}
```

24-46
```c
（1）
实现C1的代码为临界区，因为写操作需要互斥访问，否则会引发数据不一致的问题。
(2)
semaphore rw_mutex = 1; //控制读者和写者互斥访问临界资源
int reader_count=0; // 记录多少读者在访问临界资源
semaphore r_mutex = 1; // 控制多个读者互斥访问全局变量reader_count
P1() {  //写者
    while(true) {
        wait(rw_mutex); // 和读者互斥访问临界资源
        C1();
        signal(rw_mutex);
    }
}

P2() {  //读者
    while(true) {
        wait(r_mutex); // 互斥修改reader_count
        reader_count++;
        if (reader_count == 1)
            wait(rw_mutex);  // 表示第一个读者和写者互斥访问临界资源
        signal(reader_count);
        C2();
        wait(r_mutex);
        reader_count--;
        if (reader_count == 0)
            signal(rw_mutex); // 最后一个读者释放读写锁
        signal(r_mutex);
    }
}

(3)
semaphore rw_mutex = 1; //互斥访问临界资源
P1() {  
    while(true) {
        wait(rw_mutex); 
        C3();
        signal(rw_mutex);
    }
}

P2() {  
    while(true) {
        wait(rw_mutex); 
        C3();
        signal(rw_mutex);
    }
}

————————综合题六——————————
19-43
```c
semaphore chopsticks[n];  // 每个信号量用来控制哲学家互斥访问对应的筷子
// semaphore bowls[m];  // 每个信号量用来控制哲学家互斥访问对应的碗
void init() {
    for (int i = 0; i < n; i++)
        chopsticks[i] = 1;
    // for (int i = 0; i < m; i++)
    //     bowls[i] = 1;
}

// 哲学家i的活动过程
void philosophers(int i) {
    while (true) {
        thinking();

        if (i % 2 == 1) {
            // 先拿左边的筷子
            wait(chopsticks[i]);
            wait(chopsticks[(i+1)%n]);// 拿右边的筷子
        } else {
            wait(chopsticks[(i+1)%n]);// 拿右边的筷子
            wait(chopsticks[i]);  // 左边筷子
        }

        eating();

        signal(chopsticks[i]);
        signal(chopsticks[(i+1)%n]);
    }
}