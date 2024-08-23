#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 25
#define PDENSITY (int)(MAX * 0.8)
#define EMPTY 0
#define DELETED -1


typedef struct{
  int elem[MAX];
  int last;
}Dictionary;


void initDict(Dictionary *D){
    int i, x;

    for(i = 0; i < MAX; i++){
        D->elem[i] = EMPTY;
    }

    D->last = PDENSITY - 1;
}

int hashVal(int elem){
    return elem % PDENSITY;
}

bool isMember(Dictionary *D, int elem){

    int x = hashVal(elem);

    if(D->elem[x] != elem){
        for(x = PDENSITY; x < D->last && D->elem[x] != elem; x++){}
    }

    return D->elem[x] == elem;
}


void insertDict(Dictionary *D, int elem){
    int trav;

    int val = hashVal(elem);

    if(!isMember(D, elem)){
        if(D->elem[val] == EMPTY){
            D->elem[val] = elem;
        }else if(D->elem[val] != EMPTY){
            if(D->last != MAX - 1){
            D->last++;
            D->elem[D->last] = elem;
            }
        }
    }
}

void deleteDict(Dictionary *D, int elem){
    int i;

    int val = hashVal(elem);

    if(D->elem[val] == elem){
        D->elem[val] = DELETED;
    }
}

void displayDict(Dictionary D){
    int x, i;

    for(x = 0; x < PDENSITY; x++){
        printf("\n[%d] :: %d", x, D.elem[x]);
    }
    printf("\n\nSynonym Area\n");
    for(i = PDENSITY; i <= D.last; i++){
        printf("\n[%d] :: %d", i, D.elem[i]);
    }
}

int main(){
    Dictionary D;

    initDict(&D);

    insertDict(&D, 5);
    insertDict(&D, 1);
    insertDict(&D, 23);
    insertDict(&D, 4);
    insertDict(&D, 25);
    // insertDict(&D, 6);
    // insertDict(&D, 3);
    // insertDict(&D, 13);

    displayDict(D);
}
