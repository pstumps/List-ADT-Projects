//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 - PA5
//FindComponents.c
//Determines strongly connected components of a given graph

#include<stdlib.h>
#include<stdio.h>

#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){

    int n;

    if(argc > 3 || argc < 3){
        printf("Usage: inputfile outputfile");
        exit(1);
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if(input == NULL){
        printf("Program cannot continue as input file is NULL or unreadable.");
        exit(1);
    }

    if(output == NULL){
        printf("Program cannot continue as output file is NULL or unwritable.");
        exit(1);
    }

    fscanf(input, "%d", &n);
    Graph g = newGraph(n);

    int v1=0;
    int v2=0;

    while(fgetc(input) != EOF){
        fscanf(input, "%d", &v1);
        fscanf(input, "%d", &v2);

        if(v1==0 && v2 == 0){
            break;
        }
        else{
            addArc(g, v1, v2);
        }
    }

    List l = newList();

    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, g);
    fprintf(output, "\n");

    for(int i=1; i<=n; i++){
        append(l, i);
    }

    DFS(g, l);

    //printf("Generating transpose of g\n");
    Graph t = newGraph(n);
    t = transpose(g);
    DFS(t, l);

    int scc = 0;
    for(int i=1; i<=getOrder(g); i++){
        if(getParent(t, i) == NIL){ scc++; }
    }

    fprintf(output, "G contains %d strongly connected components:\n", scc);

    int c=1;
    //moveBack(l);
    List sccList[scc+1];

    for(int i=1; i<= scc; i++){
        sccList[i]=newList();
    }

    for(moveBack(l); index(l) != -1; movePrev(l)){

        int u = get(l);
        prepend(sccList[c], u);

        if(getParent(t, u) == NIL){

            fprintf(output, "Component %d: ", c);
            printList(output, sccList[c]);
            fprintf(output, "\n");
            c++;
            
        }

        //movePrev(l);

    }

    for(int i=1; i<=scc; i++){freeList(&sccList[i]);}

    freeGraph(&g);
    freeGraph(&t);
    
    freeList(&l);

    fclose(input);
    fclose(output);


}
