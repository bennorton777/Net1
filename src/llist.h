#ifndef LLIST
#define LLIST
typedef struct queueNode{
    void *data;
    struct queueNode *next;
} Node;
typedef struct llist{
    Node *head;
    int length;
    Node *index;
} llist;
void  resetIterator(llist *list);
Node *nextElement(llist *list);
llist *newList();
void *deQueue(llist *list);
void addToList(llist *list, void * thing);
void removeFromList(llist *list, Node *node, void (*free_func)(void *));
Node *findInList(llist *list, void *target, int (*compare)(void *, void *));
#endif