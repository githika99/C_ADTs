/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa1
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"

int main(int argc, char *argv[]) {
    // Check if there are exactly three command-line arguments (program name, input file, and output file)
    if (argc != 3) {
        fprintf(stderr, "Error: Calling Lex.c without exactly 2 arguments for input file and output file");
        exit(EXIT_FAILURE);
    }

    // Extract the input and output file names from command-line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    // Check if the file opened successfully
    if (inputFile == NULL) {
        printf("Error opening input file: %s\n", inputFileName);
        return 1;
    }
    if (outputFile == NULL) {
        printf("Error opening output file: %s\n", outputFileName);
        return 1;
    }

    char buffer[2048];
    int lines = 0;
    char* empty = "\n";

    while(fgets(buffer, sizeof(buffer), inputFile) != NULL){
        if(strcmp(buffer, empty) != 0){
                lines++;
            }
    }
    fclose(inputFile);
    printf("there are %d lines in inputfile\n", lines);

    char** array = (char**)malloc(lines * sizeof(char*));

    int arrayIndex = 0;
    inputFile = fopen(inputFileName, "r");        //open file to read
    while(fgets(buffer, sizeof(buffer), inputFile) != NULL){ //don't need to clear buffer fgets replaces it
        //printf("\n%dth line of input file is '%s'", arrayIndex, buffer);
        if(strcmp(buffer, empty) != 0){
            array[arrayIndex] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
            strcpy(array[arrayIndex], buffer);
            arrayIndex++;
        }
    }

    fclose(inputFile);
    
    //sort List
    List L = newList();
    append(L, 0);
    //printList(stdout, L);
    bool added;
    
    for(int i = 1; i < lines; i++){
        added = false;
        moveFront(L);
        while(index(L) >= 0 ){              //while cursor is defined
            if (strcmp(array[i], array[get(L)] ) <= 0) { 
                insertBefore(L, i);
                added = true;
                break;
            }   
            moveNext(L);
        }
        if (!added){
            append(L, i);
        }
    }

    //write to output file
    moveFront(L);
    while(index(L) >= 0 ){   
        fprintf(outputFile, "%s", array[get(L)]);
        moveNext(L);
    }
    fprintf(outputFile, "\n");
    fclose(outputFile);


    //freeing array and array[i]
    for(int i = 0; i < lines; i++){
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;

    freeList(&L);
    return 0;
}