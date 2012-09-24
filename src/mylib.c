#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
Node *head;
Node *getLastThing(){
    Node *current=head;
    if (head==NULL){
        return head;
    }
    else{
        while (current->next!=NULL){
            current=current->next;
        }
        return current;
    }
}
void enQueue(char * thing){
    Node *last=getLastThing();
    Node *newThing=(Node *)malloc(sizeof(Node));
    newThing->data=thing;
    if (head==NULL){
        head=newThing;
    }
    else{
        last->next=newThing;
    }
    newThing->next=NULL;
}
char *deQueue(){
    if (head==NULL){
        return NULL;
    }
    Node *retNode=head;
    head=head->next;
    char *retVal=retNode->data;
    free(retNode);
    return retVal;
}
void split(char *buffer){
    char *token;
    char *search = " ";
    token = strtok(buffer, search);
    enQueue(token);
    while (token!=NULL){
        token = strtok(NULL, search);
        enQueue(token);
    }
}