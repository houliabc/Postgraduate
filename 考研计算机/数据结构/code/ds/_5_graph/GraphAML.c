//- - - - -无向图的邻接多重表存储表示- - - - -
typedef char * VertexType;
typedef int EdgeType;

// 边结点 
typedef struct ENode {
   int ivex;            // 该边依附的顶点 i
   struct ENode *iNext; // 指向依附于顶点 i 的下一个边结点
   int jvex;            // 该边依附的顶点 j
   struct ENode *jNext; // 指向依附于顶点 j 的下一个边结点              
   EdgeType data;       // 边数据（比如权重等）
} EdgeNode;

// 顶点结点
typedef struct VexNode {
   VertexType data;      // 顶点的数据
   EdgeNode *firstEdge;  // 指向第一条依附该顶点的边
} VexNode;

typedef struct{
   VexNode *adjmulist;  // 顶点结点表  
   int vexnum, edgenum; // 无向图的当前顶点数和边数
} AMLGraph;