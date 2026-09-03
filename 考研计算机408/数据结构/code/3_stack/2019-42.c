（1）该队列应选择链式存储结构。
（2）判断队空：Q->rear == Q->front；判断队满：不会出现队满情况
(4)
// 入队操作
typedef int ElemType;
typedef struct QueueNode {
    ElemType data;
    struct QueueNode *next;
}QueueNode;
typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int length;
}*LinkQueue, *freeQueue;
bool EnQueue(LinkQueue Q, freeQueue f, ElemType e) {
    QueueNode *p;
    // 若空闲队列没有可用空间，则开辟一个空间
    if (f->rear == f->front) {
        // 为新插入结点开辟空间
        p = (QueueNode*)malloc(sizeof(QueueNode));
    }
    // 若有多余的空间空间，则从此处拿
    else {
        p = f->front->next;
        // 更新头指针指向的结点
        f->front->next = p->next;
    }
    p->data = e;
    // 尾节点的next指针应该指向空
    p->next = NULL;
    // 将原本的尾指针指向新插入的结点
    Q->rear->next = p;
    Q->rear = p;
    Q->length++;
    return true;
}
// 出队操作
bool DeQueue(LinkQueue Q, freeQueue f, ElemType *e) {
    // 若队列为空，则出队失败
    if (Q->rear == Q->front) {
        return false;
    }
    // 若Q不为空，则将首元结点出队，同时要加入空闲队列中
    QueueNode *p = Q->front->next;
    if (e)
        // 返回出队的值
        *e = p->data;
    Q->front->next = p->next;
    // 将从Q中出队的结点插入到空闲队列中
    p->next = NULL;
    f->rear->next = p;
    // 更新空闲队列的尾指针
    f->rear = p;
    Q->length--;
    return true;
}