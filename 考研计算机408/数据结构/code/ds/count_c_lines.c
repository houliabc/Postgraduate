#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// 哈希表节点结构
typedef struct HashNode {
    char filename[256];
    struct HashNode* next;
} HashNode;

// 哈希表结构
typedef struct {
    HashNode** table;
    int size;
} HashMap;

// 创建哈希表
HashMap* createHashMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->table = (HashNode**)calloc(size, sizeof(HashNode*));
    return map;
}

// 哈希函数
unsigned int hash(const char* str, int size) {
    unsigned int hashval = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hashval = str[i] + (hashval << 6) + (hashval << 16) - hashval;
    }
    return hashval % size;
}

// 检查文件名是否已存在于哈希表中
int containsKey(HashMap* map, const char* filename) {
    unsigned int index = hash(filename, map->size);
    HashNode* current = map->table[index];
    
    while (current != NULL) {
        if (strcmp(current->filename, filename) == 0) {
            return 1; // 已存在
        }
        current = current->next;
    }
    
    return 0; // 不存在
}

// 添加文件名到哈希表
void put(HashMap* map, const char* filename) {
    unsigned int index = hash(filename, map->size);
    
    // 创建新节点
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strncpy(newNode->filename, filename, sizeof(newNode->filename) - 1);
    newNode->filename[sizeof(newNode->filename) - 1] = '\0';
    newNode->next = NULL;
    
    // 添加到链表
    if (map->table[index] == NULL) {
        map->table[index] = newNode;
    } else {
        HashNode* current = map->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// 释放哈希表内存
void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        HashNode* current = map->table[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map->table);
    free(map);
}

// 使用strstr实现字符串包含检查
int contains(const char *str, const char *substr) {
    // 如果子字符串为NULL，认为包含
    if (substr == NULL) {
        return 1;
    }
    
    // 如果主字符串为NULL或子字符串为空，认为不包含
    if (str == NULL || *substr == '\0') {
        return 0;
    }
    
    // 使用strstr查找子字符串
    char *result = strstr(str, substr);
    
    // 如果找到，返回1；否则返回0
    return (result != NULL);
}


// 统计单个C文件的行数
int count_lines_in_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 0;
    }
    
    int line_count = 0;
    char buffer[1024];
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (!contains(buffer, "//") && !contains(buffer, "/*") && !contains(buffer, "*"))line_count++;
    }
    
    fclose(file);
    return line_count;
}

// 递归统计目录中所有C文件的行数
int count_c_files_in_dir(const char *dir_path, int *total_files, HashMap* fileMap) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("无法打开目录");
        return 0;
    }
    
    int total_lines = 0;
    struct dirent *entry;
    struct stat statbuf;
    char path[1024];
    
    while ((entry = readdir(dir)) != NULL) {
        // 跳过 "." 和 ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // 构建完整路径
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        
        // 获取文件信息
        if (stat(path, &statbuf) == -1) {
            perror("无法获取文件信息");
            continue;
        }
        
        // 如果是目录，则递归处理
        if (S_ISDIR(statbuf.st_mode)) {
            total_lines += count_c_files_in_dir(path, total_files, fileMap);
        }
        // 如果是C文件，则统计行数
        else if (S_ISREG(statbuf.st_mode) && 
                 strstr(entry->d_name, ".c") != NULL && 
                 strcmp(entry->d_name + strlen(entry->d_name) - 2, ".c") == 0) {
            
            // 检查文件名是否已存在
            if (!containsKey(fileMap, entry->d_name) && !contains(entry->d_name, "Test")) {
                // 不存在，添加到哈希表并统计行数
                put(fileMap, entry->d_name);
                int lines = count_lines_in_file(path);
                printf("%s: %d line\n", path, lines);
                total_lines += lines;
                (*total_files)++;
            } else if (contains(entry->d_name, "Test")) {
                printf("skip test file: %s\n", path);
            } else {
                // 已存在，跳过
                printf("skip exists file: %s\n", path);
            }
        }
    }
    
    closedir(dir);
    return total_lines;
}

int main() {
    const char *dir_path = "D://408//code_workspace//408-data-structure//ds";
    
    // 创建哈希表，大小为100
    HashMap* fileMap = createHashMap(100);

    put(fileMap, "count_c_lines.c");
    
    int total_files = 0;
    int total_lines = count_c_files_in_dir(dir_path, &total_files, fileMap);
    
    printf("\n total %d  c files, total %d line code\n", total_files, total_lines);
    
    // 释放哈希表内存
    freeHashMap(fileMap);
    
    return 0;
}
