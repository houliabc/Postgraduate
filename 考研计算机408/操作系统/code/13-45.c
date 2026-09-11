cobegin
    sema mutex = 1;  // 互斥出入口，一次只允许一个人通过
    sema empty = 500;  // 表示当前还可容纳多少人参观
    sema full = 0;  // 表示当前已有多少人参观 
    参观者进程  i:
    {
        …
        P(empty);
        P(mutex);
        进门;
        V(mutex);
        V(full);
        …
        参观;
        …
        P(full);
        P(mutex);
        出门;
        V(mutex);
        V(empty);
        …
    }
coend
