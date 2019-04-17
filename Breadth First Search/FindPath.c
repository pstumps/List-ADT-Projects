//Patrick Stumps
//pstumps@ucsc.edu
//CMPS 101 PA 4
//FindPath.c
//Finds path from source to destination in graph

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "List.h"
#include "Graph.h"

int main(int argc, char *argv[]){
    
    int sauce = 0;
    int dest = 0;
    int vertices = 0;
    int v1 = 0;
    int v2 = 0;

    if(argc > 3 || argc < 3){
        printf("Usage: FindPatch.c input output\n");
        exit(1);
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if(input == NULL){
        printf("Input file is null.\n");
        exit(1);
    }

    if(output == NULL){
        printf("Output file is null.\n");
        exit(1);
    }

    fscanf(input, "%d", &vertices);

    Graph g = newGraph(vertices);

    while(fgetc(input) != EOF){
        fscanf(input, "%d", &v1);
        fscanf(input, "%d", &v2);

        if(v1 != 0 && v2 != 0){
            addEdge(g, v1, v2);
        }
        else if(v1 == 0 && v2 == 0){
            break;
        }
    }

    printGraph(output, g);

    fprintf(output, "\n");

    List l = newList();

    while(fscanf(input, "%d %d", &sauce, &dest)){
        //List l = newList();

        if(sauce == 0 && dest == 0){
            //printf(" Source and destination equal 0\n");
            break;
        }
        //printf("Performing BFS on %d\n", sauce);
        BFS(g, sauce);
        //printf("Determining path to %d\n", dest);
        getPath(l, g, dest);
        fprintf(output, "\n");
        fprintf(output, "The distance from %d to %d is ", sauce, dest);

        if(front(l)==0){
            fprintf(output, "infinity\n");
            fprintf(output,"No %d-%d path exists\n", sauce, dest);
        }
        else if (front(l) != 0){
            int d = getDist(g, dest);
            fprintf(output, "%d\n", d);
            fprintf(output, "A shortest %d-%d path is: ", sauce, dest);
            printList(output, l);
            fprintf(output, "\n");
        }

        clear(l);
        freeList(&l);

    }
    
    fclose(input);
    fclose(output);

    freeGraph(&g);

}