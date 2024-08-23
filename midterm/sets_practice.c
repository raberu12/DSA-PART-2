#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 5

typedef int SET[MAX];

void pause(void);
SET *Union(SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);
int member(SET A, int ndx);
void insert(SET A, int ndx);
void deleteSetElem(SET A, int ndx);
void displaySet(SET A);

int main(void){
	SET A = {0, 1, 1, 1, 0};
	SET B = {0, 1, 1, 1, 0};
	printf("SET A:\n");
	displaySet(A);
	printf("\nSET B:\n");
	displaySet(B);
	pause();
	int isMember = member(A, 3);
	printf("Looking for Element 3 in SET A\n");
	if(isMember == 1){
		printf("Element is a member of SET A");
	}else{
		printf("Nah it ain't a element");
	}
	pause();
	printf("Trying to insert element 4 in SET A\n");
	printf("SET A prior to insertion: ");
	displaySet(A);
	insert(A, 4);
	printf("\nSET A after insertion: ");
	displaySet(A);
	pause();
	printf("Deleting element 3 in SET B\n");
	printf("SET B prior to deletion: ");
	displaySet(B);
	deleteSetElem(B, 3);
	printf("\nSET B after deletion: ");
	displaySet(B);
	pause();
	printf("Current SET A: ");
	displaySet(A);
	printf("\nCurrent SET B: ");
	displaySet(B);
	printf("\nUID of SET\n");
	printf("Union of SET A and B: \n");
	SET *C = Union(A, B);
	displaySet(*C);
	printf("\nIntersection of SET A and B: \n");
	C = Intersection(A, B);
	displaySet(*C);
	printf("\nDifference of SET A and B: \n");
	C = Difference(A, B);
	displaySet(*C);
}

void pause(void) {
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}

SET *Union(SET A, SET B){
	int i;
	SET *C = (SET*)malloc(sizeof(SET));
	if(C != NULL){
		for(i = 0; i < MAX; i++){
			(*C)[i] = A[i] | B[i];
		}
	}
	return C;
}
SET *Intersection(SET A, SET B){
	int i;
	SET *C = (SET*)malloc(sizeof(SET));
	if(C != NULL){
		for(i = 0; i < MAX; i++){
			(*C)[i] = A[i] & B[i];
		}
	}
	return C;
}
SET *Difference(SET A, SET B){
	int i;
	SET *C = (SET*)malloc(sizeof(SET));
	if(C != NULL){
		for(i = 0; i < MAX; i++){
			(*C)[i] = A[i] & ~B[i];
		}
	}
	return C;
}
int member(SET A, int ndx){
	return A[ndx] == 1 ? 1 : 0;
}
void insert(SET A, int ndx){
	if(ndx < MAX){
		A[ndx] = 1;
	}
}
void deleteSetElem(SET A, int ndx){
	if(ndx < MAX){
		A[ndx] = 0;
	}
}
void displaySet(SET A){
	int i;
	for(i = 0; i < MAX; i++){
		printf("[%d]", A[i]);
	}
}
