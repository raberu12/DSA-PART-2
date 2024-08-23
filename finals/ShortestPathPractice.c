#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V 5
#define INF INT_MAX

typedef int Graph[V][V];
typedef int set[V];

void initGraph(Graph* G);
void addEdge(int v, int w, int weight, Graph *G);
void populateGraph(Graph *G);
int minEdge(int *D, set S);
int *dijkstraAlgo(Graph G, int startVertex);
void printGraph(Graph G, char *s);
void printShortPath(int *D, char* s);
void FloydAlgo(Graph G, Graph *F);
void WarshallAlgo(Graph *G);

int main() {
	Graph myGraph;
	initGraph(&myGraph);
	populateGraph(&myGraph);
	printGraph(myGraph, "Graph");

	int *D = dijkstraAlgo(myGraph, 0);
	printShortPath(D, "Using Dijkstra's Algorithm starting from Vertex 0");

	Graph shortPaths;
	initGraph(&shortPaths);
	FloydAlgo(myGraph, &shortPaths);
	printGraph(shortPaths, "Shortest Paths For Each Vertex");
}

void initGraph(Graph* G) {
	int i, j;
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			(*G)[i][j] = INF;
		}
	}
}

void addEdge(int v, int w, int weight, Graph *G) {
	if(v < V && w < V) {
		if((*G)[v][w] == INF) {
			(*G)[v][w] = weight;
			printf("Arc with weight %d connected to vertices %d --> %d\n\n", weight, v, w);
		} else {
			printf("Vertices %d--%d is already connected with weight %d\n\n", v, w, (*G)[v][w]);
		}
	} else {
		printf("Vertices %d--%d cannot exist in the Graph\n\n", v , w);
	}
}

void populateGraph(Graph *G) {
	addEdge(0, 1, 10, G);
	addEdge(0, 3, 30, G);
	addEdge(0, 4, 100, G);
	addEdge(1, 2, 50, G);
	addEdge(2, 0 ,20, G);
	addEdge(2, 4, 10, G);
	addEdge(3, 2, 20, G);
	addEdge(3, 4, 60, G);
	printf("Graph has been populated!\n\n");
}

int minEdge(int *D, set S) {
	int min = INF;
	int min_index = -1;
	int v;
	for(v = 0; v < V; v++) {
		if(!S[v] && D[v] <= min) {
			min = D[v];
			min_index = v;
		}
	}
	return min_index;
}

int *dijkstraAlgo(Graph G, int startVertex) {
	int *D = (int*)malloc(sizeof(int)*V);
	if(D != NULL) {
		int i;
		for(i = 0; i < V; i++) {
			D[i] = INF;
		}
		set S = {0};

		D[startVertex] = 0;
		printf("Running Dijkstra's Algorithm...\n\n");
		for(i = 0; i < V - 1; i++) {
			int w = minEdge(D, S);
			S[w] = 1;
			int v;
			for(v = 0; v < V; v++) {
				if(!S[v] && G[w][v] != INF && D[w] != INF && D[w] + G[w][v] < D[v]) {
					D[v] = D[w] + G[w][v];
				}
			}
		}
	}
	return D;
}

void printGraph(Graph G, char* s) {
	printf("Displaying the Matrix(%s):\n\n", s);
	int i, j;
	printf("  ");
	for(i = 0; i < V; i++) {
		printf("%5d ", i);
	}
	printf("\n\n");
	for(i = 0; i < V; i++) {
		printf("%d ", i);
		for(j = 0; j < V; j++) {
			G[i][j] != INF ? printf("%5d ", G[i][j]) : printf("%5c ", 236);
		}
		printf("\n\n");
	}
}

void printShortPath(int *D, char* s) {
	printf("Showing shortest path (%s):\n\n", s);
	int i;
	printf("%5s", "Dest");
	printf("%5s", "Cost");
	for(i = 0; i < V; i++) {
		printf("\n%5d", i);
		printf("%5d", D[i]);
	}
	printf("\n\n");
}

void FloydAlgo(Graph G, Graph *F) {
	int i, j, k;
	for(i = 0; i < V; i++) {
		for(j = 0; j < V; j++) {
			(*F)[i][j] = G[i][j];
		}
	}
	for(i = 0; i < V; i++) {
		(*F)[i][i] = 0;
	}
	printf("Running Floyd's Algorithm...\n\n");
	for(k = 0; k < V; k++) {
		for(i = 0; i < V; i++) {
			for(j = 0; j < V; j++) {
				if((*F)[i][k] + (*F)[k][j] < (*F)[i][j] && (*F)[i][k] != INF && (*F)[k][j] != INF) {
					(*F)[i][j] =(*F)[i][k] + (*F)[k][j];
				}
			}
		}
	}
}

