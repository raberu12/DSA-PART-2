#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int label;
	struct node *left;
	struct node *right;
} treeNode, *BST;

void initTree(BST *T);
void insert(BST *T, int label);
void search(BST T, int label);
void deleteNodePred(BST *T, int label); //immediate predecessor version
void deleteNodeSucc(BST *T, int label); //immediate successor version
void Preorder(BST T);

int main() {
	BST T;
	
	initTree(&T);
	insert(&T, 10);
	insert(&T, 15);
	insert(&T, 5);
	insert(&T, 4);
	insert(&T, 7);
	insert(&T, 3);
	insert(&T, 1);
	insert(&T, 2);
	insert(&T, 6);
	insert(&T, 8);
	insert(&T, 12);
	insert(&T, 16);
	printf("Preorder Display of the Tree\n");
	Preorder(T);
	deleteNodePred(&T, 10);
	printf("\n\nTree After Deletion of the Root\n");
	Preorder(T);
	deleteNodePred(&T, 16);
	printf("\n\nTree After Deletion of a Leaf\n");
	Preorder(T);
	deleteNodePred(&T, 3);
	printf("\n\nTree After Deletion of a node with 1 Child\n");
	Preorder(T);

}


void initTree(BST *T){
	*T = NULL;
}

void insert(BST *T, int label) {
	BST temp;
	BST *trav;
	for(trav = T; *trav != NULL && (*trav)->label != label;) {
		trav = (*trav)->label > label ? &(*trav)->left : &(*trav)->right;
	}
	if(*trav == NULL) {
		temp = (BST)malloc(sizeof(treeNode));
		if(temp != NULL) {
			temp->label = label;
			temp->left = NULL;
			temp->right = NULL;
			*trav = temp;
		}
	}
}

void search(BST T, int label){
	BST trav;
	for(trav = T; trav != NULL && trav->label != label;){
		trav = ((trav->label < label)) ? trav->right : trav->left;
	}
	if(trav->label == label){
		printf("The element exists!");
	}else{
		printf("The element does not exist!");
	}
}

void deleteNodePred(BST *T, int label){
	BST temp;
	BST *trav;
	for(trav = T; *trav != NULL && (*trav)->label != label;){
		trav = ((*trav)->label < label) ? &(*trav)->right : &(*trav)->left;
	}
	if((*trav)->left == NULL){
		temp = *trav;
		*trav = (*trav)->right;
	}else if((*trav)->right == NULL){
		temp = *trav;
		*trav = (*trav)->left;
	}else{
		BST deleteNode = *trav;
		for(trav = &(*trav)->left; (*trav)->right != NULL; trav = &(*trav)->right){}
		deleteNode->label = (*trav)->label;
		temp = *trav;
		*trav = temp->left;	
    }
	free(temp);
}

void deleteNodeSucc(BST *T, int label);

void Preorder(BST T){
	if(T != NULL){
		printf("%d ", T->label);
		Preorder(T->left);
		Preorder(T->right);
	}
}


