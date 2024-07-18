#include <stdio.h>
#include <stdlib.h>
#define V 5

typedef struct edge {

	int dest;
	int weight;

} EdgeType;

typedef struct node {
	EdgeType edge;
	struct node *link;
}*LL, nodeType;

typedef struct list {
	LL adjList[V];
	int edgeCount;
} Graph;

void initAdjList(Graph *G);
void addEdge(Graph *G, int src, int dest, int weight);
void printGraph(Graph G);

int main() {
	Graph G;
	initAdjList(&G);
	addEdge(&G, 0, 2, 3);
	addEdge(&G, 2, 1, 4);
	addEdge(&G, 1, 4, 10);
	addEdge(&G, 1, 3, 7);
	printGraph(G);
}

void initAdjList(Graph *G) {
	int i = 0;
	for(i = 0; i < V; i++) {
		G->adjList[i] = NULL;
	}
	G->edgeCount = 0;
}
void addEdge(Graph *G, int src, int dest, int weight) {
	LL temp, temp2, *trav, *trav2;

	for(trav = &G->adjList[src]; *trav != NULL; trav = &(*trav)->link) {}
	for(trav2 = &G->adjList[dest]; *trav2 != NULL; trav2 = &(*trav2)->link) {}

	temp = (LL)malloc(sizeof(nodeType));
	temp2 = (LL)malloc(sizeof(nodeType));
	if(temp != NULL && temp2 != NULL) {
		temp->edge.dest = dest;
		temp->edge.weight = weight;
		temp->link = *trav;
		*trav = temp;

		temp2->edge.dest = src;
		temp2->edge.weight = weight;
		temp2->link = *trav2;
		*trav2 = temp2;
	}
}

void printGraph(Graph G) {
	int i;
	LL trav;
	printf("Vertex -> (Dest)[Weight]\n\n");
	for(i = 0; i < V; i++){
		printf("%d", i);
		for(trav = G.adjList[i]; trav != NULL; trav = trav->link){
			printf(" -> (%d)[%d]", trav->edge.dest, trav->edge.weight);
		}
		printf("\n");
	}
}
