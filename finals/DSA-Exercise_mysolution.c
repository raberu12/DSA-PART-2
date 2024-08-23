#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VH_SIZE 0XC     // size of Virtual Heap
#define ARRAY_SIZE 0XE   // size of the array implementation of List
#define CLOSE_DSIZE 0XB

/******************************************************************************
* Data Structure Definition:                                                  *
******************************************************************************/
typedef struct{
	char model[30];
	char manufacturer[40]; // Airbus, Textron Aviation, Boeing
	int passengerCount;
	int year;
}planeDesc;

typedef struct{
	char planeID[8];
	planeDesc planeInfo;
	float planePrice;
	int maxSpeed;
}Aircraft;

typedef struct {
	Aircraft data;
	int next;
}PlaneNode;

/************************
* Virtual Heap          *
************************/
typedef struct {
	PlaneNode VH_Node[VH_SIZE];
	int avail;
}VHeap;

/******************************************
* Cursor-Based Implementation of LIST     *
******************************************/
typedef struct CList{
	int elemIndex; // index of the 1st element in the set
	int count;     // holds the actual number of elements in the list
	VHeap *VHptr;  // holds the pointer to the virtual heap
}*CursorList;

/******************************************
* Array Implementation of LIST  		  *
******************************************/
typedef struct ArrList{
	Aircraft data[ARRAY_SIZE];
	int count; // holds the actual number of elements in the list
}*ArrayList;


typedef struct node{
	Aircraft elem;
	struct node *link;
}*LinkedList;

/******************************************
* Linked List Implementation of QUEUE 	  *
******************************************/
typedef struct {
	LinkedList front;
	LinkedList rear;
}LinkedQueue;

/**********************************************
* Closed Hashing with 2 pass loading          *
**********************************************/
#define EMPTY "emp" // stored in product ID field
#define DELETED "del" // stored in product ID field *

typedef Aircraft CloseDic[CLOSE_DSIZE]; // Definition of the closed hash dictionary

/**********************************************************
* Function Prototypes                                    *
*********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);
CursorList initCursorList(VHeap *VH);
ArrayList initArrayList();
void displayVHeap(VHeap V);
void displayArrayList(ArrayList A);
void displayCursorList(CursorList C);

//---Problem #2 ---
void populateArrayList(ArrayList *A);
int populateCListSorted(ArrayList *A, CursorList *C); // Inserts element from array list to cursor list sorted if the manufacturer is Airbus OR Textron Aviation. Returns the number of elements inserted.
int allocSpace(VHeap *VH);

//---Problem #3 ---
void initQueue(LinkedQueue *Q);
void freeSpace(VHeap *VH, int ndx);
void enqueueFromCList(LinkedQueue *Q, CursorList *C);

//---Problem #4 ---
int closeHash(char ID[]);
void initCloseDic(CloseDic CD);
Aircraft dequeue(LinkedQueue *Q);
CloseDic *convertToCloseDic(LinkedQueue *Q);
void displayCloseDic(CloseDic CD);

int main(){
	// Variable Declaration for all problems here
	ArrayList A;
	CursorList B;
	LinkedQueue C;
	CloseDic *D;
	VHeap V;
	
	/*--------------------------------------------------------------------------------------------
    * 	Problem #1 ::  1) Initializes the virtual heap, the array list and the cursor list        *
    *                  2) Displays the contents virtual heap, the array list and the cursor list  *
    *---------------------------------------------------------------------------------------------*/
    printf("\n\n\nProblem #1:: ");
    printf("\n------------");
	initVHeap(&V);
	A = initArrayList();
	B = initCursorList(&V);
	displayVHeap(V);
	displayArrayList(A);
	displayCursorList(B);
	
	printf("\n");
	system("pause");
	system("cls");
	
	/*--------------------------------------------------------------------------------------------
    * 	Problem #2 ::  1) Populates and displays the array list  						          *
    *                  2) Populates the cursor list which is sorted in ascending order according  *
	*                     to ID from a given array list if the Aircraft was manufactured by       *
	*                     Airbus or Textron Aviation                                              *
	*                  3) Displays the virtual heap, the cursor list and the array list again     *
	*                     after transfering the data to the cursor list                           *
    *---------------------------------------------------------------------------------------------*/
    printf("\n\n\nProblem #2:: ");
    printf("\n------------");
	populateArrayList(&A);
	displayArrayList(A);
	populateCListSorted(&A, &B);
	displayArrayList(A);
	displayVHeap(V);
	displayCursorList(B);
	
	printf("\n\n");
	system("pause");
	system("cls");
	
	/*--------------------------------------------------------------------------------------------
    * 	Problem #3 ::  1) Initializes the queue                                                   *
    *                  2) Transfers the data from the cursor list to a queue                      *
    *                  3) Displays the empty cursor list and virtual heap                         *
    *---------------------------------------------------------------------------------------------*/
    printf("\n\n\nProblem #3:: ");
    printf("\n------------");
	initQueue(&C);
	enqueueFromCList(&C, &B);
	displayCursorList(B);
	displayVHeap(V);
	
	printf("\n\n");
	system("pause");
	system("cls");
	
	/*--------------------------------------------------------------------------------------------
    * 	Problem #4 ::  1) Empties the queue and transfers all of its data to a close hash         *
	*                     dictionary                                                              *
    *                  2) Displays the close hash dictionary                                      *
    *---------------------------------------------------------------------------------------------*/
    printf("\n\n\nProblem #4:: ");
    printf("\n------------");
	D = convertToCloseDic(&C);
	displayCloseDic(*D);
	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                        *
 ************************************************************/
