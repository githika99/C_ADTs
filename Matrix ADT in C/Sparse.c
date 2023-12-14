/*
Githika Annapureddy
Cruz ID: gannapur
Assignment: pa4
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"
#include "Matrix.h"


int main(int argc, char *argv[]) {
    // Check if there are exactly three command-line arguments (program name, input file, and output file)
    if (argc != 3) {
        fprintf(stderr, "Error: Calling Sparse.c without exactly 2 arguments for input file and output file");
        exit(EXIT_FAILURE);
    }

    // Extract the input and output file names from command-line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    
    FILE *inputFile = fopen(inputFileName, "r");
    // Check if the file opened successfully
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", inputFileName);
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        fprintf(stderr, "Error opening output file: %s\n", outputFileName);
        exit(EXIT_FAILURE);
    }

    char buffer[2048];
    //remove lines var later
    int lines = 2;

    if (fgets(buffer, sizeof(buffer), inputFile) == NULL){  
        fprintf(stderr, "Error reading from input file: %s\n", inputFileName);
        exit(EXIT_FAILURE);
    }
    int order, size_A, size_B;
    int result = sscanf(buffer, "%d %d %d", &order, &size_A, &size_B);
    if (result != 3){
            fprintf(outputFile, "Sparse Error: input file does not follow format in line %d\n", lines);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }

    fgets(buffer, sizeof(buffer), inputFile);           //read empty line

    Matrix A = newMatrix(order);
    int r, c;
    double value;
    int count = 0;
    while(fgets(buffer, sizeof(buffer), inputFile) != NULL && count < size_A){
        lines++;
        count++;
        int result = sscanf(buffer, "%d %d %lf", &r, &c, &value);
        if (result != 3){
            fprintf(outputFile, "Sparse Error: input file does not follow format in line %d\n", lines);
            freeMatrix(&A);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }
        if(r>order || c > order){
            fprintf(stderr, "Input formatted incorrectly. Matrix is %d by %d. Cannot add an entry to position %d x %d.\n", order, order, r, c);
            exit(EXIT_FAILURE);
        }
        //fprintf(outputFile, "line is: %d %d %lf\n", r, c, value);
        changeEntry(A, r, c, value);
    }

    //fgets(buffer, sizeof(buffer), inputFile);           //read empty line
    count = 0;
    Matrix B = newMatrix(order);
    while((fgets(buffer, sizeof(buffer), inputFile) != NULL) && count < size_B){
        lines++;
        count++;
        int result = sscanf(buffer, "%d %d %lf", &r, &c, &value);
        if (result != 3){
            fprintf(outputFile, "Sparse Error: input file does not follow format in line %d\n", lines);
            freeMatrix(&A);
            freeMatrix(&B);
            fclose(inputFile);
            fclose(outputFile);
            exit(EXIT_FAILURE);
        }
        if(r>order || c > order){
            fprintf(stderr, "Input formatted incorrectly. Matrix is %d by %d. Cannot add an entry to position %d x %d.\n", order, order, r, c);
            exit(EXIT_FAILURE);
        }
        //fprintf(outputFile, "line is: %d %d %lf\n", r, c, value);
        changeEntry(B, r, c, value);
    }
    fclose(inputFile);

    //REMOVE LATER
    //fprintf(outputFile, "Outfile entered\n\n");
    //output the following: 𝐴, 𝐵, (1.5)𝐴, 𝐴 + 𝐵, 𝐴 + 𝐴, 𝐵 − 𝐴, 𝐴 − 𝐴, 𝐴𝑇, 𝐴𝐵, 𝐵2
    
    fprintf(outputFile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outputFile, A);

    fprintf(outputFile, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(outputFile, B);

    Matrix D, F, G, H;
    Matrix C, E, I, J;
    C = scalarMult(1.5,A);
    fprintf(outputFile, "\n(1.5)*A =\n");
    printMatrix(outputFile, C);

    D = sum(A, B);
    fprintf(outputFile, "\nA+B =\n");
    printMatrix(outputFile, D);

    E = sum(A, A);
    fprintf(outputFile, "\nA+A =\n");
    printMatrix(outputFile, E);

    F = diff(B, A);
    fprintf(outputFile, "\nB-A =\n");
    printMatrix(outputFile, F);

    G = diff(A, A);
    fprintf(outputFile, "\nA-A =\n");
    printMatrix(outputFile, G);

    H = transpose(A);
    fprintf(outputFile, "\nTranspose(A) =\n");
    printMatrix(outputFile, H);

    I = product(A, B);
    fprintf(outputFile, "\nA*B =\n");
    printMatrix(outputFile, I);

    J = product(B, B);
    fprintf(outputFile, "\nB*B =\n");
    printMatrix(outputFile, J);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    fclose(outputFile);

    return 0;
}


/*
Output should be of format:
A has 9 non-zero entries:
1: (1, 1.0) (2, 2.0) (3, 3.0) 
2: (1, 4.0) (2, 5.0) (3, 6.0) 
3: (1, 7.0) (2, 8.0) (3, 9.0) 

B has 5 non-zero entries:
1: (1, 1.0) (3, 1.0) 
3: (1, 1.0) (2, 1.0) (3, 1.0) 

(1.5)*A =
1: (1, 1.5) (2, 3.0) (3, 4.5) 
2: (1, 6.0) (2, 7.5) (3, 9.0) 
3: (1, 10.5) (2, 12.0) (3, 13.5) 

A+B =
1: (1, 2.0) (2, 2.0) (3, 4.0) 
2: (1, 4.0) (2, 5.0) (3, 6.0) 
3: (1, 8.0) (2, 9.0) (3, 10.0) 

A+A =
1: (1, 2.0) (2, 4.0) (3, 6.0) 
2: (1, 8.0) (2, 10.0) (3, 12.0) 
3: (1, 14.0) (2, 16.0) (3, 18.0) 

B-A =
1: (2, -2.0) (3, -2.0) 
2: (1, -4.0) (2, -5.0) (3, -6.0) 
3: (1, -6.0) (2, -7.0) (3, -8.0) 

A-A =

Transpose(A) =
1: (1, 1.0) (2, 4.0) (3, 7.0) 
2: (1, 2.0) (2, 5.0) (3, 8.0) 
3: (1, 3.0) (2, 6.0) (3, 9.0) 

A*B =
1: (1, 4.0) (2, 3.0) (3, 4.0) 
2: (1, 10.0) (2, 6.0) (3, 10.0) 
3: (1, 16.0) (2, 9.0) (3, 16.0) 

B*B =
1: (1, 2.0) (2, 1.0) (3, 2.0) 
3: (1, 2.0) (2, 1.0) (3, 2.0) 
*/