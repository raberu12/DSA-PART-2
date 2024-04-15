#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct{
	char idNum;
	char FN[20];
	char LN[20];
	char MI;
	int yearLevel;
}Student;

typedef struct node{
	Student data;
	struct node *next;
}NodeType, *NodePtr;

typedef NodePtr Dictionary[SIZE];
typedef enum {FALSE, TRUE} Bool;