void initVHeap(VHeap *VH){
	int x;
	for(x = 0; x < VH_SIZE; x++){
		VH->VH_Node[x].next = x - 1;
		strcpy(VH->VH_Node[x].data.planeID, "");
	}
	VH->avail = x - 1;
}
CursorList initCursorList(VHeap *VH){
	CursorList C;
	C = (CursorList)malloc(sizeof(struct CList));
	if(C != NULL){
		C->count = 0;
		C->elemIndex = -1;
		C->VHptr = VH;
	}
	return C;
}
ArrayList initArrayList(){
	ArrayList A;
	A = (ArrayList)malloc(sizeof(struct ArrList));
	if(A != NULL){
		A->count = 0;
	}
	return A;
}
void displayVHeap(VHeap VH){
	// Variable Declaration here
	int x;
	
	printf("\n\nDetails of the Virtual Heap :: ");
	printf("\n------------------------------");
	printf("\nAvailable Index  ::  %d", VH.avail); // Complete this statement
	printf("\nVHeap Address    ::  %x", VH);       // Complete this statement
	
	printf("\n\n%10s", "Index");
	printf("%10s", "Plane ID");
	printf("%15s", "Next Field");
	printf("\n%10s%10s%15s", "-----", "-------", "----------");
	for(x = 0; x < VH_SIZE; x++){
		printf("\n%10d%10s%15d", x, VH.VH_Node[x].data.planeID, VH.VH_Node[x].next);
	}

}
void displayArrayList(ArrayList A){
	int x;
	printf("\n\nDetails of the Array List :: ");
	printf("\n---------------------");
	printf("\nNo. of Elements :: %d", A->count);
	printf("\n\n%-8s", "Index");
	printf("%-9s", "ID");
	printf("%-15s", "Plane Model");
	printf("%-25s", "Plane Manufacturer");
	printf("\n%-7s%-10s%-15s%-25s", "-----", "-----", "-----------", "------------------");
	
	// Write your code here
	for(x = 0; x < A->count; x++){
		printf("\n%-7d%-10s%-15s%-25s", x, A->data[x].planeID, A->data[x].planeInfo.model, A->data[x].planeInfo.manufacturer);
	}
}
void displayCursorList(CursorList C){
	int trav;
	printf("\n\nDetails of the Cursor List :: ");
	printf("\n---------------------");
	printf("\nNo. of Elements :: %d", C->count);
	printf("\n\n%-7s", "ID");
	printf("%-15s", "Plane Model");
	printf("%-25s", "Plane Manufacturer");
	printf("%-10s", "VHeap Index");
	printf("\n%-7s%-15s%-25s%-10s", "--", "----------", "------------------",
         "-----------");
	for(trav = C->elemIndex; trav != -1; trav = C->VHptr->VH_Node[trav].next){
		printf("\n%-7s%-15s%-25s%-10d", C->VHptr->VH_Node[trav].data.planeID, C->VHptr->VH_Node[trav].data.planeInfo.model, C->VHptr->VH_Node[trav].data.planeInfo.manufacturer, trav);
	}
}

