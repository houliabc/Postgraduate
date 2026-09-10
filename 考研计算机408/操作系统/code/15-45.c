CoBegin
    sema A_empty = M;  // 表示A信箱还可放入多少个邮件
    sema A_full = 0;  // A信箱已放入多少邮件
    sema B_empty = N;  // 表示B信箱还可放入多少个邮件
    sema B_full = 0;  // B信箱已放入多少邮件
    sema A_mutex = 1;  // 用于互斥访问A邮箱
    sema B_mutex = 1;  // 用于互斥访问B邮箱
    A{
        while (TRUE) {
            P(A_full);
            P(A_mutex);
            从 A 的信箱中取出一个邮件;
            V(A_mutex);
            V(A_empty);
            回答问题并提出一个新问题;
            P(B_empty);
            P(B_mutex);
            将新邮件放入 B 的信箱;
            V(B_mutex);
            V(B_full);
        }
    }

    B{
        while (TRUE) {
            P(B_full);
            P(B_mutex);
            从 B 的信箱中取出一个邮件;
            V(B_mutex);
            V(B_empty);
            回答问题并提出一个新问题;
            P(A_empty);
            P(A_mutex);
            将新邮件放入 A 的信箱;
            V(A_mutex);
            V(A_full);
        }
    }
CoEnd
