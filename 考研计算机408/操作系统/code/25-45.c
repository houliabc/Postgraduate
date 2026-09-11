sema full = 0;  // 表示树坑数量
sema empty = 2;  // 表示树坑数量小于3时才能新增树坑（树坑数量限制）
sema spade = 1;  // 互斥访问铁楸
sema finish = 0;  // 表示当前需要浇水的树苗数

甲() {
    while (1) {
        P(empty);
        P(spade);
        挖树坑;
        V(spade);
        V(full);
    }
}
乙() {
    while (1) {
        P(full);
        树苗放入树坑;
        P(spade);
        填土;
        V(spade);
        V(empty);  // 填上土就少一个树坑了
        V(finish);
    }
}
丙() {
    while (1) {
        P(finish);
        给新种树苗浇水;
    }
}