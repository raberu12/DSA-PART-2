#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char FN[24], LN[16], MI;
}nametype;

typedef struct{
	char ID[10];
	nametype name;
	char course[8];
	int yrLevel;
} studRec;

typedef struct{
	nametype names[LSIZE];
	int lastNdx;
} *NameList;

typedef struct node{
	studRec sElem;
	struct node *sLink;
}*LinkList;

NameList removeICT(LinkList* A);
void populateLinkList(LinkList* A);
void displayDeleted(NameList A);
void displayLinkList(LinkList A);

int main(){
	
}

