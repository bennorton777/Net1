#ifndef MYLIB
#define MYLIB
typedef struct queueNode{
    void *data;
    struct queueNode *next;
} Node;
typedef struct llist{
    Node *head;
    int length;
} llist;
llist *newList();
void split(char *buffer, llist *list);
void *deQueue(llist *list);
void addToList(llist *list, void * thing);
void removeFromList(llist *list, Node *node, void (*free_func)(void *));
int sameString(char *a, char *b);
Node *findInList(llist *list, void *target, int (*compare)(void *, void *));
#endif