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