#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define m 3                             // B-树的阶，暂设为 3

typedef int KeyType;
typedef char* ValueType;

// B-树结点
typedef struct BTNode {
   int n;                          // 结点中存储关键字的个数
   bool leaf;                      // 结点是否是叶子结点
   struct BTNode *parent;          // 指向双亲结点
   KeyType *keys;                 // 存储所有关键字
   ValueType *values;             // 关键字对应的 value
   struct BTNode **ptr;           // 存储所有子树的指针
} BTNode, *BTree;                 // B-树的类型

// 搜索 B-树中的关键字
bool SearchBTree(BTree T, KeyType key, ValueType *value) {
    if (T == NULL) return false;
    
    int i = 0;
    // 找到第一个不小于 key 的关键字
    while (i < T->n && key > T->keys[i]) i++;
    
    // 如果找到关键字
    if (i < T->n && key == T->keys[i]) {
        *value = T->values[i];
        return true;
    }
    
    // 如果是叶子节点，未找到关键字
    if (T->leaf) return false;
    
    // 递归搜索子树
    return SearchBTree(T->ptr[i], key, value);
}

// 创建新的B-树节点
BTree CreateNode(bool leaf) {
    BTree node = (BTree)malloc(sizeof(BTNode));
    node->n = 0;
    node->leaf = leaf;
    node->parent = NULL;
    
    // 分配关键字和值数组
    node->keys = (KeyType*)malloc((m-1) * sizeof(KeyType));
    node->values = (ValueType*)malloc((m-1) * sizeof(ValueType));
    
    // 分配子节点指针数组
    if (!leaf) {
        node->ptr = (BTree*)malloc(m * sizeof(BTree));
        for (int i = 0; i < m; i++) {
            node->ptr[i] = NULL;
        }
    } else {
        node->ptr = NULL;
    }
    
    return node;
}

// 初始化 B-树
BTree InitBTree() {
    BTree T = CreateNode(true);
    if (T == NULL) {
        return NULL;
    }
    
    T->n = 0;
    return T;
}

// 分裂子节点
void SplitChild(BTree parent, int index, BTree child) {
    // 创建新节点，用于存储后半部分关键字
    BTree newNode = CreateNode(child->leaf);
    newNode->n = (m-1) / 2;
    
    // 复制后半部分关键字到新节点
    for (int j = 0; j < newNode->n; j++) {
        newNode->keys[j] = child->keys[j + (m+1)/2];
        newNode->values[j] = child->values[j + (m+1)/2];
    }
    
    // 如果不是叶子节点，复制后半部分子节点指针
    if (!child->leaf) {
        for (int j = 0; j <= newNode->n; j++) {
            newNode->ptr[j] = child->ptr[j + (m+1)/2];
            if (newNode->ptr[j] != NULL) {
                newNode->ptr[j]->parent = newNode;
            }
        }
    }
    
    // 更新原节点的关键字数量
    child->n = (m-1) / 2;
    
    // 在父节点中为中间关键字腾出位置
    for (int j = parent->n; j > index; j--) {
        parent->ptr[j+1] = parent->ptr[j];
    }
    
    // 连接新节点
    parent->ptr[index+1] = newNode;
    newNode->parent = parent;
    
    // 在父节点中插入中间关键字
    for (int j = parent->n-1; j >= index; j--) {
        parent->keys[j+1] = parent->keys[j];
        parent->values[j+1] = parent->values[j];
    }
    
    parent->keys[index] = child->keys[(m-1)/2];
    parent->values[index] = child->values[(m-1)/2];
    parent->n++;
}

// 在非满节点中插入关键字
void InsertNonFull(BTree node, KeyType key, ValueType value) {
    int i = node->n - 1;
    
    // 如果是叶子节点，直接插入
    if (node->leaf) {
        // 找到关键字应该插入的位置
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i+1] = node->keys[i];
            node->values[i+1] = node->values[i];
            i--;
        }
        
        // 插入关键字和对应的值
        node->keys[i+1] = key;
        node->values[i+1] = value;
        node->n++;
    } else {
        // 找到应该插入的子树
        while (i >= 0 && node->keys[i] > key) i--;
        i++;
        
        // 如果子节点已满，先分裂
        if (node->ptr[i]->n == m-1) {
            SplitChild(node, i, node->ptr[i]);
            
            // 确定应该插入哪个子树
            if (node->keys[i] < key) i++;
        }
        
        // 递归插入到子树中
        InsertNonFull(node->ptr[i], key, value);
    }
}


// 插入关键字到B-树
bool InsertBTree(BTree *T, KeyType key, ValueType value) {
    BTree root = *T;
    
    // 如果树为空，创建新节点
    if (root == NULL) {
        *T = CreateNode(true);
        root = *T;
    }
    
    // 如果根节点已满，需要分裂
    if (root->n == m-1) {
        BTree newRoot = CreateNode(false);
        *T = newRoot;
        newRoot->ptr[0] = root;
        root->parent = newRoot;
        
        SplitChild(newRoot, 0, root);
        
        // 确定应该插入哪个子树
        int i = 0;
        if (newRoot->keys[0] < key) i++;
        
        InsertNonFull(newRoot->ptr[i], key, value);
    } else {
        // 根节点未满，直接插入
        InsertNonFull(root, key, value);
    }
    
    return true;
}

