#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef char* ValueType;

typedef struct {
    KeyType key;        // 关键字
    ValueType value;    // 值
} ElemType;

// 基于顺序表构建查找表
typedef struct {
    ElemType *data;     // 存储键值对数据的数组
    int capacity;       // 查找表的最大容量
    int length;         // 查找表中的键值对数量
} SSTable;

// 初始化查找表
void InitSSTable(SSTable *table, int capacity) {
    table->data = (ElemType *) malloc (sizeof(ElemType) * capacity);
    table->capacity = capacity;
    table->length = 0;
}

// 销毁查找表
void DestroySSTable(SSTable *table) {
    free(table->data);
}

// 时间复杂度：O(n)
// 在查找表中查找指定的 key，如果存在，则返回 key 所在顺序表中的位置，否则，返回 -1
int SeqSearch(SSTable *table, KeyType key) {
    // 顺序查找：从表的一端开始，依次将记录的关键字和给定值进行比较，若某个记录的关键字和给定值相等，则查找成功
    for (int i = 0; i < table->length; i++) { 
        if (table->data[i].key == key) 
            return i;
    }
    return -1;
}

// 时间复杂度：O(n)
// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
ValueType GetSSTable(SSTable *table, KeyType key) {
    int i = SeqSearch(table, key);
    if (i != -1) return table->data[i].value;
    return NULL;
}

// 时间复杂度：O(n)
// 将键值对存入表中
void PutSSTable(SSTable *table, KeyType key, ValueType value) {
    int i = SeqSearch(table, key);
    if (i != -1) {  // 如果 key 已经存在，则直接更新 value
        free(table->data[i].value);
        table->data[i].value = strdup(value);
        return;
    }

    // 如果查找表满了，直接返回
    if (table->length == table->capacity) return;

    // 将新的键值对插入到顺序表的最后
    table->data[table->length].key = key;
    table->data[table->length].value = strdup(value);
    table->length++;
}

// 时间复杂度：O(n)
// 从表中删除键 key (对应的值也删掉)
void DeleteSStable(SSTable *table, KeyType key) {
    int i = SeqSearch(table, key);
    // 如果 key 不存在，则直接返回
    if (i == -1) return;

    // bug fix：先释放要删除键值对的值的内存
    free(table->data[i].value);

    // 将下标为 i 后面的元素往前移动一个位置
    for (int j = i; j < table->length - 1; j++) {
        table->data[j] = table->data[j + 1];
    }

    table->length--;
}

int main() {

    SSTable table;
    InitSSTable(&table, 100);

    PutSSTable(&table, 10, "laotang");
    PutSSTable(&table, 12, "douma");
    PutSSTable(&table, 13, "algo");
    PutSSTable(&table, 8, "lisi");

    printf("key = 12, value = %s\n", GetSSTable(&table, 12)); // 打印 douma

    PutSSTable(&table, 12, "data structure");
    printf("key = 12, value = %s\n", GetSSTable(&table, 12)); // 打印 data structure

    DeleteSStable(&table, 12);
    printf("key = 12, value = %s\n", GetSSTable(&table, 12)); // 打印空

    DestroySSTable(&table);

    return 0;
}