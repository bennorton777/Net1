#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mylib.h"
void split(char *buffer, llist *list){
    char *token;
    char *delim = " ";
    token = strtok(buffer, delim);
    addToList(list, (void *)token);
    token = strtok(NULL, delim);
    while (token!=NULL){
        addToList(list, (void *)token);
        token = strtok(NULL, delim);
    }
}
int sameString(char *a, char *b){
    a=(char *)a;
    b=(char *)b;
    if ((strlen(a)==strlen(b))&&(!strncmp(a, b, strlen(a)))) return 1;
    return 0;
}