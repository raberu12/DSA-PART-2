#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef unsigned char SET;
typedef enum {FALSE, TRUE} Bool;

void pause(void);
void initSet(SET *A);
void displaySet(SET A);
void Insert(SET *A, SET elem);
Bool Member(SET A, SET elem);
void Delete(SET *A, SET elem);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);


int main() {
	SET C;
	printf("Initializing SET C...");
	initSet(&C);
	pause();
	
	printf("Inserting values in C\n");
	Insert(&C, 8);
	Insert(&C, 7);
	Insert(&C, 0);
	Insert(&C, 5);
	Insert(&C, 4);
	displaySet(C);
	pause();
	
	SET check = 5;
	printf("Check if %d is an element in the SET\n", check);
	if(Member(C, check)){
		printf("%d is an element in the SET!\n", check);
	}else{
		printf("%d is not an element in the SET!\n", check);
	}
	pause();
	
	printf("Deletion of Elements in SET C\n");
	printf("Current SET:\n");
	displaySet(C);
	SET deletedNum01 = 7;
	SET deletedNum02 = 8;
	printf("Trying to delete: %d\n", deletedNum01);
	Delete(&C, deletedNum01);
	printf("Trying to delete: %d\n", deletedNum02);
	Delete(&C, deletedNum02);
	printf("SET C after deletion:\n");
	displaySet(C);
	pause();
	
	SET B;
	printf("Initializing SET B...\n");
	initSet(&B);
	printf("Inserting values in SET B\n");
	Insert(&B, 1);
	Insert(&B, 2);
	Insert(&B, 3);
	Insert(&B, 0);
	printf("Displaying SET B:\n");
	displaySet(B);
	pause();
	printf("SET OPERATIONS: \n");
	SET S = Union(C, B);
	printf("Union of C and B:\n");
	displaySet(S);
	S = Difference(C, B);
	printf("Difference of C and B:\n");
	displaySet(S);
	printf("Intersection of C and B:\n");
	S = Intersection(C, B);
	displaySet(S);
	
	
}

void pause(void) {
	printf("\n\nPress any button to continue...");
	getch();
	system("CLS");
}

void initSet(SET *A) {
	*A = 0;
}

void displaySet(SET A) {
	SET mask;
	int i;

	printf("Displaying the bit pattern of the SET:");
	for(mask = 1 << (sizeof(SET)*8-1); mask > 0; mask >>= 1) {
		printf("[%d]", (A & mask) ? 1 : 0);
	}

	printf("\nDisplaying the elements in the SET:");
	for(i = 0; i < (sizeof(SET)*8); i++) {
		if(A & (1 << i)) {
			printf("[%d]", i);
		}
	}
	printf("\n");
}

void Insert(SET *A, SET elem){
	if(elem > sizeof(SET)*8-1){
		printf("Out of Range\n");
	}else{
		printf("Position #%d has been added!\n", elem);
		*A |= (1 << elem);
	}
}

Bool Member(SET A, SET elem){
	return(A & (1 << elem)) ? TRUE : FALSE;
}

void Delete(SET *A, SET elem){
	if(elem > 7){
		printf("The number %d is out of range or is non-existent!\n", elem);
	}else{
		*A &= ~(1 << elem);
	}
}

SET Union(SET A, SET B){
	return A | B;
}

SET Intersection(SET A, SET B){
	return A & B;
}

SET Difference(SET A, SET B){
	return A & ~(B);
}

