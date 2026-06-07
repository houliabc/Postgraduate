
// 路由器和路由器之间的链路
typedef struct Link {
    unsigned int id;
    unsigned int ip;
} LinkNode;

// 路由器和网络之间的链路
typedef struct Net {
    char* prefix;
} NetNode;

// 边表结点（链路）
typedef struct ENode {
    int flag;  // 链路的类型，flag=0 表示 Link，flag=1 表示 Net
    union {
        LinkNode link;
        NetNode net;
    };
    int metric;         // 链路的费用
    struct ENode *nextEdge;  // 指向下一条链路的指针
} EdgeNode;

// 表头结点（路由器）
typedef struct VNode {
    unsigned int routerId;     // 路由器的 ID
    EdgeNode *firstEdge; // 指向第一条依附该顶点的边的指针
} VertexNode;

// 邻接表，保存 4 个路由器顶点结点
VertexNode adjList[4];   

