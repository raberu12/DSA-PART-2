#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define arrSize 20
#define EMPTY '?'
#define DELETED '!'


typedef char Dictionary[arrSize];
typedef enum {TRUE, FALSE} Boolean;

void pause(void);
void initDict(Dictionary D);
void displayDict(Dictionary D);
int hash(char elem);
void insertDict(Dictionary D, char elem);
Boolean isMember(Dictionary D, char elem);
void deleteDict(Dictionary D, char elem);


int main() {
	Dictionary D;
	initDict(D);
	displayDict(D);
	pause();
	printf("Insertion:\n\n");
	int i;
	insertDict(D, 'A');
	insertDict(D, 'B');
	insertDict(D, 'C');
	insertDict(D, 'D');
	insertDict(D, 'E');
	insertDict(D, 'F');
	insertDict(D, 'G');
	insertDict(D, 'H');
	insertDict(D, 'W');
	insertDict(D, 'X');
	insertDict(D, 'Y');
	insertDict(D, 'Z');
	insertDict(D, 'U');
	insertDict(D, 'Q');
	insertDict(D, 'I');
	insertDict(D, 'J');
	insertDict(D, 'L');
	insertDict(D, 'O');
	insertDict(D, 'R');
	insertDict(D, 'V');
	insertDict(D, 'S');
	insertDict(D, 'V');
	displayDict(D);
	pause();
	printf("Checking if an Element is a member:\n\n");
	displayDict(D);
	isMember(D, 'Z');
	pause();
	printf("Deletion of an Element:\n\n");
	printf("Dictionary before Deletion:\n\n");
	displayDict(D);
	deleteDict(D, 'A');
	deleteDict(D, 'Q');
	deleteDict(D, 'Q');
	printf("Dictionary after Deletion:\n\n");
	displayDict(D);
	pause();
}

void pause(void) {
	printf("\n\nPress any key to continue...");
	getch();
	system("CLS");
}

void initDict(Dictionary D) {
	printf("Trying to initialize the Dictionary...\n\n");
	int i;
	for(i = 0; i < arrSize; i++) {
		D[i] = EMPTY;
	}
	printf("Dictionary initialized!\n\n");
}

void displayDict(Dictionary D) {
	printf("Legend:\n[%c] - EMPTY\n[%c] - DELETED\n\n",EMPTY, DELETED);
	printf("Displaying the Dictionary:\n\n");
	int i;
	for(i = 0; i < arrSize; i++) {
		printf("%d - [%c]\n", i, D[i]);
	}
}
int hash(char elem) {
	return elem % 20;
}
void insertDict(Dictionary D, char elem) {
	int index = hash(elem);
	if(D[index] == EMPTY || D[index] == DELETED) {
		D[index] = elem;
	} else {
		int currentHash = index;
		if(D[index] == elem) {
			printf("The element [%c] already exists!\n\n", elem);
		} else {
			for(index = index + 1; index != currentHash && D[index] != EMPTY && D[index] != DELETED && D[index] != elem; index = (index + 1) % arrSize) {}
			if(D[index] == DELETED || D[index] == EMPTY) {
				D[index] = elem;
			} else if(index == currentHash) {
				printf("The element [%c] could not be added because the Dictionary is already full!\n\n", elem);
			} else if(D[index] == elem) {
				printf("The element [%c] already exists!\n\n", elem);
			}
		}
	}
}

Boolean isMember(Dictionary D, char elem) {
	Boolean retval = FALSE;
	int hashVal = hash(elem);
	printf("\nChecking if Element %c is in the Dictionary...\n\n", elem);
	if(D[hashVal] == elem) {
		retval = TRUE;
	} else {
		int index;
		for(index = hashVal + 1; index != hashVal && D[index] != EMPTY && D[index] != elem; index = (index + 1) % arrSize) {}
		if(index == hashVal || D[index] == EMPTY) {
			retval = FALSE;
		} else {
			retval = TRUE;
		}
	}
	if(retval == TRUE) {
		printf("The element %c is a member!\n\n", elem);
	} else {
		printf("The element %c is not a member!\n\n", elem);
	}

	return retval;
}
void deleteDict(Dictionary D, char elem) {
	int hashVal = hash(elem);
	printf("Trying to delete element %c in the Dictionary...\n\n", elem);
	if(D[hashVal] == elem){
		D[hashVal] = DELETED;
	}else{
		int index;
		for(index = hashVal + 1; index != hashVal && D[index] != EMPTY && D[index] != elem; index = (index + 1) % arrSize){}
		if(D[index] == elem){
			D[index] = DELETED;
		}else{
			printf("The Element %c does not exist or has been already deleted!\n\n", elem);
		}
	}
}

