#include <stdio.h>
#include <stdlib.h>
#define VH_SIZE 15

typedef struct elemType {
	char *name;
	int value;
} elemType;

typedef struct node {
	elemType elem;
	int lc;
	int rc;
} nodeType;

typedef struct VHeap {
	nodeType nodes[VH_SIZE];
	int avail;
} VHeap;

typedef int BST;

void initializeVHeap(VHeap* V);
void initializeBST(BST *B);
BST allocSpace(VHeap* V);
void deallocSpace(VHeap* V, BST index);
void insert(BST *B, VHeap *VH, elemType E);
void deleteNode(BST *B, VHeap *V, int value);
void displayVHeap(VHeap V);
void displayElem(elemType E);
void displayBST(BST B, VHeap V);

int main() {
	VHeap V;
	BST root;

	initializeVHeap(&V);
	displayVHeap(V);
	initializeBST(&root);

	elemType elem1 = {"Jin", 50};
	elemType elem2 = {"Kazuya", 45};
	elemType elem3 = {"Heihachi", 55};
	elemType elem4 = {"Jinpachi", 75};
	elemType elem5 = {"Lee", 12};
	elemType elem6 = {"Paul", 30};
	elemType elem7 = {"Victor", 21};
	elemType elem8 = {"Zafina", 72};
	elemType elem9 = {"Reina", 88};
	elemType elem10 = {"Asuka", 11};

	insert(&root, &V, elem1);
	insert(&root, &V, elem2);
	insert(&root, &V, elem3);
	insert(&root, &V, elem4);
	insert(&root, &V, elem5);
	insert(&root, &V, elem6);

	printf("\nVHeap After Insertion of Elements:\n");
	displayVHeap(V);
	printf("\nPreorder display of the BST:");
	displayBST(root, V);
	printf("\n\n");

	deleteNode(&root, &V, 50);
	deleteNode(&root, &V, 75);
	printf("\nPreorder display of the BST after deletion:");
	displayBST(root, V);
	printf("\n\n");
	printf("\nVHeap After Deletion of Elements:\n");
	displayVHeap(V);

	printf("\nInserting after deletion:");
	insert(&root, &V, elem7);
	insert(&root, &V, elem8);
	insert(&root, &V, elem9);
	insert(&root, &V, elem10);
	displayBST(root, V);
	printf("\n\n");
	displayVHeap(V);


}

void initializeVHeap(VHeap* V) {
	int i;
	for(i = -1; i < VH_SIZE; i++) {
		V->nodes[i+1].lc = i;
		V->nodes[i+1].rc = -1;
		V->nodes[i+1].elem.value = -2;
	}
	V->avail = VH_SIZE - 1;
}

void initializeBST(BST *B) {
	*B = -1;
}

BST allocSpace(VHeap* V) {
	BST retval = V->avail;
	if(V->avail != -1) {
		V->avail = V->nodes[retval].lc;
	}
	return retval;
}

void deallocSpace(VHeap* V, BST index) {
	if(index != -1 && index < VH_SIZE) {
		V->nodes[index].lc = V->avail;
		V->nodes[index].rc = -1;
		V->nodes[index].elem.value = -3;
		V->avail = index;
	}
}

void insert(BST *B, VHeap *V, elemType E) {
	BST *trav;
	if(V->avail != -1) {
		for(trav = B; *trav != -1 && V->nodes[*trav].elem.value != E.value;) {
			trav = (V->nodes[*trav].elem.value > E.value) ? &(V->nodes[*trav].lc) : &(V->nodes[*trav].rc);
		}
		BST index = allocSpace(V);
		V->nodes[index].elem = E;
		V->nodes[index].lc = -1;
		V->nodes[index].rc = -1;
		*trav = index;
	}
}

void deleteNode(BST *B, VHeap *V, int value) {
	BST *trav;
	for(trav = B; *trav != -1 && V->nodes[*trav].elem.value != value;) {
		trav = (V->nodes[*trav].elem.value > value) ? &(V->nodes[*trav].lc) : &(V->nodes[*trav].rc);
	}
	if(*trav != -1) {
		BST temp;
		if(V->nodes[*trav].lc == -1) {
			temp = *trav;
			*trav = V->nodes[*trav].rc;
		} else if(V->nodes[*trav].rc == -1) {
			temp = *trav;
			*trav = V->nodes[*trav].lc;
		} else {
			BST deletedNode = *trav;
			for(trav = &V->nodes[*trav].rc; V->nodes[*trav].lc != -1; trav = &V->nodes[*trav].lc) {}
			V->nodes[deletedNode].elem = V->nodes[*trav].elem;
			temp = *trav;
			*trav = V->nodes[*trav].rc;
		}
		deallocSpace(V, temp);
	}
}

void displayVHeap(VHeap V) {
	int i;
	printf("Showcasing the VHEAP\n");
	printf("Current Avail: %d\n", V.avail);
	printf("%-15s", "INDEX");
	printf("%-15s", "VALUE FIELD");
	printf("%-15s", "LC FIELD");
	printf("%-15s", "RC FIELD");
	printf("\n%-15s", "=====");
	printf("%-15s", "===========");
	printf("%-15s", "========");
	printf("%-15s", "========");

	for(i = 0; i < VH_SIZE; i++) {
		printf("\n%-15d", i);
		if(V.nodes[i].elem.value == -2) {
			printf("%-15s", "null");
		} else if (V.nodes[i].elem.value == -3) {
			printf("%-15s", "deleted");
		} else {
			printf("%-15d", V.nodes[i].elem.value);
		}
		printf("%-15d%-20d", V.nodes[i].lc, V.nodes[i].rc);
	}
	printf("\n");
}

void displayElem(elemType E) {
	printf("\n%-10s", E.name);
	printf("%-10d", E.value);
}

void displayBST(BST B, VHeap V) {
	if(B != -1) {
		displayElem(V.nodes[B].elem);
		displayBST(V.nodes[B].lc, V);
		displayBST(V.nodes[B].rc, V);
	}
}




