//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 PA4
//Graph.h
//Header file for Graph.c

#ifndef GRAPH_H
#define GRAPH_H

#include<stdio.h>
#include "List.h"

#define INF -1
#define NIL 0
#define white 2
#define gray 4
#define black 8
#define UNDEF -1


typedef struct GraphObj* Graph;


Graph newGraph(int n);

void freeGraph(Graph* pG);


int getOrder(Graph G);

int getSize(Graph G);

//int getSource(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

//int getDist(Graph G, int u);

//void getPath(List L, Graph G, int u);

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

//void BFS(Graph G, int s);

void DFS(Graph G, List S);

void Visit(Graph G, List S, int v, int *q);

void printGraph(FILE* out, Graph G);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

#endif