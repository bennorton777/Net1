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
int sameString(void *a, void *b){
    a=(char *)a;
    b=(char *)b;
    if (!a||!b){
        fprintf(stderr, "HEY!  You can't compare null strings! %s %s\n",a,b);
    }
    if ((strlen(a)==strlen(b))&&(!strncmp(a, b, strlen(a)))){
        fprintf(stderr, "%s and %s are the same\n", (char *)a, (char *)b);
        return 1;
    }
    else{
        fprintf(stderr, "%s and %s are NOT the same\n", (char *)a, (char *)b);
        return 0;
    }
    return 0;
}