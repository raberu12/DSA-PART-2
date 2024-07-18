#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 9

typedef int Graph[MAX][MAX];

typedef struct{
	int v , w, weight;
}edge;

void initGraph(Graph *G);
void addEdge(Graph *G ,int v, int w, int weight);
void printGraph(Graph G);
int prim(Graph G, int start);

int main() {

	Graph G;
	initGraph(&G);

	addEdge(&G, 0, 1, 1);
	addEdge(&G, 2, 0, 10);
	addEdge(&G, 3, 1, 4);
	addEdge(&G, 2, 4, 5);
	addEdge(&G, 3, 4, 6);
	addEdge(&G, 2, 3, 3);

	printGraph(G);
	int minCostPrims = prim(G, 2);
	printf("\nThe Minimum Cost is %d", minCostPrims);
}

void initGraph(Graph *G) {
	int i, j;
	for(i = 0; i < MAX; i++) {
		for(j = 0; j < MAX; j++) {
			(*G)[i][j] = INT_MAX;
		}
	}
}

void addEdge(Graph *G, int v, int w, int weight) {
	if((*G)[v][w] == INT_MAX && (*G)[v][w] == INT_MAX) {
		(*G)[v][w] = weight;
		(*G)[w][v] = weight;
		printf("Successfully connected vectors %d and %d with a weight of %d!\n", v, w, (*G)[v][w]);
	} else {
		printf("Vectors %d and %d is already connected with a weight of %d\n", v, w, (*G)[v][w]);
	}
	printf("\n");
}

void printGraph(Graph G) {
	int i, j;
	for(i = 0; i < MAX; i++) {
		for(j = 0; j < MAX; j++) {
			G[i][j] != INT_MAX ? printf("%-6d ", G[i][j]) : printf("%-6s ", "INF");
		}
		printf("\n");
	}
}

int prim(Graph G, int start) {
	int selected[MAX] = {0};
	int minCost = 0;
	int i, j;
	
	selected[start] = 1;
	int numSelected = 1;
	int allSelected = 0; //flag to indicate all vertices are selected;
	
	printf("\nPrim's Algorithm running starting at VERTEX %d...\n", start);
	printf("Minimum Cost Spanning Tree via Prim's Algorithm:\n");
	while(!allSelected) {
		int minWeight = INT_MAX;
		int row = -1;
		int col = -1;
		for(i = 0; i < MAX; i++) {
			if(selected[i]) {
				for(j = 0; j < MAX; j++) {
					if(!selected[j] && G[i][j] < minWeight) {
						minWeight = G[i][j];
						row = i;
						col = j;
					}
				}
			}
		}
		if(row != -1 && col != -1) {
			selected[col] = 1;
			printf("\nEdge %d - %d, Weight: %d\n", row, col, minWeight);
			minCost += minWeight;
			numSelected++;
		} else {
			allSelected = 1;
		}
		if(numSelected >= MAX) {
			allSelected = 1;
		}
	}
	return minCost;
}






