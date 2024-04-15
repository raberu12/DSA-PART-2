#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define DEFAULT 7

typedef struct ArrayList {
	int *array;
	int count;
} SET;

typedef enum {FALSE, TRUE} boolean;


void pause(void);
void initSet(SET *A);
void insertElem(SET *A, int elem);
void deleteElem(SET *A, int elem);
boolean isMember(SET A, int elem);
SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);
void displaySet(SET A, char*);

int main() {

	SET A;
	SET B;

	initSet(&A);
	insertElem(&A, 1);
	insertElem(&A, 2);
	insertElem(&A, 3);
	insertElem(&A, 6);
	insertElem(&A, 7);
	displaySet(A, "Displaying SET A" );
	deleteElem(&A, 2);
	displaySet(A, "Displaying SET A after deletion");
	pause();
	initSet(&B);
	insertElem(&B, 4);
	insertElem(&B, 5);
	insertElem(&B, 1);
	insertElem(&B, 7);
	insertElem(&B, 8);
	displaySet(A, "Displaying SET A");
	displaySet(B, "Displaying SET B");
	SET *C = Union(A, B);
	displaySet(*C, "Displaying the UNION of SET A and B");
	pause();
	displaySet(A, "Displaying SET A");
	displaySet(B, "Displaying SET B");
	C = Intersection(A, B);
	displaySet(*C, "Displaying the INTERSECTION of SET A and B");
	pause();
	displaySet(A, "Displaying SET A");
	displaySet(B, "Displaying SET B");
	C = Difference(A, B);
	displaySet(*C, "Displaying the DIFFERENCE of SET A and B");
}

void pause(void) {
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}

void initSet(SET *A) {

	A->array = (int*)malloc(sizeof(int)*DEFAULT);
	A->count = 0;

}

void insertElem(SET *A, int elem) {
	int i;
	if(A->count < DEFAULT) {
		for(i = 0; i < A->count && A->array[i] != elem; i++) {}
		if(A->array[i] != elem) {
			A->array[A->count] = elem;
			A->count++;
		}
	}
}

void deleteElem(SET *A, int elem) {
	int i, j, temp;
	if(A->count > 0) {
		for(i = 0; i < A->count; i++) {
			if(A->array[i] == elem) {
				for(j = i; j < A->count; j++) {
					A->array[j] = A->array[j+1];

				}
			}
		}
		A->count--;
	}
}

boolean isMember(SET A, int elem) {
	int i;
	boolean found = FALSE;
	for(i = 0; i < A.count && found != TRUE; i++) {
		if(A.array[i] == elem) {
			found = TRUE;
		}
	}
	return found;
}

SET* Union(SET A, SET B) {
	SET *C = (SET*)malloc(sizeof(SET));
	C->count = 0;
	int maxSize = A.count + B.count;
	C->array = (int*)malloc(sizeof(int)*(maxSize));
	int i, j, found = 0;
	for(i = 0; i < A.count; i++) {
		C->array[i] = A.array[i];
		C->count++;
	}
	for(i = 0; i < B.count; i++) {
		if(!isMember(*C, B.array[i])) {
			C->array[C->count] = B.array[i];
			C->count++;
		}
	}
	return C;
}

SET* Intersection(SET A, SET B) {
	SET *C = (SET*)malloc(sizeof(SET));
	C->count = 0;
	int maxSize = A.count + B.count;
	C->array = (int*)malloc(sizeof(int)*maxSize);
	int i, j;
	for(i = 0; i < A.count; i++) {
		for(j = 0; j < B.count; j++) {
			if(A.array[i] == B.array[j]) {
				C->array[C->count] = A.array[i];
				C->count++;
			}
		}
	}
	return C;
}

SET* Difference(SET A, SET B) {
	SET *C = (SET*)malloc(sizeof(SET));
	C->count = 0;
	C->array = (int*)malloc(sizeof(int)*A.count);
	int i, j;
	for(i = 0; i < A.count; i++) {
		for(j = 0; j < B.count && A.array[i] != B.array[j]; j++) {}
		if(j == B.count) {
			C->array[C->count] = A.array[i];
			C->count++;
		}
	}
	return C;
}

void displaySet(SET A, char string[]) {
	printf("%s:\n", string);
	int i;
	for(i = 0; i < A.count; i++) {
		printf("%d ", A.array[i]);
	}
	printf("\n");
}
