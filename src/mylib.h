#ifndef MYLIB
#define MYLIB
typedef struct queueNode{
    void *data;
    struct queueNode *next;
} Node;
void enQueue(char * thing);
char *deQueue();
#endif