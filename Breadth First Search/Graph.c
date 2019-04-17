//Patrick Stumps
//pstumps@ucsc.edu
//CMPS101
//Graph.c - PA4
//Graph ADT

#include<stdlib.h>
#include<stdio.h>
#include "Graph.h"

typedef struct GraphObj {
    
    List *adj;

    int *dist;
    int *col;
    int *par;

    int sauce;
    int order;
    int size;

} GraphObj;

//--- Constructors-Destructors ---

Graph newGraph(int n){

    if (n <= 0){
        printf("Cannot call new graph on empty graph (n < 1");
    }

    Graph graph = malloc(sizeof(GraphObj));

    graph->adj = calloc(n+1, sizeof(List));
    graph->dist = calloc(n+1, sizeof(int));
    graph->col = calloc(n+1, sizeof(int));
    graph->par = calloc(n+1, sizeof(int));

    graph->sauce = NIL;
    graph->order = n;
    graph->size = 0;

    for(int i=1; i<= n; i++){
        graph->adj[i] = newList();
        graph->dist[i]= INF; 
        graph->par[i] = NIL;
        graph->col[i] = 0;
    }

    return graph;

}

void freeGraph (Graph* pG){

    Graph g = *pG;

    for(int i=1; i<= getOrder(*pG); i++){
        freeList(&(g->adj[i]));
    }
    free(g->col);
    free(g->dist);
    free(g->par);
    free(g->adj);
    free(*pG);

    *pG = NULL;
}

//--- Access functions ---

int getOrder(Graph G){
    if(G == NULL){
        printf("Cannot call getOrder() on null graph.\n");
        exit(1);
    }

    return G->order;
}

int getSize(Graph G){
    if(G == NULL){
        printf("Cannot call getSize() on null graph.\n");
        exit(1);
    }

    return G->size;
}

int getSource(Graph G){
    if(G == NULL){
        printf("Cannot call getSource() on null graph.\n");
        exit(1);
    }

    return G->sauce;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("Cannot call getParent() on null graph.\n");
        exit(1);
    }

    if(u <= 0){
        printf("Cannot call getParent() with vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("Cannot call getParent with vertex not within vertices.\n");
        exit(1);
    }

    return G->par[u];

}

int getDist(Graph G, int u){
    if(G == NULL){
        printf("Cannot call getDist() on null graph.\n");
        exit(1);
    }

    if(u <= 0){
        printf("Cannot call getDist() with vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("Cannot call getDist() with vertex not within vertices.\n");
        exit(1);
    }

    if(getSource(G) == NIL){
        return INF;
    }

    return G->dist[u];
}

void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("Cannot call getPath() on null graph.\n");
        exit(1);
    }

    if(u <= 0){
        printf("Cannot call getPath() with vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("Cannot call getPath() with vertex not within vertices.\n");
        exit(1);
    }

    if(getSource(G) == NIL){
        printf("Cannot call getPath() on non-existant source.\n");
        exit(1);
    }

    if(G->sauce == u){
        append(L, u);
    }
    else if(G->par[u] == NIL){
        append(L, NIL);
    }
    else{
        getPath(L, G, G->par[u]);
        append(L, u);
    }

}

// --- Manipulation procedures ---

void makeNull (Graph G){
    if(G == NULL){
        printf("Cannot call makeNull() on NULL graph.\n");
        exit(1);
    }

    for(int i=1; i<= getOrder(G); i++){
        clear(G->adj[i]);
    }

    G->size = 0;
    G->sauce = NIL;

}

void addEdge(Graph G, int u, int v){
    /*if(G == NULL){
        printf("Cannot addEdge() to NULL graph.\n");
        exit(1);
    }*/

    if(u < 1){
        printf("Cannot addEdge() on vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("Cannot addEdge() on vertex greater than graph order.\n");
        exit(1);
    }

    if(v < 1){
        printf("Cannot addEdge() on v not within vertices.\n");
        exit(1);
    }

    if(v > getOrder(G)){
        printf("Cannot addEdge() on v greater than graph order.\n");
        exit(1);
    }

    List lV = G->adj[v];
    List lU = G->adj[u];
    moveFront(lU);

    int flag = 0;

    while(index(lU) != -1 && flag == 0){
        int curr = get(lU);
        if(curr < v){
            moveNext(lU);
        }
        else{
            insertBefore(lU, v);
            flag = 1;
        }
    }

    if(index(lU) == -1){
        append(lU, v);
    }

    flag = 0;

    moveFront(lV);

    while(index(lV) != -1 && flag == 0){
        int curr = get(lV);
        if(curr < u){
            moveNext(lV);
        }
        else{
            insertBefore(lV, u);
            flag = 1;
        }
    }

    if(index(lV) == -1){
        append(lV, u);
    }

    G->size++;
}

void addArc(Graph G, int u, int v){
    /*if(G == NULL){
        printf("Cannot addArc() to NULL graph.\n");
        exit(1);
    }*/

    if(u < 1){
        printf("Cannot addArc() on vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("Cannot addArc() on vertex greater than graph order.\n");
        exit(1);
    }

    if(v < 1){
        printf("Cannot addArc() on v not within vertices.\n");
        exit(1);
    }

    if(v > getOrder(G)){
        printf("Cannot addArc() on v greater than graph order.\n");
        exit(1);
    }

    List L = G->adj[u];
    moveFront(L);

    int flag = 0;

    while(index(L) != -1 && flag == 0){
        int curr = get(L);
        if(curr < v){
            moveNext(L);
        }
        else{
            insertBefore(L, v);
            flag = 1;
        }
    }

    if(index(L) == -1){
        append(L, v);
    }

    G->size++;
   
}

void BFS(Graph G, int s){
    if( G == NULL){
        printf("Cannot call BFS on NULL graph.\n");
        exit(1);
    }

    if(s < 1){
        printf("Cannot call BFS on vertex out of bounds (s < 1).\n");
        exit(1);
    }

    if(s > getOrder(G)){
        printf("Cannot call BFS on vertex out of bounds (s > order)\n");
        exit(1);
    }

    for(int i=1; i<= getOrder(G); i++){
        G->col[i] = 0;
        G->dist[i] = INF;
        G->par[i] = NIL;
    }

    G->par[s] = NIL;
    G->dist[s] = 0;
    G->col[s] = 1;
    G->sauce = s;

    List q = newList();

    append(q, s);

    while(length(q) > 0){
        
        int top = front(q);
        deleteFront(q);

        for(moveFront(G->adj[top]); index(G->adj[top]) != -1; moveNext(G->adj[top])){
            int cur = get(G->adj[top]);

            if(G->col[cur] == 0){ //if white
                G->col[cur] = 1;
                G->dist[cur] = G->dist[top] + 1;
                G->par[cur] = top;
                append(q, cur);
            }
        }

        G->col[top] = 2;
    }

    freeList(&q);

}

void printGraph(FILE* out, Graph G){
    if(out == NULL){
        printf("Cannot call printGraph() on NULL outfile.\n");
        exit(1);
    }

    if(G == NULL){
        printf("Cannot call printGraph() on NULL graph.\n");
        exit(1);
    }

    for(int i=1; i<= getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }

}