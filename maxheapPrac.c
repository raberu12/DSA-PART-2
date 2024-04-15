#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 17

typedef struct nameType {
	char *lname;
	char *fname;
} nameType;

typedef struct studNode {
	nameType name;
	int prioNum;
} studType;

typedef struct node {
	studType student;
	struct node *next;
} listNode, *LL;

typedef struct heap {
	studType studHeap[MAX];
	int lastNdx;
} Heap;

void initLinkedList(LL *L);
void initHeap(Heap *H);
void populateLinkedList(LL *L);
void transferToHeap(LL *L, Heap *H);
void insertHeap(Heap *H, studType stud);
void maxHeapify(Heap *H);
studType deleteMax(Heap *H);
void heapsort(Heap *H);
void displayLinkedList(LL L, char* status);
void displayHeap(Heap H, char* status);

int main() {
	LL myList;
	Heap myHeap;

	initLinkedList(&myList);
	initHeap(&myHeap);
	populateLinkedList(&myList);
	
	displayLinkedList(myList, "After Populating");
	transferToHeap(&myList, &myHeap);
	displayHeap(myHeap, "After Transfer from Linked List");
	
	maxHeapify(&myHeap);
	displayHeap(myHeap, "After Max Heapify");
	
	studType stud1 ={{"Slayer", "Goblin"}, 77};
	insertHeap(&myHeap, stud1);
	displayHeap(myHeap, "After Insertion");
	
	heapsort(&myHeap);
	displayHeap(myHeap, "After Heapsort");
	
}

void initLinkedList(LL *L) {
	*L = NULL;
	printf("Linked List initialized!\n\n");
}

void initHeap(Heap *H) {
	H->lastNdx = -1;
	printf("Heap initialized!\n\n");
}

void populateLinkedList(LL *L) {
	studType array[] = {{{"Magdadaro", "Matt"}, 100},
		{{"Labide", "Xander"}, 20},
		{{"Lanutan", "Achille"}, 10},
		{{"Nacario", "Shawn"}, 55},
		{{"Patalingersz", "Eman"}, 40},
		{{"Laurent", "Yves"}, 31},
		{{"Dior", "Christian"}, 21},
		{{"Lauren", "Ralph"}, 88},
		{{"Philippe", "Patek"}, 91},
		{{"Jack", "Cactus"}, 3},
		{{"Borne", "Jason"}, 99},
		{{"Shaft", "John"}, 66},
		{{"Wick", "John"}, 33},
		{{"James", "LeBron"}, 23},
		{{"Marbella", "Jasper"}, 36},
		{{"Kiyotaka", "Ayanokoji"}, 86},
	};

	int size = sizeof(array)/sizeof(array[0]);

	int i;
	LL temp, *trav;
	for(i = 0; i < size; i++) {
		for(trav = L; *trav != NULL && strcmp((*trav)->student.name.fname, array[i].name.fname) < 0; trav = &(*trav)->next) {}
		temp = (LL)malloc(sizeof(listNode));
		if(temp != NULL) {
			temp->next = *trav;
			temp->student = array[i];
			*trav = temp;
		}
	}
	printf("Linked List populated!\n\n");
}

void transferToHeap(LL *L, Heap *H) {
	LL *trav, temp;
	studType catcher;

	for(trav = L; *trav != NULL;) {
		temp = *trav;
		if(temp != NULL) {
			catcher = temp->student;
			H->lastNdx++;
			H->studHeap[H->lastNdx] = catcher;
		} else {
			printf("The Linked List is now empty!\n\n");
		}
		trav = &(*trav)->next;
		free(temp);
	}
	printf("Successfully transfered Linked List data into the heap!\n\n");
}

void insertHeap(Heap *H, studType stud) {
	if(H->lastNdx < MAX - 1){
		H->lastNdx++;
		int child = H->lastNdx;
		int parent = (child - 1)/2;
		while(child > 0 && H->studHeap[parent].prioNum < stud.prioNum){
			H->studHeap[child] = H->studHeap[parent];
			child = parent;
			parent = (child - 1)/2;
		}
		H->studHeap[child] = stud;
	}
	printf("Successfully inserted into the Heap!\n\n");
}

void maxHeapify(Heap *H) {
	int currentNdx, parent;
	for(currentNdx = (H->lastNdx-1)/2; currentNdx >= 0; currentNdx--) {
		for(parent = currentNdx; parent <= H->lastNdx;) {
			int lc = parent * 2 + 1;
			int rc = lc + 1;
			if(lc <= H->lastNdx) {
				int bigger = lc;
				if(rc <= H->lastNdx && H->studHeap[rc].prioNum > H->studHeap[bigger].prioNum) {
					bigger = rc;
				}
				if(H->studHeap[parent].prioNum < H->studHeap[bigger].prioNum) {
					studType temp = H->studHeap[parent];
					H->studHeap[parent] = H->studHeap[bigger];
					H->studHeap[bigger] = temp;
					parent = bigger;
				} else {
					parent = H->lastNdx + 1;
				}
			} else {
				parent = H->lastNdx + 1;
			}
		}
	}
}

studType deleteMax(Heap *H) {
	studType retval = {{"XXXX", "XXXX"}, -1};
	if(H->lastNdx != -1) {
		retval = H->studHeap[0];
		H->studHeap[0] = H->studHeap[H->lastNdx];
		H->lastNdx--;
		maxHeapify(H);
	}
	return retval;
}

void heapsort(Heap *H) {
	int originalLast = H->lastNdx;
	studType temp;
	while(H->lastNdx != -1) {
		temp = deleteMax(H);
		H->studHeap[H->lastNdx + 1] = temp;
	}
	H->lastNdx = originalLast;
	printf("Successfully heapsorted!\n");
}

void displayLinkedList(LL L, char* status) {
	printf("Student Information Data in Linked List: (%s)\n", status);
	printf("%-15s%-15s%-15s\n", "First Name", "Last Name", "Priority Number");

	LL trav;
	for(trav = L; trav != NULL; trav = trav->next) {
		printf("%-15s%-15s%-15d\n", trav->student.name.fname, trav->student.name.lname, trav->student.prioNum);
	}
	printf("\n");
}

void displayHeap(Heap H, char* status) {
	printf("Student Information Data in Heap: (%s)\n", status);
	printf("Current Last: %d\n", H.lastNdx);
	printf("%-15s%-15s%-15s\n", "First Name", "Last Name", "Priority Number");

	int i;
	for(i = 0; i <= H.lastNdx; i++) {
		printf("%-15s%-15s%-15d\n", H.studHeap[i].name.fname, H.studHeap[i].name.lname, H.studHeap[i].prioNum);
	}
	printf("\n");
}
