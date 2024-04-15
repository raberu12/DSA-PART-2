#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define arrSize 9

typedef struct node {
	int elem;
	struct node *next;
}*SET;

typedef SET Dictionary[MAX];
typedef enum {TRUE, FALSE} Boolean;

void initDictionary(Dictionary D);
void displayDictionary(Dictionary D);
int hash(int elem);
void insert(Dictionary D, int elem);
Boolean isMember(Dictionary D, int elem);
void checkIsMember(Dictionary D, int elem);
void deleteElem(Dictionary D, int elem);

int main() {
	Dictionary D;
	initDictionary(D);
	int i;
	int array[arrSize] = {0, 13, 20, 28, 30, 33, 45, 48, 108};
	for(i = 0; i < arrSize; i++) {
		insert(D, array[i]);
	}
	insert(D, 108);
	displayDictionary(D);
	checkIsMember(D, array[2]);
	checkIsMember(D, 500);
	deleteElem(D, array[2]);
	deleteElem(D, 500);
	displayDictionary(D);
}

void initDictionary(Dictionary D) {
	printf("Initialization of Dictionary D...\n");
	int i;
	for(i = 0; i < MAX; i++) {
		D[i] = NULL;
	}
}

void displayDictionary(Dictionary D) {
	printf("\nDisplaying the Dictionary:\n");
	printf("----------------------------------\n");
	int i;
	SET trav;
	for(i = 0; i < MAX; i++) {
		if(D[i] != NULL) {
			printf("Index [%d] -> ", i);
			for(trav = D[i]; trav->next != NULL; trav = trav->next) {
				printf("%d -> ", trav->elem);
			}
			printf("%d", trav->elem);
			printf("\n");
		}	
	}
	printf("----------------------------------\n");
}

int hash(int elem) {
	return elem % 10;
}

void insert(Dictionary D, int elem) {
	SET temp, *trav;
	temp = (SET)malloc(sizeof(struct node));
	if(temp != NULL) {
		for(trav = &(D[hash(elem)]); *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->next) {}
		if(*trav == NULL) {
			temp->elem = elem;
			temp->next = *trav;
			*trav = temp;
			printf("Successfully inserted %d at index [%d]\n", elem, hash(elem));
		}else{
			printf("Element %d already exists therefore it cannot be added!\n", elem);
		}
	}
}

Boolean isMember(Dictionary D, int elem) {
	SET trav;
	Boolean retval = FALSE;
	for(trav = D[hash(elem)]; trav != NULL && trav->elem != elem; trav = trav->next) {}
	if(trav != NULL) {
		retval = TRUE;
	}
	return retval;
}

void checkIsMember(Dictionary D, int elem) {
	if(isMember(D, elem) == TRUE) {
		printf("Element %d is a member of this Dictionary!\n", elem);
	} else {
		printf("Element %d is not a member of this Dictionary!\n", elem);
	}
}

void deleteElem(Dictionary D, int elem) {
	SET *trav, temp;
	for(trav = &(D[hash(elem)]); *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->next) {}
	if(*trav != NULL) {
		temp = *trav;
		*trav = temp->next;
		free(temp);
		printf("Element %d has been deleted from index [%d]\n", elem, hash(elem));
	} else {
		printf("Element %d does not exist to begin with!\n", elem);
	}
}