// 在节点中查找关键字的索引
int FindKeyIndex(BTree node, KeyType key) {
    int index = 0;
    while (index < node->n && node->keys[index] < key) {
        index++;
    }
    return index;
}

// 获取节点的前驱关键字
void GetPredecessor(BTree node, int index, KeyType *key, ValueType *value) {
    BTree current = node->ptr[index];
    while (!current->leaf) {
        current = current->ptr[current->n];
    }
    
    *key = current->keys[current->n-1];
    *value = current->values[current->n-1];
}

// 获取节点的后继关键字
void GetSuccessor(BTree node, int index, KeyType *key, ValueType *value) {
    BTree current = node->ptr[index+1];
    while (!current->leaf) {
        current = current->ptr[0];
    }
    
    *key = current->keys[0];
    *value = current->values[0];
}

// 合并两个节点
void MergeNodes(BTree parent, int index, BTree left, BTree right) {
    // 将父节点的关键字和右子节点的内容合并到左子节点
    left->keys[(m-1)/2] = parent->keys[index];
    left->values[(m-1)/2] = parent->values[index];
    
    for (int i = 0; i < right->n; i++) {
        left->keys[(m-1)/2 + 1 + i] = right->keys[i];
        left->values[(m-1)/2 + 1 + i] = right->values[i];
    }
    
    // 如果不是叶子节点，复制子节点指针
    if (!left->leaf) {
        for (int i = 0; i <= right->n; i++) {
            left->ptr[(m-1)/2 + 1 + i] = right->ptr[i];
            if (left->ptr[(m-1)/2 + 1 + i] != NULL) {
                left->ptr[(m-1)/2 + 1 + i]->parent = left;
            }
        }
    }
    
    // 更新左子节点的关键字数量
    left->n = m - 1;
    
    // 从父节点中删除关键字
    for (int i = index; i < parent->n - 1; i++) {
        parent->keys[i] = parent->keys[i+1];
        parent->values[i] = parent->values[i+1];
        parent->ptr[i+1] = parent->ptr[i+2];
    }
    
    parent->n--;
    
    // 释放右子节点的内存
    free(right->keys);
    free(right->values);
    if (!right->leaf) {
        free(right->ptr);
    }
    free(right);
}

// 删除辅助函数
bool DeleteBTreeHelper(BTree node, KeyType key) {
    int index = FindKeyIndex(node, key);
    
    // 关键字在当前节点中
    if (index < node->n && node->keys[index] == key) {
        // 如果是叶子节点，直接删除
        if (node->leaf) {
            for (int i = index; i < node->n - 1; i++) {
                node->keys[i] = node->keys[i+1];
                node->values[i] = node->values[i+1];
            }
            node->n--;
            return true;
        } else {
            // 如果不是叶子节点，处理内部节点的删除
            
            // 获取前驱关键字
            BTree predecessor = node->ptr[index];
            if (predecessor->n >= (m+1)/2) {
                KeyType predKey;
                ValueType predValue;
                GetPredecessor(node, index, &predKey, &predValue);
                
                // 用前驱关键字替换要删除的关键字
                node->keys[index] = predKey;
                node->values[index] = predValue;
                
                // 递归删除前驱关键字
                return DeleteBTreeHelper(predecessor, predKey);
            }
            
            // 获取后继关键字
            BTree successor = node->ptr[index+1];
            if (successor->n >= (m+1)/2) {
                KeyType succKey;
                ValueType succValue;
                GetSuccessor(node, index, &succKey, &succValue);
                
                // 用后继关键字替换要删除的关键字
                node->keys[index] = succKey;
                node->values[index] = succValue;
                
                // 递归删除后继关键字
                return DeleteBTreeHelper(successor, succKey);
            }
            
            // 如果前驱和后继节点都只有最小数量的关键字，合并
            MergeNodes(node, index, predecessor, successor);
            return DeleteBTreeHelper(predecessor, key);
        }
    } else {
        // 关键字不在当前节点中
        if (node->leaf) {
            return false; // 关键字不在树中
        }
        
        // 确定要查找的子树
        int childIndex = index;
        BTree child = node->ptr[childIndex];
        
        // 如果子节点关键字数量不足，需要调整
        if (child->n < (m+1)/2) {
            // 尝试从左兄弟借关键字
            if (childIndex > 0 && node->ptr[childIndex-1]->n >= (m+1)/2) {
                BTree leftSibling = node->ptr[childIndex-1];
                
                // 从父节点移动一个关键字到子节点
                for (int i = child->n; i > 0; i--) {
                    child->keys[i] = child->keys[i-1];
                    child->values[i] = child->values[i-1];
                }
                
                if (!child->leaf) {
                    for (int i = child->n + 1; i > 0; i--) {
                        child->ptr[i] = child->ptr[i-1];
                    }
                    child->ptr[0] = leftSibling->ptr[leftSibling->n];
                    if (child->ptr[0] != NULL) {
                        child->ptr[0]->parent = child;
                    }
                }
                
                child->keys[0] = node->keys[childIndex-1];
                child->values[0] = node->values[childIndex-1];
                
                // 从左兄弟移动一个关键字到父节点
                node->keys[childIndex-1] = leftSibling->keys[leftSibling->n-1];
                node->values[childIndex-1] = leftSibling->values[leftSibling->n-1];
                
                child->n++;
                leftSibling->n--;
            }
            // 尝试从右兄弟借关键字
            else if (childIndex < node->n && node->ptr[childIndex+1]->n >= (m+1)/2) {
                BTree rightSibling = node->ptr[childIndex+1];
                
                // 从父节点移动一个关键字到子节点
                child->keys[child->n] = node->keys[childIndex];
                child->values[child->n] = node->values[childIndex];
                
                if (!child->leaf) {
                    child->ptr[child->n+1] = rightSibling->ptr[0];
                    if (child->ptr[child->n+1] != NULL) {
                        child->ptr[child->n+1]->parent = child;
                    }
                    
                    for (int i = 0; i < rightSibling->n - 1; i++) {
                        rightSibling->ptr[i] = rightSibling->ptr[i+1];
                    }
                }
                
                // 从右兄弟移动一个关键字到父节点
                node->keys[childIndex] = rightSibling->keys[0];
                node->values[childIndex] = rightSibling->values[0];
                
                for (int i = 0; i < rightSibling->n - 1; i++) {
                    rightSibling->keys[i] = rightSibling->keys[i+1];
                    rightSibling->values[i] = rightSibling->values[i+1];
                }
                
                child->n++;
                rightSibling->n--;
            }
            // 如果左右兄弟都没有足够的关键字，合并
            else {
                if (childIndex > 0) {
                    BTree leftSibling = node->ptr[childIndex-1];
                    MergeNodes(node, childIndex-1, leftSibling, child);
                    child = leftSibling; // 更新child为合并后的节点
                } else {
                    BTree rightSibling = node->ptr[childIndex+1];
                    MergeNodes(node, childIndex, child, rightSibling);
                }
            }
        }
        
        // 递归删除子树中的关键字
        return DeleteBTreeHelper(child, key);
    }
}


