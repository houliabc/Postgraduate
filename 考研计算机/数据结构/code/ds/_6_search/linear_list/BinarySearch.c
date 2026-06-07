#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int KeyType;
typedef char* ValueType;

typedef struct {
    KeyType key;        // 关键字
    ValueType value;    // 值
} ElemType;

// 基于顺序表的有序查找表
typedef struct {
    ElemType *data;     // key 升序的数组
    int capacity;       // 容量大小
    int length;         // 键值对数量
} BSTable;

// 初始化查找表
void InitBSTable(BSTable *table, int capacity) {
    table->data = (ElemType *) malloc (sizeof(ElemType) * capacity);
    table->length = 0;
    table->capacity = capacity;
}

// 销毁查找表
void DestroyBSTable(BSTable *table) {
    free(table->data);
}

// 折半查找
// 在查找表中，查找指定 key 对应的下标
// 时间复杂度：O(logn)
int BinarySearch(BSTable *table, KeyType key) {
    int low = 0, high = table->length - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key < table->data[mid].key) high = mid - 1;
        else if (key > table->data[mid].key) low = mid + 1;
        else return mid;
    }

    // key 不存在，则返回比 key 小的关键字的数量
    // 如果这个关键字要插入的话，那么就是插入在这个位置上
    return low;
}

// 时间复杂度：O(logn)
// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
ValueType Get(BSTable *table, KeyType key) {
    // 找到这个 key 对应的下标
    int i = BinarySearch(table, key);
    if (i < table->length && table->data[i].key == key) 
        return table->data[i].value;
    return NULL;
}

// 将键值对存入表中
// 时间复杂度：O(n)
void Put(BSTable *table, KeyType key, ValueType value) {
    // 找到这个 key 对应的下标
    int i = BinarySearch(table, key);

    // 如果 key 存在，那么直接修改对应的值
    if (i < table->length && table->data[i].key == key) {
        free(table->data[i].value);
        table->data[i].value = strdup(value);
        return;
    }

    // 如果查找表满了，不做插入操作
    if (table->length == table->capacity) return;

    // 如果 key 不存在，那么插入到相应的位置上
    for (int j = table->length; j > i; j--)
        table->data[j] = table->data[j - 1];

    table->data[i].key = key;
    table->data[i].value = strdup(value);

    table->length++;
}

// 从表中删除键 key (对应的值也删掉)
// 时间复杂度：O(n)
void Delete(BSTable *table, KeyType key) {
    // 找到这个 key 对应的下标
    int i = BinarySearch(table, key);

    // 如果 key 存在，那么删除这个键值对
    if (i < table->length && table->data[i].key == key) {
        // bug fix：先释放要删除键值对的值的内存
        free(table->data[i].value);
        for (int j = i; j < table->length - 1; j++)
            table->data[j] = table->data[j + 1];
         table->length--;
    }
}

int main() {
    BSTable table;
    InitBSTable(&table, 30);

    Put(&table, 10, "laotang");
    Put(&table, 12, "douma");
    Put(&table, 13, "algo");
    Put(&table, 8, "os");
    Put(&table, 2, "net");

    printf("key = 8, value = %s\n", Get(&table, 8));
    printf("key = 12, value = %s\n", Get(&table, 12));

    Put(&table, 12, "data structure");
    printf("key = 12, value = %s\n", Get(&table, 12));

    Delete(&table, 12);
    printf("key = 12, value = %s\n", Get(&table, 12));
    printf("key = 8, value = %s\n", Get(&table, 8));
    printf("key = 2, value = %s\n", Get(&table, 2));
    printf("key = 8, value = %s\n", Get(&table, 8));

    return 0;
}