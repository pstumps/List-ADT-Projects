//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 PA 4
//GraphTest.c
// Test client for Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

int main(int argc, char * argv[]){

    printf("Setting graph H n = 10\n");
    int n2 = 8;

    printf("Generating graph\n");
    Graph H = newGraph(n2);

    printf("Adding edge to H 1, 2\n");
    addEdge(H, 1, 2);
    printf("Adding edge to H 1, 3\n");
    addEdge(H, 1, 3);
    printf("Adding edge to H 2, 4\n");
    addEdge(H, 2, 4);
    printf("Adding edge to H 2, 5\n");
    addEdge(H, 2, 5);
    printf("Adding edge to H 2, 6\n");
    addEdge(H, 2, 6);
    printf("Adding edge to H 3, 4\n");
    addEdge(H, 3, 4);
    printf("Adding edge to H 4, 5\n");
    addEdge(H, 4, 5);
    printf("Adding edge to H 5, 6\n");
    addEdge(H, 5, 6);

    printf("Printing graph H\n");
    printGraph(stdout, H);
    printf("\n");

    int s = 2;
    int d = 5;

    List M = newList();

    printf("Performing BFS on Graph H source %d", s);
    printf("\n");
    BFS(H, s);
    getPath(M, H, d);
    printf("Distance from %d to %d is: ", s, d);

    if(getDist(H, d) == INF){
        printf("infinity, no such path exists\n");
    }
    else{
        printf("%d\n", length(M) -1);
        printf("Shortest %d-%d path: ", s, d);
        printList(stdout, M);
    }
}

/*    int n = 35;

    Graph G = newGraph(n);

    printf("Constructing graph");

    for(int i=1; i < 100; ++i){
        if( i % 3 == 1){
            addArc(G, i, 100-i);
        }
        else if ( i % 2 == 1){
            addEdge(G, i, 100-i);
        }
    }

    for(int i =1; i < 100; i++){
        printf("Performing BFS on %d", i);
        BFS(G, i);
        for(int j= 1; j< 100; j++){
            int distance = getDist(G, j);
            if( distance != INF){
                printf("Distance is: %d-%d: %d\n", i, j, distance);
            }
        }
    }
*/