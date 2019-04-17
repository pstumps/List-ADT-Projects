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

    int *disc;
    int *col;
    int *par;
    int *fin;

    //int sauce;
    int order;
    int size;
    //int time;

} GraphObj;

//--- Constructors-Destructors ---

Graph newGraph(int n){

    if (n <= 0){
        printf("\nCannot call new graph on empty graph (n < 1)\n");
        exit(1);
    }

    Graph graph = malloc(sizeof(GraphObj));

    graph->adj = calloc(n+1, sizeof(List));
    graph->disc = calloc(n+1, sizeof(int));
    graph->col = calloc(n+1, sizeof(int));
    graph->par = calloc(n+1, sizeof(int));
    graph->fin = calloc(n+1, sizeof(int));

    //graph->sauce = NIL;
    graph->order = n;
    graph->size = 0;
    //graph->time = 0;

    for(int i=1; i<= n; i++){
        graph->adj[i] = newList();
        graph->disc[i]= INF; 
        graph->par[i] = NIL;
        graph->col[i] = white;
        graph->fin[i] = UNDEF;
    }

    return graph;

}

void freeGraph (Graph* pG){

    for(int i=1; i<= getOrder(*pG); i++){
        freeList(&((*pG)->adj[i]));
    }
    free((*pG)->col);
    free((*pG)->disc);
    free((*pG)->par);
    free((*pG)->adj);
    free((*pG)->fin);
    free(*pG);

    *pG = NULL;
}

//--- Access functions ---

int getOrder(Graph G){
    if(G == NULL){
        printf("\nCannot call getOrder() on null graph.\n");
        exit(1);
    }

    return G->order;
}

int getSize(Graph G){
    if(G == NULL){
        printf("\nCannot call getSize() on null graph.\n");
        exit(1);
    }

    return G->size;
}

//Removed for PA5
/*int getSource(Graph G){
    if(G == NULL){
        printf("\nCannot call getSource() on null graph.\n");
        exit(1);
    }

    return G->sauce;
}
*/

int getParent(Graph G, int u){
    if(G == NULL){
        printf("\nCannot call getParent() on null graph.\n");
        exit(1);
    }

    if(u <= 0){
        printf("\nCannot call getParent() with vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("\nCannot call getParent with vertex not within vertices.\n");
        exit(1);
    }

    return G->par[u];

}

int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("\nCannot call getDiscover() on null graph.\n");
        exit(1);
    }

    if(u <= 0){
        printf("\nCannot call getDiscover() with vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("\nCannot call getDiscover() with vertex not within vertices.\n");
        exit(1);
    }

    /*if(getSource(G) == NIL){
        return INF;
    }
    */

    return G->disc[u];
}

int getFinish(Graph G, int u){
    if(G == NULL){
        printf("\nCannot call getFinish() on null graph.\n");
        exit(1);
    
    }

    if(u <= 0){
        printf("\nCannot call getFinish() on vertex less than 1. (Out of bounds)");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("\nCannot call getFinish() on vertex greater than graph order. (Not within vertices).");
        exit(1);

    }

    return G->fin[u];

    
}

//Removed for PA5.
/*void getPath(List L, Graph G, int u){
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
*/

// --- Manipulation procedures ---

void makeNull (Graph G){
    if(G == NULL){
        printf("\nCannot call makeNull() on NULL graph.\n");
        exit(1);
    }

    for(int i=1; i<= getOrder(G); i++){
        clear(G->adj[i]);
    }

    G->size = 0;
    //G->sauce = NIL;

}

void addEdge(Graph G, int u, int v){
    /*if(G == NULL){
        printf("Cannot addEdge() to NULL graph.\n");
        exit(1);
    }*/

    if(u < 1){
        printf("\nCannot addEdge() on vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("\nCannot addEdge() on vertex greater than graph order.\n");
        exit(1);
    }

    if(v < 1){
        printf("\nCannot addEdge() on v not within vertices.\n");
        exit(1);
    }

    if(v > getOrder(G)){
        printf("\nCannot addEdge() on v greater than graph order.\n");
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
        printf("\nCannot addArc() on vertex less than 1.\n");
        exit(1);
    }

    if(u > getOrder(G)){
        printf("\nCannot addArc() on vertex greater than graph order.\n");
        exit(1);
    }

    if(v < 1){
        printf("\nCannot addArc() on v not within vertices.\n");
        exit(1);
    }

    if(v > getOrder(G)){
        printf("\nCannot addArc() on v greater than graph order.\n");
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

// BFS removed for PA5.
/*
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
*/

void DFS(Graph G, List S){
    if(G == NULL){
        printf("\nCannot call DFS() on NULL graph.\n");
        exit(1);
    }

    if(S == NULL){
        printf("\nCannot call DFS() on NULL list.\n");
        exit(1);
    }

    if(G == NULL && S == NULL){
        printf("\nCannot call DFS() on NULL graph and NULL list.\n");
        exit(1);
    }

    if(length(S) != getOrder(G)){
        printf("\nCannot call DFS() on graph with order != list length.\n");
        exit(1);
    }

    int q = 0;

    for(int i=1; i <= getOrder(G); i++){
        G->par[i] = NIL;
        G->col[i] = white; 
    }


    //List L = copyList(S);

    //clear(S);


    for(moveFront(S); index(S) != -1; moveNext(S)){
        int v = get(S);
        if(G->col[v] == white){ 

            Visit(G, S, v, &q);
        }
    }

    //Fixed

    for(int i=1; i<= getOrder(G); i++){
        deleteBack(S);
    }

    //freeList(&L);


}


void Visit(Graph G, List S, int v, int *q){

    G->col[v] = gray;
    //G->time++;
    G->disc[v] = ++*q;
    for(moveFront(G->adj[v]); index(G->adj[v]) != -1; moveNext(G->adj[v])){
        int x = get(G->adj[v]);

        if(G->col[x] == white){
            G->par[x] = v;
            //Visit(G, S, x);
            Visit(G, S, x, q);
        }
    }

    //G->time++;
    G->col[v] = black;
    G->fin[v] = ++*q;

    prepend(S, v);
}

//--Other Functions---


void printGraph(FILE* out, Graph G){
    if(out == NULL){
        printf("\nCannot call printGraph() on NULL outfile.\n");
        exit(1);
    }

    if(G == NULL){
        printf("\nCannot call printGraph() on NULL graph.\n");
        exit(1);
    }

    for(int i=1; i<= getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }

}

Graph transpose(Graph G){ // required for finding strongly connected components

    if(G == NULL){
        printf("\nCannot call transpose() on NULL graph.\n");
        exit(1);
    }

    Graph tG = newGraph(getOrder(G));

    for(int i=1; i<=getOrder(G); i++){

        //moveFront(G->adj[i]);

        for(moveFront(G->adj[i]);index(G->adj[i]) != -1;moveNext(G->adj[i])){
            addArc(tG, get(G->adj[i]), i);
        }
    }

    return tG;

}

Graph copyGraph(Graph G){

    if(G == NULL){
        printf("\nCannot call copyGraph() on NULL graph.\n");
        exit(1);
    }

    Graph cG = newGraph(getOrder(G));

    for(int i=1; i<=getOrder(G); i++){
        moveFront(G->adj[i]);

        while(index(G->adj[i]) != -1){
            
            //int x = get(G->adj[i]);
            addArc(cG, i, get(G->adj[i]));
            moveNext(G->adj[i]);

        }
    }

    return cG;

}