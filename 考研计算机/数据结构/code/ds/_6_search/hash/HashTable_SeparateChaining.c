
#include "../linear_list/SequentialSearch_LinkList.c"

// 基于链地址法的散列表
typedef struct {
    int n;      // 散列表中键值对的数量
    int m;      // 散列表的大小
    SSTable *st;    //  m 个单链表实现的顺序查找表
} HashTable;

// 初始化散列表，其长度为 m
void InitHashTable(HashTable *ht, int m) {
    ht->m = m;
    ht->n = 0;

    // 初始化 m 个单链表实现的顺序查找表
    ht->st = (SSTable *) malloc (m * sizeof(SSTable));
    for (int i = 0; i < m; i++) {
        InitSSTable(&ht->st[i]);
    }
}

// 销毁查找表
void DestroyHashTable(HashTable *ht) {
    for (int i = 0; i < ht->m; i++) {
        DestroySSTable(ht->st[i]);
    }
}

// 散列函数：计算 key 的散列地址
// 时间复杂度：O(1)
int Hash(int m, KeyType key) {
    // 将 key 取绝对值，再和散列表长 m 求模
    return abs(key) % m;
}

// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
// 时间复杂度：O(1) 
ValueType GetHashTable(HashTable *ht, KeyType key) {
    // 拿到 key 的散列地址
    int i = Hash(ht->m, key);
    // 去下标为 i 的单链表中，顺序查找 key
    return GetSSTable(ht->st[i], key);
}

// 扩容操作
void resize(HashTable *ht, int newSize) {
    // 创建新的顺序查找表数组，并初始化，长度是之前的 2 倍
    SSTable *newST = (SSTable *) malloc (newSize * sizeof(SSTable));
    for (int i = 0; i < newSize; i++) {
        InitSSTable(&newST[i]);
    }

    // 遍历旧散列表中的所有键值对
    for (int i = 0; i < ht->m; i++) {
        Node *curr = ht->st[i]->next;
        while (curr) {
            // 重新计算 key 对应的散列地址
            int hash = Hash(newSize, curr->key);
            // 插入到新的散列表中
            PutSSTable(newST[hash], curr->key, curr->value);
            curr = curr->next;
        }
        DestroySSTable(ht->st[i]);
    }
    free(ht->st);

    // 将散列表的数组地址指向新的散列表
    ht->m = newSize;
    ht->st = newST;
}

// 将键值对存入表中
// 时间复杂度：O(1) 
void PutHashTable(HashTable *ht, KeyType key, ValueType value) {
    // 保证散列表的装载因子不会超过 0.5
    if (ht->n >= ht->m / 2) resize(ht, 2 * ht->m);
    int i = Hash(ht->m, key);
    if (PutSSTable(ht->st[i], key, value)) ht->n++;
}

// 从表中删除键 key (对应的值也删掉)
// 时间复杂度：O(1) 
void DeleteHashTable(HashTable *ht, KeyType key) {
    int i = Hash(ht->m, key);
    if (DeleteSStable(ht->st[i], key)) ht->n--;
}

int main() {
    HashTable table;
    InitHashTable(&table, 10);

    PutHashTable(&table, 10, "laotang");
    PutHashTable(&table, 12, "douma");
    PutHashTable(&table, 13, "algo");

    printf("key = 12, value = %s\n", GetHashTable(&table, 12)); // 打印 douma

    PutHashTable(&table, 12, "data structure");
    PutHashTable(&table, 33, "gggg");
    PutHashTable(&table, 55, "666");
    PutHashTable(&table, 66, "yyyy");
    PutHashTable(&table, 77, "aaaaa");
    printf("key = 12, value = %s\n", GetHashTable(&table, 12)); // 打印 data structure

    DeleteHashTable(&table, 12);
    printf("key = 12, value = %s\n", GetHashTable(&table, 12)); // 打印空

    DestroyHashTable(&table);

    return 0;
}