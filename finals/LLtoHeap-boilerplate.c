#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 16

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
		{{"Borne", "Jason"}, 101},
		{{"Shaft", "John"}, 66},
		{{"Wick", "John"}, 33},
		{{"James", "LeBron"}, 23},
		{{"Marbella", "Jasper"}, 36},
		{{"Kiyotaka", "Ayanokoji"}, 86},
	};

	
}

void transferToHeap(LL *L, Heap *H) {

}

void insertHeap(Heap *H, studType stud) {

}

void maxHeapify(Heap *H) {

}

studType deleteMax(Heap *H){

}

void heapsort(Heap *H){

}

void displayLinkedList(LL L, char* status){

}

void displayHeap(Heap H, char* status){

}
