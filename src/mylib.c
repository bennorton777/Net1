#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
void split(char *buffer, llist *list){
    char *token;
    char *delim = " ";
    token = strtok(buffer, delim);
    char *buff=malloc(sizeof(char)*strlen(token));
    strcpy(buff, token);
    addToList(list, (void *)buff);
    token = strtok(NULL, delim);
    while (token!=NULL){
        char *buff=malloc(sizeof(char)*strlen(token));
        strcpy(buff, token);
        addToList(list, (void *)buff);
        token = strtok(NULL, delim);
    }
}
int sameString(void *a1, void *b1){
    char *a=(char *)a1;
    char *b=(char *)b1;
    if ((strlen(a)==strlen(b))&&(!strncmp(a, b, strlen(a)))){
        return 1;
    }
    return 0;
}