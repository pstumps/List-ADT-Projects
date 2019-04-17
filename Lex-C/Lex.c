//Patrick Stumps
//pstumps@ucsc.edu
//CMPS101
//PA2
//Lex.c

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 256

int main(int argc,  char*argv[]){
    if(argc != 3){
        printf("Usage: Lex inputfile outputfile");
        exit(1);
    }

    //FILEIO declaration
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    int inputNum = 0, p = 0, l=0;
    char inputLine[MAX_LEN];
    List sList = newList();
    append(sList, 0);

    //Determine # of lines from input file
    //printf("Counting lines from input file \n");
    while(fgets(inputLine, MAX_LEN, input) != NULL){
        inputNum++;
    }
    
    //Creating array to be sorted
    char *unSorted[inputNum];
    rewind(input);

    //Allocating memory for sorted 
    //printf("Allocating memory for Array\n");
    for (int i=0; i <= inputNum; i++){
        unSorted[i] = calloc(1, sizeof(char *[MAX_LEN]));
    }

    //Copying input from inputLine to array
    //printf("Copying lines from input file to array\n");

    while(fgets(inputLine, MAX_LEN, input) != NULL){
        strcpy(unSorted[p], inputLine);
        p++;
    }

    //Sorting input
    //printf("Sorting...\n");
    for (int j=0; j<inputNum-1; j++){
        moveFront(sList);
        for(int k=-j; k<1; k++){
            //printlist(stdout, sList);
            if(strcmp(unSorted[get(sList)], unSorted[j+1]) > 0){
                //printf("Comparing %s to %s\n", unSorted[get(sList)], unSorted[j+1]);
                insertBefore(sList, j+1);
                k=1;
            } 
            else if (index(sList) == length(sList)-1){
                //printf("Appending %d to list\n", j+1);
                append(sList, j+1);
                k=1;
            }
            else{
                //printf("Using MoveNext");
                moveNext(sList);
            }
        }
    }

    moveFront(sList);

    //Printing sorted data to output file
    //prinf("Printing to output file \n");
    while(index(sList) != -1){
        fprintf(output, "%s", unSorted[get(sList)]);
        moveNext(sList);
    }

    while(l <= inputNum){
        free(unSorted[l]);
        l++;
    }
    
    freeList(&sList);
}