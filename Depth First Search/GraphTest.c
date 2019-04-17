//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 -PA5
//GraphTest.C
//Test for Graph.c functions

#include<stdlib.h>
#include<stdio.h>

#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){

    int n = 100;

    printf("Constructing graph g of order: %d\n", n);
    Graph g = newGraph(n);

    List l = newList();
    for(int i=1; i<= n; i++){
        prepend(l, i);
        int wtf = getFinish(g,i);
        printf("%d\n",wtf);
    }

        addArc(g, 64, 4);
        addArc(g, 64, 3);
        addArc(g, 42, 2);
        addArc(g, 2, 64);
        addArc(g, 4, 2);
        addArc(g, 3, 42);

    


    printf("Printing graph g:\n");
    printGraph(stdout, g);
    printf("\n");

    printf("Using graphCopy() on graph g:\n");
    Graph copy = copyGraph(g);
    printGraph(stdout, copy);
    printf("\n");

    printf("Running DFS on graph g\n");
    
    DFS(g, l);
    printf("Format:\n");
    printf("[vertex]: [discover time] [finish time] [parent]\n");

    for(int i=1; i<= n; i++){

        printf("%d: %d %d %d\n", i, getDiscover(g, i), getFinish(g, i), getParent(g, i));

    }
    printf("\n");
    int q = getDiscover(g, 100);

    printf("%d\n", q);
/*
    printf("Printing list\n");
    printList(stdout, l);
    printf("\n");

    printf("Using transpose() on graph g: \n");
    Graph transp = newGraph(n);
    transp = transpose(g);
    printGraph(stdout, transp);

    printf("Printing List\n");
    printList(stdout, l);
    printf("\n");

    int len = length(l);
    printf("List length: ");
    printf("%d", len);
    printf("\n");

    int ord = getOrder(transp);
    printf("Printing Order of transpose of g: ");
    printf("%d", ord);
    printf("\n");
    


    printf("Running DFS on transpose of g:\n");
    DFS(transp, l);
    
    for(int i=1; i<=n; i++){

        printf("%d: %d %d %d\n", i, getDiscover(transp, i), getFinish(transp, i), getParent(transp, i));

    }

    printf("Printing List: \n");
    printList(stdout, l);
    printf("\n");
*/
    freeList(&l);

    freeGraph(&g);
    freeGraph(&copy);
    //freeGraph(&transp);

}