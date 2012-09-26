#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llist.h"
llist *newList(){
    llist *newList=(llist *)malloc(sizeof(llist));
    newList->length=0;
    return newList;
}
Node *getLastThing(llist *list){
    Node *current=list->head;
    if (list->head==NULL){
        return list->head;
    }
    else{
        while (current->next!=NULL){
            current=current->next;
        }
        return current;
    }
}
//A good compare function returns any non-zero number for true, and zero for false.  I know that's not standards compliant, but this is a small scale project, so don't judge me okay!
Node *findInList(llist *list, void *target, int (*compare)(void *, void *)){
    Node *current=list->head;
    if (!current){
        return NULL;
    }
    while (current, (!compare(target, current->data))){
        current=current->next;
    }
    return current;
}
void  resetIterator(llist *list){
    list->index=list->head;
}
Node *nextElement(llist *list){
    if (list->index){
        Node *ret=list->index;
        list->index=list->index->net;
        return ret;
    }
    return NULL;
}
void addToList(llist *list, void *thing){
    list->length++;
    Node *last=getLastThing(list);
    Node *newThing=(Node *)malloc(sizeof(Node));
    newThing->data=thing;
//    fprintf(stderr, "Adding %s\n", (char *)thing);
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
}
void *deQueue(llist *list){
    if (list->length){
        if (list->length==1){
            Node *head=list->head;
            void *ret=list->head->data;
            list->head=NULL;
            free(head);
            list->length--;
            return ret;
        }
        else{
            list->length--;
            Node *head=list->head;
            list->head=list->head->next;
            void *ret=head->data;
            free(head);
            return ret;
        }
    }
    return NULL;
}
void removeFromList(llist *list, Node *node, void (*free_func)(void *)){
//    fprintf(stderr, "Removing %s\n", (char *)node->data);
    if (list->head==node){
        list->length--;
        free_func(node->data);
        list->head=NULL;
        free(node);
        return;
    }
    Node *current=list->head;
    while((current->next!=node)&&(current->next)){
        current=current->next;
    }
    if (current->next==node){
        list->length--;
        current->next=current->next->next;
        free_func(node->data);
        free(node);
    }
}