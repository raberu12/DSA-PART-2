#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 14

typedef struct{
	char data;	 
	int next;
}nodeType;

typedef struct{
	nodeType node[MAX];
	int avail;
}VHeap;

typedef int List;

void initVHeap(VHeap *VH);
int allocSpace(VHeap *VH);
List stringToCBList(VHeap VH, char);

int main(){
	
}

void initVHeap(VHeap *VH){
	VH->avail = 0;
	int i;
	for(i = 0; i < MAX; i++){
		strcpy(VH->node[i].data, "");
		VH->node[i].next = i + 1;
	}
	VH->node[i].next = -1;
}
int allocSpace(VHeap *VH);
List stringToCBList(VHeap VH, char);
