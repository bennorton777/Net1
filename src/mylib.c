#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
Node *head;
Node *getLastThing(){
    Node *current=head;
    if (head==NULL){
        printf("Last thing is a null head\n");
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
        printf("Setting head\n");
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
    printf("%s\n",retVal);
    return retVal;
}
void split(char *buffer){
    int start;
    int end;
    for (int i=0;i<strlen(buffer); i++){
        if (!i){
            start=0;
        }
        if ((buffer[i]==' ')||(i==strlen(buffer)-1)){
            end=i-1;
            char *newString=(char *)malloc(sizeof(char)*(end-start+2));//1 for zero indexing, 2 for null character!
            for (int i2=0;i2<(end-start+1);i2++){
                newString[i2]=buffer[start+i2];
            }
            if (i==strlen(buffer)-1){
                newString[end-start+1]=buffer[end];
            }
            enQueue(newString);
            printf("String is %s which starts ad %d and ends at %d\n", newString, start, end);
            start=i+1;
        }
    }
}