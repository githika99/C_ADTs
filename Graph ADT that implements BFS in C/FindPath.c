/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa2
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
        fprintf(stderr, "Error: Calling FindPath.c without exactly 2 arguments for input file and output file");
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
        printf("Error reading from input file: %s\n", inputFileName);
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
        addEdge(G, u, v);
    }

    printGraph(outputFile, G);

    List D = newList();
    while(fgets(buffer, sizeof(buffer), inputFile) != NULL){
        lines++;
        int result = sscanf(buffer, "%d %d", &u, &v);
        if (result != 2){
            fprintf(outputFile, "FindPath Error: input file does not follow format in line %d\n", lines);
            freeGraph(&G);
            freeList(&D);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }
        if ((u == 0) && (v == 0)){
            break;
        }
        BFS(G, u);
        int dist = getDist(G, v);
        if (dist == INF){
            fprintf(outputFile, "\nThe distance from %d to %d is infinity\n", u, v);
            fprintf(outputFile, "No %d-%d path exists\n", u, v);
        } else {
            clear(D);
            getPath(D, G, v);
            fprintf(outputFile, "\nThe distance from %d to %d is %d\n", u, v, dist);
            fprintf(outputFile, "A shortest %d-%d path is: ", u, v);
            printList(outputFile, D);
            fprintf(outputFile, "\n");
        }
    }
    //fprintf(outputFile, "\n");

    freeList(&D);
    freeGraph(&G);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