/************************************************************
 *  Problem 2:: Function Definitions                        *
 ************************************************************/
void populateArrayList(ArrayList *A) {
	int COUNT = 15;
	Aircraft data[] = {{"17839",{"A330", "Airbus", 150, 2012}, 300000, 250},
					   {"18367",{"737 MAX", "Boeing", 200, 2021}, 150000, 275},
					   {"23748",{"BBJ", "Boeing", 175, 2020}, 275000, 290},
					   {"16790",{"Caravan", "Textron Aviation", 100, 2017}, 125000, 315},
					   {"17489",{"A350", "Airbus", 175, 2020}, 310000, 270},
					   {"17839",{"A400M", "Airbus", 140, 2013}, 175000, 220},
					   {"16778",{"Caravan", "Textron Aviation", 140, 2018}, 165000, 310},
					   {"23748",{"300F", "Boeing", 180, 2022}, 140000, 250},
					   {"17888",{"Beechcraft", "Textron Aviation", 175, 2019}, 180000, 220},
					   {"13435",{"BBJ", "Boeing", 190, 2021}, 180000, 280},
					   {"15049",{"Denali", "Textron Aviation", 205, 2017}, 190000, 230},
					   {"17888",{"A330", "Airbus", 180, 2021}, 290000, 200},
					   {"18367",{"KC-767", "Boeing", 200, 2022}, 220000, 240},
					   {"16790",{"737 MAX", "Boeing", 340, 2023}, 430000, 220},
					   {"23929",{"A400M", "Airbus", 300, 2019}, 300000, 340}};
	int x;
	// Inserts each element of the array to the array list
    // Write your code here!!
    for(x = 0; x < COUNT; x++){
    	if((*A)->count < ARRAY_SIZE){
    		(*A)->data[(*A)->count++] = data[x];
		}
	}
}

int populateCListSorted(ArrayList *A, CursorList *C){
	int insCount = 0;
	int *trav, node;
	int x, y;
	for(x = 0; x < (*A)->count;){
		for(trav = &(*C)->elemIndex; *trav != -1 && strcmp((*C)->VHptr->VH_Node[*trav].data.planeID, (*A)->data[x].planeID) < 0; trav = &(*C)->VHptr->VH_Node[*trav].next){}
		if(strcmp((*A)->data[x].planeInfo.manufacturer, "Boeing") != 0 && (*C)->VHptr->avail != -1){
			node = allocSpace((*C)->VHptr);
			(*C)->VHptr->VH_Node[node].data = (*A)->data[x];
			(*C)->VHptr->VH_Node[node].next = *trav;
			*trav = node;
			(*C)->count++;
			insCount++;
			(*A)->count--;
			for(y = x; y < (*A)->count; y++){
				(*A)->data[y] = (*A)->data[y+1];
			}
		} else{
			x++;
		}
	}
	
	return insCount;
}
int allocSpace(VHeap *VH){
	int avail = VH->avail;
	if(avail != -1){
		VH->avail = VH->VH_Node[avail].next;
	}
	return avail;
}

