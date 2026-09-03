#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "SqQueue.c"

int main() {
    SqQueue queue;
    InitQueue(&queue, 6);

    EnQueue(&queue, 10);
    EnQueue(&queue, 100);
    EnQueue(&queue, 1000);
    EnQueue(&queue, 10000);

    printf("queue length = %d\n", QueueLength(&queue));
    QueueTraverse(&queue);

    DeQueue(&queue, NULL);
    QueueTraverse(&queue);

    DestroyQueue(&queue);
}
