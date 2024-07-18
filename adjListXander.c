#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define VISITED -1
#define UNVISITED -2

typedef struct {
	int head;
	int weight;
	int tail;
} adjType;

typedef struct node {
	adjType elem;
	struct node *link;
} *ptr, nodeType;

typedef struct {
	int elem[MAX];
	int front, rear;
} Queue;

typedef struct {
	ptr adjList[MAX];
	int edgecount;
} Graph;

void initGraph(Graph *G);
void DFS(Graph C, int vertex, int mark[]);
void BFS(Graph G, int start);
void addEdge(Graph *G, adjType A);
void displayGraph(Graph G);

int main() {
	Graph G;
	initGraph(&G);

	adjType A = {4, 5, 10};

	addEdge(&G, A);




	displayGraph(G);

	return 0;
}

Queue initQueue() {
	Queue Q;
	Q.front = 0;
	Q.rear = 0;

	return Q;
}

void initGraph(Graph *G) {
	int i;
	for (i = 0; i < MAX; i++) {
		G->adjList[i] = NULL;
	}
}

void DFS(Graph C, int vertex, int mark[]) {
	ptr trav;
	printf("Visiting Vertex %d\n", vertex);
	mark[vertex] = VISITED;
	for (trav = C.adjList[vertex]; trav != NULL; trav = trav->link) {
		if (mark[trav->elem.head] == UNVISITED) {
			DFS(C, trav->elem.head, mark);
		}
	}
}

void BFS(Graph G, int start) {
	Queue Q = initQueue();
	ptr trav;
	int mark[MAX];
	// Enqueue the starting vertex and mark it as visited
	Q.elem[Q.rear++] = start;
	mark[start] = VISITED;

	while (Q.front != Q.rear) {
		int vertex = Q.elem[Q.front++]; // Dequeue a vertex
		printf("Visiting Vertex %d\n", vertex);

		// Traverse all adjacent vertices of the dequeued vertex
		for (trav = G.adjList[vertex]; trav != NULL; trav = trav->link) {
			if (mark[trav->elem.head] == UNVISITED) {
				Q.elem[Q.rear++] = trav->elem.head;
				mark[trav->elem.head] = VISITED;
			}
		}
	}
}

// void addEdge(Graph *G, int head, int tail, int weight) {
//   ptr newNode = (ptr)malloc(sizeof(nodeType));
//   ptr newNode2 = (ptr)malloc(sizeof(nodeType));

//   if (newNode != NULL && newNode2 != NULL) {
//     newNode->elem.head = tail;
//     newNode->elem.weight = weight;
//     newNode->link = G->adjList[head];
//     G->adjList[head] = newNode;

//     newNode2->elem.head = head;
//     newNode2->elem.weight = weight;
//     newNode2->link = G->adjList[tail];
//     G->adjList[tail] = newNode2;

//     G->edgecount++;
//   }
// }

void addEdge(Graph *G, adjType A) {
	ptr newNode = (ptr)malloc(sizeof(nodeType));
	ptr newNode2 = (ptr)malloc(sizeof(nodeType));

	ptr *trav;

	if(newNode2!=NULL && newNode!=NULL) {
		for(trav = &G->adjList[A.head]; *trav!=NULL; trav = &(*trav)->link) {}
		newNode->elem.head = A.head;
		newNode->elem.weight = A.weight;
		newNode->elem.tail = A.tail; // Set the tail field
		*trav = newNode;

		for (trav = &G->adjList[A.tail]; *trav != NULL; trav = &(*trav)->link) {}
		newNode2->elem.head = A.tail;
		newNode2->elem.weight = A.weight;
		newNode2->elem.tail = A.head; // Set the head field
		*trav = newNode2;
		G->edgecount++;
	}
}


void displayGraph(Graph G) {
	printf("\n\nThe Adjacency List ::");
	printf("\n%-8s", "VERTEX");
	printf("%-20s", "Adjacent vertices (weight)");
	printf("\n%-8s", "------");
	printf("%-20s", "------------------------");

	ptr trav;
	int i;
	for (i = 0; i < MAX; i++) {
		printf("\n%-8d", i);
		for (trav = G.adjList[i]; trav != NULL; trav = trav->link) {
			printf(" -> (%d)", trav->elem.head);
		}
	}
}
