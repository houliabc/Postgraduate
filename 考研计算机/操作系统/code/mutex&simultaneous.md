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
        V(mutex);
        V(empty);
        countodd();  // 统计奇数个数
    }
}
P3() {
    while (1) {
        P(even);
        P(mutex);
        geteven();  // 取出一个偶数
        V(mutex);
        V(empty);
        counteven();  // 统计偶数个数
    }
}
```

11-45
https://houlir2.dpdns.org/2026/05/311bf5025755126a1cf6be469f794c8e.png
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
    }

    process 营业员 {
        while (TRUE) {
            P(customer);
            叫号;
            V(server);
            V(empty);
            为客户服务;
        }
    }
} coend
```

————————综合题三——————————
14-47
```c
mutex=1：用来控制生产者和消费者互斥访问缓冲区
empty=1000：表示缓存区最多可容纳1000件产品
full=0：表示缓存区当前已容纳多少件产品
mutex2=1：用来控制一个消费者连续取出10件产品
producer_i() {
    生产1件产品;
    P(empty);
    P(mutex);
    放入1件产品;
    V(mutex);
    V(full);
}
consumer_i() {
    P(mutex2);
    for (int i = 0; i < 10; i++) {
        P(full);
        P(mutex);
        取出1件产品;
        V(mutex);
        V(empty);
    }
    V(mutex2);
}
```

15-45
```c
// 本题中A、B信箱各为一个缓存区，需要对应的两个互斥锁，同时还要在A、B之间加上同步操作（用来控制先后顺序）
mutexA=1：用来控制A和B互斥访问邮箱A
mutexB=1：用来控制A和B互斥访问邮箱B
emptyA=M-x：用于表示A邮箱还能放多少个邮件
emptyB=N-y：用于表示B邮箱还能放多少个邮件
fullA=x：用于表示A邮箱当前的邮件数
fullB=y：用于表示B邮箱当前的邮件数
CoBegin
    A {
        while (TRUE) {
            P(fullA);
            P(mutexA);
            从 A 的信箱中取出一个邮件;
            V(mutexA);
            V(emptyA);

            回答问题并提出一个新问题;

            P(emptyB);
            P(mutexB);
            将新邮件放入 B 的信箱;
            V(mutexB);
            V(fullB);
        }
    }

    B {
        while (TRUE) {
            P(fullB);
            P(mutexB);
            从 B 的信箱中取出一个邮件;
            V(mutexB);
            V(emptyB);

            回答问题并提出一个新问题;

            P(emptyA);
            P(mutexA);
            将新邮件放入 A 的信箱;
            V(mutexA);
            V(fullA);
        }
    }
CoEnd
```

————————综合题四——————————
13-45
```c
mutex=1：表示同时只能进门1个或出门一个人
empty=500：表示最多可容纳500人参观
cobegin
    参观者进程 i:
    {
        P(empty);
        P(mutex);
        进门;
        V(mutex);

        参观

        P(mutex);
        出门;
        V(mutex);
        V(empty);
    }
coend
```

25-45
```c
// 典型的生产者和消费者（需要while无限循环），甲乙作为生产者，丙作为消费者，需要用互斥表示树坑数量，以及同步来控制三者执行的先后顺序
https://houlir2.dpdns.org/2026/05/54126d960d7119c3b53adcc08881c79c.png
mutex1=1：用于控制甲、乙互斥访问铁楸
mutex2=1：用于控制甲、乙互斥访问树坑  // 多余的树坑操作
empty=3：表示最多可以有3个树坑
full=0：表示当前已有几个树坑
sem=0：控制乙丙操作的顺序
甲() {
    while(1) {
        P(empty);
        P(mutex1);
        P(mutex2);   // 多余的树坑操作
        挖树坑
        V(mutex2);
        V(mutex1);
        V(full);  // 通知乙可以放树苗了
    }
}
乙() {
    while(1) {
        P(full);
        P(mutex2);
        将树苗放入树坑
        V(mutex2);

        P(mutex1);
        填土
        V(mutex1);

        V(empty);  // 通知甲可以挖坑了
        V(sem);  // 通知丙，可以浇水了
    }
}
丙() {
    while(1) {
        P(sem);  // 等待丙填土完
        浇水
    }
}
```

————————综合题五——————————
17-46
```c
// 本题中x只有读操作，不需要互斥，y分别在线程1、3和线程2、3之间发生互斥，z在线程2、3之间发生互斥。w是局部变量，不用管
mutexY=1：表示互斥访问全局变量y
mutexZ=1：表示互斥访问全局变量z
thread1() {
    cnum w;
    P(mutexY);
    w = add(x, y);
    V(mutexY);
    ...
}

thread2() {
    cnum w;
    P(mutexZ);
    P(mutexY);
    w = add(y, z);
    V(mutexY);
    V(mutexZ);
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
semaphore full = 0; // 用来控制读者是否可以访问缓冲区
P1() {  //写者
    C1();
    signal(full);
}

P2() {  //读者
    wait(full);
    C2();
}

(3)
semaphore rw_mutex = 1; //互斥访问缓存区
P1() {  
    wait(rw_mutex);
    C3();
    signal(rw_mutex);
}

P2() {  
    wait(rw_mutex);
    C3();
    signal(rw_mutex);
}

————————综合题六——————————
19-43
```c
semaphore chopsticks[n];  // 每个信号量用来控制哲学家互斥访问对应的筷子
semaphore bowls=m;  // 用来表示碗的数量
void init() {
    for (int i = 0; i < n; i++)
        chopsticks[i] = 1;
}

// 哲学家i的活动过程
void philosophers(int i) {
    while (true) {
        thinking();

        wait(bowls);
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
        signal(bowls);
    }
}