// 从B-树中删除关键字
bool DeleteBTree(BTree *T, KeyType key) {
    if (*T == NULL) {
        return false;
    }
    
    // 调用辅助函数删除关键字
    bool result = DeleteBTreeHelper(*T, key);
    
    // 如果根节点没有关键字且有子节点，更新根节点
    if ((*T)->n == 0 && !(*T)->leaf) {
        BTree oldRoot = *T;
        *T = (*T)->ptr[0];
        (*T)->parent = NULL;
        
        free(oldRoot->keys);
        free(oldRoot->values);
        free(oldRoot->ptr);
        free(oldRoot);
    }
    
    return result;
}

// 打印B-树（用于调试）
void PrintBTree(BTree T, int depth) {
    if (T == NULL) {
        return;
    }
    
    // 打印缩进
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    // 打印节点关键字
    printf("Node (n=%d, leaf=%s): ", T->n, T->leaf ? "true" : "false");
    for (int i = 0; i < T->n; i++) {
        printf("%d(%s) ", T->keys[i], T->values[i]);
    }
    printf("\n");
    
    // 递归打印子节点
    if (!T->leaf) {
        for (int i = 0; i <= T->n; i++) {
            PrintBTree(T->ptr[i], depth + 1);
        }
    }
}

int main() {
    BTree T = InitBTree();
    
    // 插入测试
    printf("插入测试:\n");
    InsertBTree(&T, 10, "Ten");
    InsertBTree(&T, 20, "Twenty");
    InsertBTree(&T, 5, "Five");
    InsertBTree(&T, 6, "Six");
    InsertBTree(&T, 12, "Twelve");
    InsertBTree(&T, 30, "Thirty");
    InsertBTree(&T, 7, "Seven");
    InsertBTree(&T, 17, "Seventeen");
    
    PrintBTree(T, 0);
    
    // 查询测试
    printf("\n查询测试:\n");
    ValueType value;
    if (SearchBTree(T, 10, &value)) {
        printf("找到关键字 10: %s\n", value);
    } else {
        printf("未找到关键字 10\n");
    }
    
    if (SearchBTree(T, 15, &value)) {
        printf("找到关键字 15: %s\n", value);
    } else {
        printf("未找到关键字 15\n");
    }
    
    // 删除测试
    printf("\n删除测试:\n");
    printf("删除关键字 10\n");
    DeleteBTree(&T, 10);
    PrintBTree(T, 0);
    
    printf("\n删除关键字 20\n");
    DeleteBTree(&T, 20);
    PrintBTree(T, 0);
    
    // 释放内存
    // 实际应用中需要实现一个函数来递归释放所有节点的内存
    
    return 0;
}
    
    