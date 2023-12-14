/*
Githika Annapureddy
Cruz ID: gannapur
Assignment: pa3
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"
#include "Graph.h"


int main(int argc, char *argv[]) {
    // Check if there are exactly three command-line arguments (program name, input file, and output file)
    if (argc != 3) {
        fprintf(stderr, "Error: Calling FindComponents.c without exactly 2 arguments for input file and output file");
        exit(EXIT_FAILURE);
    }

    // Extract the input and output file names from command-line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    // Check if the file opened successfully
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", inputFileName);
        if (outputFile != NULL)
            fclose(outputFile);
        return 1;
    }
    if (outputFile == NULL) {
        fclose(inputFile);
        fprintf(stderr, "Error opening output file: %s\n", outputFileName);
        return 1;
    }

    char buffer[2048];
    //remove lines var later
    int lines = 0;

    if (fgets(buffer, sizeof(buffer), inputFile) == NULL){  
        fprintf(stderr, "Error reading from input file: %s\n", inputFileName);
        return 1;
    }
    lines++;
    int order = atoi(buffer);
    Graph G = newGraph(order);
    int u, v;
    while(fgets(buffer, sizeof(buffer), inputFile) != NULL){
        lines++;
        int result = sscanf(buffer, "%d %d", &u, &v);
        if (result != 2){
            fprintf(outputFile, "FindPath Error: input file does not follow format in line %d\n", lines);
            freeGraph(&G);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }
        if ((u == 0) && (v == 0)){
            break;
        }
        addArc(G, u, v);
    }
    fclose(inputFile);

    fprintf(outputFile, "Adjacency list representation of G:\n");
    printGraph(outputFile, G);              //prints Adjacency List to outputFile

    List S = newList();
    for(int i=1; i<=getOrder(G);i++){
      append(S,i);
    }

    DFS(G, S);                  //run DFS on G (make List S from 1 to G->order. 
    Graph GT = transpose(G);    //Find transpose of G
    DFS(GT, S);                 //run DFS on G^T, with new order of S

    //fprintf(outputFile, "\nS is now: \n");
    //printList(outputFile, S);

    int scc = 0;    //count number of SCCs 
    for(int i = 1; i<=getOrder(GT); i++){
        //fprintf(outputFile, "\nParent of %d is %d", i, getParent(GT, i));
        if (getParent(GT, i) == NIL){
            scc++;
        }
    }

    //int * array = (int *) malloc(scc * sizeof(int));
    moveBack(S);

    //they mean GT
    fprintf(outputFile, "G contains %d strongly connected components:\n", scc);

    scc = 1;
    moveBack(S);
    List curr = newList();
    while(index(S) != -1){
        prepend(curr, get(S));
        if (getParent(GT, get(S)) == NIL){
            fprintf(outputFile, "Component %d: ", scc++);
            printList(outputFile, curr);
            clear(curr);
        }
        movePrev(S);
    }
    
    freeList(&curr);
    freeList(&S);
    freeGraph(&GT);
    freeGraph(&G);
    fclose(outputFile);

    return 0;
}