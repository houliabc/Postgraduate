#ifndef SEARCH_H

#define SEARCH_H

#include <stdbool.h>

// 定义关键字的类型为整型
typedef int KeyType;
// 定义值的类型为字符串
typedef char* ValueType;

// 定义查找表 (Search Table)，维护所有键值对的数据
typedef struct {
    // TODO
    // 不同业务的表使用不同数据结构来维护键值对数据
} STable;

// 初始化查找表
void InitSTable(STable *ST);

// 销毁查找表
void DestroySTable(STable *ST);

// 获取键 key 对应的值（若 key 不存在，则返回 NULL）
ValueType Get(STable *ST, KeyType key);

// 将键值对存入表中
void Put(STable *ST, KeyType key, ValueType value);

// 从表中删除键 key (对应的值也删掉)
void Delete(STable *ST, KeyType key);

// 键 key 在表中是否有对应的值
bool Contains(STable *ST, KeyType key);

// 判断表是否为空
bool IsEmpty();

// 表中键值对的数量
int Size();

#endif