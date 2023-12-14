/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa4
*/
//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){

   Matrix AL = newMatrix(5);
   changeEntry(AL, 1, 1, 1.0);
    changeEntry(AL, 1, 2, 2.0);
    changeEntry(AL, 1, 3, 3.0);
    printMatrix(stdout,AL);
   printf("nnz is %d\n", NNZ(AL));

   changeEntry(AL, 1, 3, 0);
      printMatrix(stdout,AL);
   printf("nnz is %d\n", NNZ(AL));

   changeEntry(AL, 1, 1, 0);
      printMatrix(stdout,AL);
   printf("nnz is %d\n", NNZ(AL));

   changeEntry(AL, 1, 2, 0);
      printMatrix(stdout,AL);
   printf("nnz is %d\n", NNZ(AL));

   changeEntry(AL, 1, 2, 0);

   changeEntry(AL, 4, 5, 9.0);

   Matrix BL, CL, DL, EL;
   BL= transpose(AL);
   changeEntry(BL, 4, 5, 9.0);
   changeEntry(BL, 5, 5, 9.0);
   changeEntry(BL, 3, 5, 9.0);
   changeEntry(BL, 4, 4, 9.0);
   changeEntry(BL, 4, 3, 9.0);
   changeEntry(BL, 4, 1, 0);
   if (NNZ(BL) != 6){
      printf("test 1 failed\n");
      return 1;
   }

   CL = product(BL, BL);
   DL = scalarMult(0.0, BL);
   //E = newMatrix(size(D));
   if (equals(DL, newMatrix(size(DL))) != 1){
      printf("test 1 failed\n");
      return 1;
   }
   EL = sum(AL,AL);

   freeMatrix(&AL);
   freeMatrix(&BL);
   freeMatrix(&CL);
   freeMatrix(&DL);
   freeMatrix(&EL);

   Matrix ALL = newMatrix(10);
   changeEntry(ALL, 2, 1, 2);
    changeEntry(ALL, 3, 1, 5);
    changeEntry(ALL, 1, 2, 2);
    changeEntry(ALL, 1, 3, 5);
    changeEntry(ALL, 1, 1, 4);
    changeEntry(ALL, 2, 2, 2);
    changeEntry(ALL, 2, 5, 0);
    changeEntry(ALL, 2, 3, 0);
    changeEntry(ALL, 3, 3, 5);
   printMatrix(stdout,ALL);
   printf("nnz is %d\n", NNZ(ALL));
    if (NNZ(ALL) != 7){
      printf("test 1 failed\n");
      return 1;
    }
      
    changeEntry(ALL, 1, 3, 0);
    printMatrix(stdout,ALL);
   printf("nnz is %d\n", NNZ(ALL));
    changeEntry(ALL, 3, 1, 0);
    printMatrix(stdout,ALL);
   printf("nnz is %d\n", NNZ(ALL));
    changeEntry(ALL, 3, 3, 0);
     printMatrix(stdout,ALL);
   printf("nnz is %d\n", NNZ(ALL));
    if (NNZ(ALL) != 4){
      printf("test 2 failed\n");
      return 2;
    }
      
    changeEntry(ALL, 7, 6, 42);
    changeEntry(ALL, 10, 1, 24);
    if (NNZ(ALL) != 6){
      printf("test 3 failed\n");
      return 3;
    }
      
    changeEntry(ALL, 7, 6, 0);
    if (NNZ(ALL) != 5){
      printf("test 4 failed\n");
      return 4;
    }
   
    makeZero(ALL);
    changeEntry(ALL, 5, 5, 5);
    if (NNZ(ALL) != 1){
      printf("test 5 failed\n");
      return 5;
    }
   
   freeMatrix(&ALL);
   
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);


   return EXIT_SUCCESS;
}

/*
Output of this program:
7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)


9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/