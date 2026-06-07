#include<stdio.h>

struct Student{
    int no;         // 学号
    char name[12];  // 姓名
    short age;      // 年龄
    struct Student *first; // 第一个后继结点的首地址
    struct Student *second; // 第二个后继结点的首地址
};



int main() {

    struct Student s4 = {
        4,
        "王五",
        18,
        NULL,
        NULL
    };

    struct Student s3 = {
        3,
        "李四",
        20,
        NULL,
        NULL
    };

    struct Student s2 = {
        2,
        "张三",
        17,
        &s3,
        NULL
    };

    struct Student s1 = {
        1,
        "老汤",
        18,
        &s2,
        &s3
    };
    

    struct Student s[6];

    printf("%s\n", s1.second->name);

    return 1;
}