#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Napster.h"
#include "llist.h"
void noop(void *ignored){
    //do nothing
}
llist *newList(){
    llist *newList=(llist *)malloc(sizeof(llist));
    newList->length=0;
    return newList;
}
Node *getLastThing(llist *list){
    if (list->head==NULL){
        return NULL;
    }
    Node *idx=list->head;
    for (int i=0;i<(list->length-1);i++){
        idx=idx->next;
    }
    return idx;
}
//A good compare function returns any non-zero number for true, and zero for false.  I know that's not standards compliant, but this is a small scale project, so don't judge me okay!
Node *findInList(llist *list, void *target, int (*compare)(void *, void *)){
    Node *current=list->head;
    if (list->head==NULL){
        return NULL;
    }
    while (current){
        if (compare(target, current->data)){
            break;
        }
        else{
            current=current->next;
        }
    }
    if (current==NULL){
    }
    return current;
}
void  resetIterator(llist *list){
    list->index=list->head;
}
Node *nextElement(llist *list){
    if (list->index){
        Node *ret=list->index;
        list->index=list->index->next;
        return ret;
    }
    return NULL;
}
void addToList(llist *list, void *thing){
    Node *last=getLastThing(list);
    Node *newThing=(Node *)malloc(sizeof(Node));
    newThing->next=NULL;
    newThing->data=thing;
    if (list->head==NULL){
        list->head=newThing;
        if (!list->index){
            list->index=newThing;
        }
    }
    else{
        last->next=newThing;
    }
    newThing->next=NULL;
    list->length++;
}
void *deQueue(llist *list){
    if ((!list->length)||(list->head==NULL)){
        return NULL;
    }
    void *temp=list->head->data;
    list->head=list->head->next;
    return temp;
}
int removeFromList(llist *list, Node *node, void (*free_func)(void *)){
    if (!node){
        return 0;
    }
    if (list->head==node){
        list->length--;
        list->head=list->head->next;
        return 1;
    }
    Node *current=list->head;
    while((current->next!=node)&&(current->next!=NULL)){
        current=current->next;
    }
    if (current->next==node){
        list->length--;
        current->next=current->next->next;
        return 1;
    }
}