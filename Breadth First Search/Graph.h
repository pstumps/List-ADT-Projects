//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 PA4
//Graph.h
//Header file for Graph.c

#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE

#define INF -100000
#define NIL 0

#include "List.h"


typedef struct GraphObj* Graph;


Graph newGraph(int n);

void freeGraph(Graph* pG);


int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);


void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);


void printGraph(FILE* out, Graph G);

#endif