/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
void initQueue(LinkedQueue *Q){
	Q->front = NULL;
	Q->rear = NULL;
}
void freeSpace(VHeap *VH, int ndx){
	if(ndx >= 0 && ndx < VH_SIZE){
		VH->VH_Node[ndx].next = VH->avail;
		VH->avail = ndx;
	}
}
void enqueueFromCList(LinkedQueue *Q, CursorList *C){
	int *trav, node;
	LinkedList linkNode;
	while((*C)->elemIndex != -1){
		for(trav = &(*C)->elemIndex; *trav != -1;){
			node = *trav;
			*trav = (*C)->VHptr->VH_Node[node].next;
			linkNode = (LinkedList)malloc(sizeof(struct node));
			if(linkNode != NULL){
				linkNode->elem = (*C)->VHptr->VH_Node[node].data;
				linkNode->link = NULL;
				if(Q->front == NULL){
					Q->front = linkNode;
				}else{
					Q->rear->link = linkNode;
				}
				Q->rear = linkNode;
			}
			strcpy((*C)->VHptr->VH_Node[node].data.planeID, "");
			freeSpace((*C)->VHptr, node);
			(*C)->count--;
		}
	}
}

/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
int closeHash(char ID[]){
	int x, sum = 0;
	for(x = 0; ID[x]; x++){
		sum = sum + (ID[x] - '0');
	}
	return sum % CLOSE_DSIZE;
}

void initCloseDic(CloseDic CD){
	int x;
	for(x = 0; x < CLOSE_DSIZE; x++){
		strcpy(CD[x].planeID, EMPTY);
		strcpy(CD[x].planeInfo.model, "");
	}
}

Aircraft dequeue(LinkedQueue *Q){
	LinkedList node;
	Aircraft data;
	if(Q->front != NULL){
		node = Q->front;
		Q->front = node->link;
		data = node->elem;
		free(node);
		if(Q->front == NULL){
			Q->rear = NULL;
		}
	}	
	return data;
}
CloseDic *convertToCloseDic(LinkedQueue *Q){
	CloseDic *C;
	ArrayList A;
	Aircraft elem;
	int hashNdx, x, y, count, scan;
	C = (CloseDic*)malloc(sizeof(CloseDic));
	if(C != NULL){
		initCloseDic(*C);
		A = initArrayList();
		
		// 1st round
		while(Q->front != NULL){
			elem = dequeue(Q);
			hashNdx = closeHash(elem.planeID);
			if(strcmp((*C)[hashNdx].planeID, EMPTY) == 0){
				(*C)[hashNdx] = elem;
			} else {
				A->data[A->count++] = elem;
			}
		}
		
		// 2nd round
		for(x = 0; x < A->count;){
			hashNdx = closeHash(A->data[x].planeID);
			for(count = 0; count < CLOSE_DSIZE && strcmp((*C)[hashNdx].planeID, EMPTY) != 0; count++, hashNdx = (hashNdx + 1) % CLOSE_DSIZE){}
			for(scan = 0; scan < CLOSE_DSIZE && strcmp((*C)[scan].planeID, A->data[x].planeID) != 0; scan++){}
			if(count != CLOSE_DSIZE && scan == CLOSE_DSIZE){
				(*C)[hashNdx] = A->data[x];
				for(y = 0; y < A->count - 1; y++){
					A->data[y] = A->data[y+1];
				}
				A->count--;
			} else{
				x++;
			}
		}
	}
	return C;
}
void displayCloseDic(CloseDic CD){
	// Variable declaration here
	int x;
	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "PlaneID");
	printf("%-15s", "Plane Model");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------");
	
	for(x = 0; x < CLOSE_DSIZE; x++){
		printf("\n%-6d%-10s%-15s", x, CD[x].planeID, CD[x].planeInfo.model);
	}
}

