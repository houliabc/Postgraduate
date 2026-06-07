#include <stdlib.h>

//- - - - -有向图的十字链表存储表示- - - - -
typedef int VertexType;
typedef int ArcType;

// 弧结点
typedef struct ArcNode {
   int tailvex;             // 弧尾顶点在顶点表中的下标
   struct ArcNode *tnext;   // 指向相同弧尾的下一个弧结点的指针域
   int headvex;             // 弧头顶点在顶点表中的下标
   struct ArcNode *hnext;   // 指向相同弧头的下一个弧结点的指针域
   ArcType info;            // 弧的信息（比如权重等）
} ArcNode;

// 顶点结点
typedef struct VexNode {
   VertexType data;        // 顶点存储的数据
   ArcNode *firstout;      // 指向第一条以该顶点作为弧尾的弧结点
   ArcNode *firstin;       // 指向第一条以该顶点作为弧的头弧结点
} VexNode;

// 有向图的十字链表表示
typedef struct {
   VexNode *xlist;       // 顶点结点表
   int vexNum, arcNum;   // 有向图的当前顶点数和弧数
} OLGraph;

// 从顶点表中，拿到顶点 v 对应的标识（即下标）
int LocateVex(OLGraph *G, VertexType v) {
    for (int i = 0; i < G->vertexNum; i++) {
        if (strcmp(G->xlist[i].data, v) == 0) return i;
    }
    return -1;
}


void InitOLGraph(OLGraph *G,
         int vertexNum, VertexType vertices[vertexNum],  
         int arcNum, VertexType arcs[arcNum][3]) {
      G->arcNum = arcNum;
      G->vexNum = vertexNum;

      G->xlist = (VexNode *) malloc (sizeof(VexNode) * vertexNum);
      for (int i = 0; i < vertexNum; i++) {
         G->xlist[i].data = vertices[i];
         G->xlist[i].firstout = NULL;
         G->xlist[i].firstin = NULL;
      }

      for (int i = 0; i < arcNum; i++) {
         int a = LocateVex(G, arcs[i][0]); // 弧尾
         int b = LocateVex(G, arcs[i][1]); // 弧头
         if (a == -1 || b == -1) {
            printf("错误：边 %s-%s 包含不存在的顶点\n", arcs[i][0], arcs[i][1]);
            continue;
         }

         ArcNode *node = (ArcNode *)malloc(sizeof(ArcNode));
         node->tailvex = a;
         node->headvex = b;
         // 设置弧的权重
         node->info = atoi(arcs[i][2]);

         // 插入到以顶点 a 作为弧尾的链表的头部
         node->tnext = G->xlist[a].firstout;
         G->xlist[a].firstout = node;

         // 插入到以顶点 b 作为弧头的链表的头部
         node->hnext = G->xlist[b].firstin;
         G->xlist[b].firstin = node;
      }
}