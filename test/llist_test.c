#include <stdio.h>
#include <stdlib.h>
#include "../src/mylib.h"
int compareFunc(void *a, void *b){
    a=(char *)a;
    b=(char *)b;
    if (sameString(a,b)){
        return 1;
    }
    else{
        return 0;
    }
}
void free_func(void *a){
//    a=(char *)a;
//    fprintf(stderr,"About to free %s\n",(char *)a);
//    free((char *)a);
}
int main(int argc, const char* argv[]) {
    int (*compareIt)(void *, void *)=NULL;
    void (*freeIt)(void *)=NULL;
    compareIt=compareFunc;
    freeIt=free_func;
    llist *list=newList();
    char *hello="HELLO";
    char *world="WORLD";
    addToList(list, hello);
    addToList(list, world);
    removeFromList(list, findInList(list,"WORLD",compareIt), freeIt);
    fprintf(stderr,"Length is %d\n", list->length);
    removeFromList(list, findInList(list,"HELLO",compareIt), freeIt);
    fprintf(stderr,"Length is %d\n", list->length);
    addToList(list, "THING");
    printf("Length is %d\n", list->length);
}