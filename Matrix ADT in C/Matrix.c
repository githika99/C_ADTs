/*
Githika Annapureddy
Cruz ID: gannapur
Assignment: pa4
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"

//Your Matrix ADT will represent a matrix
//as an array of Lists of Entries. Since Entry is itself a pointer, it can be assigned to a field of type void*

//FIND TIME COMPLEXITY OF ALL IMPLEMENTATIONS
//I THINK YOU SHOULD ALSO START AT 1 AND GO TO END OF LIST


//non void functions can exit(EXIT_FAILURE) but not return(EXIT_FAILURE), they can return; though
//not sure which I should call (exit() or return) bc exit terminates the whole program

//I can still imporve product() run time in line: 

//find 


// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
   int row;
   double data;
} EntryObj;


// private ListObj type
typedef struct MatrixObj{
   int n;   //size
   List* array;
   int nnz;
} MatrixObj;


// newEntry()
// Returns reference to new Entry object. Initializes next and data fields.
Entry newEntry(int row, double data){
   Entry E = malloc(sizeof(EntryObj));
   assert( E!=NULL );
   E->row = row;
   E->data = data;
   return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeEntry(Entry* pE){
   if( pE==NULL || *pE==NULL ){
     //not sure if we should do anything
     fprintf(stderr, "Calling freeEntry with Null Entry reference");
     exit(EXIT_FAILURE);
   }
    free(*pE);
    //*pE = NULL;       MIGHT CAUSE A DANGLING POINTER 
}

// newMatrix()
// similar to newGraph(), allocating n + 1 spots and assigning Lists to 1 - n, not 0
// Returns a reference to a new nXn Matrix object in the zero state.c
Matrix newMatrix(int n){
   Matrix M = malloc(sizeof(MatrixObj));
   assert( M!=NULL );
   M->n = n;
   M->nnz = 0;
   //should array be initialized to size of n?
   M->array = (List *)malloc((n+1) * sizeof(List));
   for (int i = 1; i <= n; i++){
        M->array[i] = newList();
   }
   return(M);
}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if(pM == NULL || *pM == NULL){              //if pG == NULL, we cannot access *pG
        fprintf(stderr, "Calling freeMatrix with Null Matrix reference");
        exit(EXIT_FAILURE);
    }
    makeZero((*pM));
    for(int i = 1; i <= (*pM)->n; i++){
        freeList(&((*pM)->array[i]));            //frees each List
    }            
    free((*pM) -> array);       
    free(*pM);
    *pM = NULL;
    
}


// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if( M ==NULL ){
      fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    return(M->n);
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if( M ==NULL ){
      fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    return (M->nnz);
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if( A ==NULL || B == NULL ){
      fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(A->n != B->n){
        return 0;
    }
    if(NNZ(A) != NNZ(B)){
        return 0;
    } 
    int Annz = 0;
    int Bnnz = 0;
    int i = 1;
    while(i <= A->n && Annz < A->nnz && Bnnz < B->nnz){
        if(length(A->array[i]) != length(B->array[i]))
            return 0;
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        while (index(A->array[i]) != -1 && index(B->array[i]) != -1){
            if (((Entry)(get(A->array[i])))-> row != ((Entry)(get(B->array[i])))-> row || ((Entry)(get(A->array[i])))-> data != ((Entry)(get(B->array[i])))-> data)
                return 0;
            Annz++;
            Bnnz++;
            moveNext(A->array[i]);
            moveNext(B->array[i]);
        }
        i++;
    }
    if(Annz != Bnnz){
        return 0;
    }
    return 1;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if( M ==NULL ){
      fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    int Mnnz = 0;
    int i = 1;
    while(i <= M->n && Mnnz < M->nnz){
            moveFront(M->array[i]);
            while(index(M->array[i]) != -1){
                Entry temp = get(M->array[i]);
                freeEntry(&(temp));             //frees data for each list element
                moveNext(M->array[i]);
                Mnnz++;
            }
            clear(M->array[i]);
            i++;
    }
    M->nnz = 0;
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
//Runtime: O(a) for a is # non-zero entries in M
void changeEntry(Matrix M, int i, int j, double x){
    //printf("entered changeEntry with row %d col %d val %.1lf", i, j, x);
    if( M ==NULL ){
      fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if (i < 1 || i > M->n || j < 1 || j > M->n){
        fprintf(stderr, "Matrix Error: calling changeEntry() with out of index row or column number\n");
        exit(EXIT_FAILURE);
    }
    moveFront(M->array[i]);
    //printf("index is %d\n", index(M->array[i]));
    //If M->array[i] is empty and z is nonzero, append it 
    if(index(M->array[i]) == -1 && x != 0){               
        Entry E = newEntry(j, x);
        append(M->array[i], E);
        M->nnz++;
        return;
    }

    while(index(M->array[i]) != -1){
        //printf("\nwe are at: row: %d col:%d val:%.1lf", i, ((Entry)get(M->array[i])) -> row, ((Entry)get(M->array[i])) -> data);
        
        //If we are at the correct position, either overwrite data or free the element
        if ( ((Entry)get(M->array[i])) -> row == j){
            //printf("condition one executed\n");
            if(x != 0)
                ((Entry)get(M->array[i])) -> data = x;
            else{
                //printf("0 condition executed\n");
                //printf("\nbefore length of row is now: %d\n", length(M->array[i]));
                Entry temp = get(M->array[i]);
                delete(M->array[i]);                            //deletes cursor element
                freeEntry(&(temp));             //frees data for each list element
                M->nnz--;
                //if List is now empty, clear it? 
                //printf("\nafter length of row is now: %d\n", length(M->array[i]));
            }
            return;
        }

        //If we passed the correct position, then it doesn't exist so insertBefore
        else if (((Entry)get(M->array[i])) -> row > j && x != 0){         //there is no i, j element so we add one
            //printf("condition two executed\n");
            Entry E = newEntry(j, x);
            insertBefore(M->array[i], E);
            M->nnz++;
            return;
        }

        //If we are at the end of the list and did not encounter the correct position, then it doesn't exist so we append it
        //If x is zero, do nothing and moveNext will make index -1 so we will exit function
        else if(((Entry)get(M->array[i])) == ((Entry)(back(M->array[i]))) && x != 0){       //we reached end of list and did not encounter jth obj, so it must not exist
            //printf("condition three executed with index = %d and back = %d\n", index(M->array[i]), length(M->array[i]) - 1);
            Entry E = newEntry(j, x);                                                      
            append(M->array[i], E);
            M->nnz++;
            return;
        }

        moveNext(M->array[i]);
    }
}


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.

//COPY LISTS OF A, SIMPLER THAN WHAT YOURE CURRENTLY DOING -- but we deleted copyList, maybe rewrite?
//Runtime: O(n*n - zero entries)  = O(nnz). this is too slow, must be O(n + a) for n - # of rows in A, a - # of nonzero entries in A
//MUST MAKE MORE EFFICIENT
Matrix copy(Matrix A){
    if( A == NULL ){
      fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    printf("entered copy");
    Matrix T = newMatrix(size(A));
    T -> nnz = A -> nnz;
    int r;
    double d;
    int Annz = 0;
    int i = 1;
    while(i<= A->n && Annz<A->nnz){
        moveFront(A->array[i]);
        while (index(A->array[i]) != -1){
            r = ((Entry)get(A->array[i])) -> row;
            d = ((Entry)get(A->array[i])) -> data;
            Entry E = newEntry(r, d);
            append(T->array[i], E);
            Annz++;
            moveNext(A->array[i]);
        }
        i++;
    }
    return(T);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
//Runtime: O(n*n - zero entries)  = O(nnz). this is too slow, must be O(n + a) for n - # of rows in A, a - # of nonzero entries in A
//MUST MAKE MORE EFFICIENT
Matrix transpose(Matrix A){
    if( A == NULL ){
      fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    printf("entered transpose\n");
    Matrix T = newMatrix(size(A));
    T -> nnz = A -> nnz;
    int r;
    double d;
    int Annz = 0;
    int i = 1;
    while(i<= A->n && Annz<A->nnz){
        moveFront(A->array[i]);
        while (index(A->array[i]) != -1){
            r = ((Entry)get(A->array[i])) -> row;
            d = ((Entry)get(A->array[i])) -> data;
            Entry E = newEntry(i, d);
            append(T->array[r], E);
            Annz++;
            moveNext(A->array[i]);
        }
        i++;
    }
    return(T);
}


// scalarMult()
// Returns a reference to a new Matrix object representing xA.
//Runtime: O(n*n - zero entries)  = O(nnz). this is too slow, must be O(n + a) for n - # of rows in A, a - # of nonzero entries in A
//MUST MAKE MORE EFFICIENT
Matrix scalarMult(double x, Matrix A){
    if( A == NULL ){
      fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(x == 0){
        Matrix N = newMatrix(A->n);
        return(N);
    }
    printf("entered scalrMult");
    Matrix T = newMatrix(size(A));
    T -> nnz = A -> nnz;
    int r;
    double d;
    int Annz = 0;
    int i = 1;
    while(i<= A->n && Annz<A->nnz){
        moveFront(A->array[i]);
        while (index(A->array[i]) != -1){
            r = ((Entry)get(A->array[i])) -> row;
            d = ((Entry)get(A->array[i])) -> data;
            Entry E = newEntry(r, x * d);
            append(T->array[i], E);
            Annz++;
            moveNext(A->array[i]);
        }
        i++;
    }
    return(T);
}

//not in .h file
//helper function for sum and diff 
//sign is a integer, 1 means positive, -1 means negative
//change nnx with (*nnz)++;
List add(List A, List B, int sign, int* nnz){
    int rA, rB;
    List cpy = newList();
    if(index(A) != -1){
        rA = ((Entry)get(A))-> row;
    } else {
        rA = -1;                                        //rA will never be -1
    }                                                       
    if(index(B) != -1) {
        rB = ((Entry)get(B))-> row;
    } else {
        rB = -1;
    }

    if (rB == -1 || (rA < rB && rA != -1)){
        Entry E = newEntry(rA, ((Entry)get(A))-> data);
        append(cpy, E);
        (*nnz)++;
        moveNext(A);
    }
    else if (rA == -1 || (rB < rA && rB != -1)){
        Entry E = newEntry(rB, ((Entry)get(B))-> data);
        if(sign == -1){
            E->data *= -1;
        } 
        append(cpy, E);
        (*nnz)++;
        moveNext(B);
    }
    else if (rA == rB){
        if(! (sign == -1 && ((Entry)get(A))-> data - ((Entry)get(B))-> data == 0) ){        //if sign is -1 and A - B == 0, skip
            Entry E = newEntry(rA, ((Entry)get(A))-> data + ((Entry)get(B))-> data);
            if(sign == -1 ){
                E->data = ((Entry)get(A))-> data - ((Entry)get(B))-> data;
            } 
            append(cpy, E);
            (*nnz)++;
        }
        moveNext(A);
        moveNext(B);
    }
    return cpy;
}


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if( A == NULL || B == NULL){
      fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if( size(A) != size(B) ){
      fprintf(stderr, "Matrix Error: calling sum() with two matricies of different sizes\n");
      exit(EXIT_FAILURE);
    }
    if (equals(A,B) == 1){
        return (scalarMult(2,A));
    }
    int rA, rB;
    Matrix cpy_list = newMatrix(size(A));
    //int MAXnnz = A->nnz > B->nnz? A->nnz : B->nnz; //FIND MAX BETWEEN TWO
    int i = 1;
    while(i<= A->n){                        //removed: && cpy_list->nnz < MAXnnz
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        //remove later
        //printf("i = %d\n", i);
        //int count = 1;
        while (index(A->array[i]) != -1 || index(B->array[i]) != -1){       //handles if you reached end of both lists
            //cpy->array[i] = add(A->array[i], B->array[i], 1, &(cpy->nnz));
            //remove later
            // printf("count = %d\n", count);
            // printf("count = %d\n", count);
            // printf("index of A is %d\n", index(A->array[i]));
            // printf("index of B is %d\n", index(B->array[i]));
            List Al = A->array[i];
            List Bl = B->array[i];
            List cpy = cpy_list->array[i];
            if(index(Al) != -1){
                rA = ((Entry)get(Al))-> row;
            } else {
                rA = -1;                                        //rA will never be -1
            }                                                       
            if(index(Bl) != -1) {
                rB = ((Entry)get(Bl))-> row;
            } else {
                rB = -1;
            }
            // printf("rA is %d\n", rA);
            // printf("rB is %d\n", rB);

            if (rB == -1 || (rA < rB && rA != -1)){
                // printf("first condition executed\n");
                Entry E = newEntry(rA, ((Entry)get(Al))-> data);
                append(cpy, E);
                (cpy_list->nnz)++;
                moveNext(Al);
            }
            else if (rA == -1 || (rB < rA && rB != -1)){
                // printf("second condition executed\n");
                Entry E = newEntry(rB, ((Entry)get(Bl))-> data);
                append(cpy, E);
                (cpy_list->nnz)++;
                moveNext(Bl);
            }
            else if (rA == rB){
                // printf("third condition executed\n");
                Entry E = newEntry(rA, ((Entry)get(Al))-> data + ((Entry)get(Bl))-> data);
                append(cpy, E);
                (cpy_list->nnz)++;
                moveNext(Al);
                moveNext(Bl);
            }
            //remove later
            //count++;
        }
        i++;
    }
    return(cpy_list);
}


// diff()
// Returns a reference to a new Matrix object representing B-A.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if( A ==NULL || B==NULL){
      fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if( size(A) != size(B) ){
      fprintf(stderr, "Matrix Error: calling diff() with two matricies of different sizes\n");
      exit(EXIT_FAILURE);
    }
    Matrix cpy = newMatrix(size(A));
    if (equals(A,B) == 1){
        return (cpy);
    }
    int rA, rB;
    //int MAXnnz = A->nnz > B->nnz? A->nnz : B->nnz; //FIND MAX BETWEEN TWO
    int i = 1;
    while(i<= A->n){                        //removed:cpy->nnz < MAXnnz
        moveFront(A->array[i]);
        moveFront(B->array[i]);
        //remove later
        // printf("i = %d\n", i);
        // int count = 1;
        while (index(A->array[i]) != -1 || index(B->array[i]) != -1){       //handles if you reached end of both lists
            //remove later
            // printf("count = %d\n", count);
            // printf("count = %d\n", count);
            // printf("index of A is %d\n", index(A->array[i]));
            // printf("index of B is %d\n", index(B->array[i]));
            if(index(A->array[i]) != -1){
                rA = ((Entry)get(A->array[i]))-> row;
            } else {
                rA = -1;                                        //rA will never be -1
            }                                                       
            if(index(B->array[i]) != -1) {
                rB = ((Entry)get(B->array[i]))-> row;
            } else {
                rB = -1;
            }
            // printf("rA is %d\n", rA);
            // printf("rB is %d\n", rB);

            if (rB == -1 || (rA < rB && rA != -1)){
                // printf("first condition executed\n");
                Entry E = newEntry(rA, ((Entry)get(A->array[i]))-> data);
                append(cpy->array[i], E);
                cpy->nnz++;
                moveNext(A->array[i]);
            }
            else if (rA == -1 || (rB < rA && rB != -1)){
                // printf("second condition executed\n");
                Entry E = newEntry(rB, -1 * ((Entry)get(B->array[i]))-> data);
                append(cpy->array[i], E);
                cpy->nnz++;
                moveNext(B->array[i]);
            }
            else if (rA == rB){
                // printf("third condition executed\n");
                if (((Entry)get(A->array[i]))-> data - ((Entry)get(B->array[i]))-> data != 0){
                    Entry E = newEntry(rA, ((Entry)get(A->array[i]))-> data - ((Entry)get(B->array[i]))-> data);
                    append(cpy->array[i], E);
                    cpy->nnz++;
                }
                moveNext(A->array[i]);
                moveNext(B->array[i]);
            }
            //remove later
            // count++;
        }
        i++;
    }
    return(cpy);
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if( A ==NULL || B==NULL){
      fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if (A->n != B->n) {
        fprintf(stderr, "Matrix Error: calling product() on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
    double vectorDot;
    Matrix P = newMatrix(A->n);
    Matrix BT = transpose(B);

    for (int i = 1; i <= A->n; i++) { 
        if (length(A->array[i]) == 0) 
            continue;
        for (int j = 1; j <= BT->n; j++) { 
            if (length(BT->array[j]) == 0) 
                continue;
            vectorDot = 0;
            moveFront(A->array[i]);
            moveFront(BT->array[j]);
            while (index(A->array[i]) >= 0 && index(BT->array[j]) >= 0) {
                Entry eA = (Entry)get(A->array[i]);
                Entry eBT = (Entry)get(BT->array[j]);
                if (eA->row < eBT->row) {
                    moveNext(A->array[i]);
                } else if (eA->row > eBT->row) {
                    moveNext(BT->array[j]);
                } else {
                    vectorDot += (eA->data * eBT->data);
                    moveNext(A->array[i]);
                    moveNext(BT->array[j]);
                }
            }
            
            if (vectorDot != 0) {
                append(P->array[i], newEntry(j, vectorDot)); 
                P->nnz++;
            }
        }
    }
    freeMatrix(&BT); 
    return P;
}


// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    
    if( M ==NULL ){
      fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if(NNZ(M) == 0 ){                                                      //don't print anything if Matrix has no non zero entries
      return;
    }
    
    for(int i = 1; i<= M->n; i++){
        if (length(M->array[i]) == 0)
            continue;
        fprintf(out, "%d: ", i);
        moveFront(M->array[i]);
        while (index(M->array[i]) != -1){
            fprintf(out, "(%d, %.1f) ", ((Entry)get(M->array[i]))-> row, ((Entry)get(M->array[i]))-> data);
            moveNext(M->array[i]);
        }
        fprintf(out, "\n");
    }
    
}

//to get the EntryObj pointed to by M->array[i]                 I think we need to do get(M->array[i]) -> row/data
// bc get(M->array[i]) returns the ListElement (Entry) pointed to by the List
// whereas (M->array[i])->row   will be an error bc the List does not have a field called row 