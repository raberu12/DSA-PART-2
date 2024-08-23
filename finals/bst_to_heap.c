#include <stdio.h>
#include <stdlib.h>
#define SIZE 15

typedef struct {
	int array[SIZE];
	int lastNdx;
} Heap;

typedef struct node {
	int data;
	struct node *LC;
	struct node *RC;

} treeNode, *BST;

void initTree(BST *T);
void insertTree(BST *T, int data);
void initHeap(Heap *H);
void convertTreeToHeap(BST T, Heap *H); //copies the values in the tree to the heap
void minHeapify(Heap *H);
int deleteMin(Heap *H);
void insertHeap(Heap *H, int data);
void heapsort(Heap *H);
void displayTreePreorder(BST T);
void displayHeap(Heap H);

int main() {

	int givenList[10] = {50, 23, 12, 70, 43, 90, 4, 5, 63, 63};
	BST myTree;
	Heap myHeap;

	initTree(&myTree);
	initHeap(&myHeap);

	int i;
	for(i = 0; i < 10; i++) {
		insertTree(&myTree, givenList[i]);
	}

	printf("Preorder Display of the Binary Search Tree\n");
	displayTreePreorder(myTree);
	printf("\n");

	convertTreeToHeap(myTree, &myHeap);
	printf("After Converting Tree to a Heap:\n");
	displayHeap(myHeap);

	minHeapify(&myHeap);
	printf("After Min Heapifying the Heap:\n");
	displayHeap(myHeap);


	heapsort(&myHeap);
	printf("After Heapsort:\n");
	displayHeap(myHeap);

}

void initTree(BST *T) {
	*T = NULL;
}

void insertTree(BST *T, int data) {
	BST *trav;
	BST temp;
	for(trav = T; *trav != NULL && (*trav)->data != data;) {
		trav = ((*trav)->data < data) ? &(*trav)->RC : &(*trav)->LC;
	}
	if(*trav == NULL) {
		temp = (BST)calloc(sizeof(treeNode), 1);
		if(temp != NULL) {
			temp->data = data;
			*trav = temp;
		}
	}
}

void initHeap(Heap *H) {
	H->lastNdx = -1;
}

void insertHeap(Heap *H, int data) {
	int currentNdx;
	if(H->lastNdx < SIZE) {
		H->lastNdx++;
		H->array[H->lastNdx] = data;
	} else {
		printf("Heap is full! Cannot insert %d!\n", data);
	}
	for(currentNdx = H->lastNdx; currentNdx > 0; currentNdx = (currentNdx-1)/2) {
		int parent = (currentNdx-1)/2;
		if(H->array[currentNdx] < H->array[parent]) {
			int temp = H->array[currentNdx];
			H->array[currentNdx] = H->array[parent];
			H->array[parent] = temp;
		}
	}
}

void convertTreeToHeap(BST T, Heap *H) {
	if(T != NULL) {
		H->lastNdx++;
		H->array[H->lastNdx] = T->data;
		convertTreeToHeap(T->LC, H);
		convertTreeToHeap(T->RC, H);
	}
}

void minHeapify(Heap *H) {
	int currentNdx, parent;
	for(parent = H->lastNdx-1/2; parent >= 0; parent--) {
		for(currentNdx = parent; currentNdx <= H->lastNdx;) {
			int lc = currentNdx * 2 + 1;
			int rc = lc + 1;
			if(lc <= H->lastNdx) {
				int smaller = lc;
				if (rc <= H->lastNdx && H->array[rc] < H->array[lc]) {
					smaller = rc;
				}
				if(H->array[currentNdx] > H->array[smaller]) {
					int temp = H->array[currentNdx];
					H->array[currentNdx] = H->array[smaller];
					H->array[smaller] = temp;
					currentNdx = smaller;
				} else {
					currentNdx = H->lastNdx + 1;
				}
			} else {
				currentNdx = H->lastNdx + 1;
			}
		}
	}
}

int deleteMin(Heap *H) {
	int retval = -1;
	if(H->lastNdx != -1) {
		retval = H->array[0];
		H->array[0] = H->array[H->lastNdx];
		H->lastNdx--;
	}
	int currentNdx;
	for(currentNdx = 0; currentNdx <= H->lastNdx;) {
		int lc = currentNdx * 2 + 1;
		int rc = lc + 1;
		if(lc <= H->lastNdx) {
			int smaller = lc;
			if(rc <= H->lastNdx && H->array[rc] < H->array[smaller]) {
				smaller = rc;
			}
			int temp = H->array[currentNdx];
			H->array[currentNdx] = H->array[smaller];
			H->array[smaller] = temp;
			currentNdx = smaller;
		} else {
			currentNdx = H->lastNdx+1;
		}
	}
	return retval;
}

void heapsort(Heap *H) {
	int originalLast = H->lastNdx;
	int tempData;
	while(H->lastNdx != -1) {
		int temp = deleteMin(H);
		H->array[H->lastNdx+1] = temp;
	}
	H->lastNdx = originalLast;
}

void displayTreePreorder(BST T) {
	if(T != NULL) {
		printf("%d -> ", T->data);
		displayTreePreorder(T->LC);
		displayTreePreorder(T->RC);
	}
}
void displayHeap(Heap H) {
	printf("Displaying the Heap\n");
	int i;
	printf("Index\tData\n");
	for(i = 0; i <= H.lastNdx; i++) {
		printf("%d\t%d\n", i, H.array[i]);
	}
}

