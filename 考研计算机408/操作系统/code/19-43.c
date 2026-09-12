sema eaters = n-1; // 用于限制同时可就餐的哲学家个数
sema bowls = m;  // 有m个碗
sema chopsticks[n];  // n个筷子

哲学家i() {
    while (1) {
        思考();

        P(eaters);
        P(bowls);
        P(chopsticks[i]);
        P(chopsticks[(i+1)%n]);
        就餐();
        V(chopsticks[i]);
        V(chopsticks[(i+1)%n]);
        V(bowls);
        V(eaters);
    }
}