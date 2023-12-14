/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa1
*/
/****************************************************************************************
*  ListTest.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("%d ", index(A));
   printf("\n");

   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("%d ", index(B));
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");  //false
   printf("%s\n", equals(B,C)?"true":"false");  //false
   printf("%s\n", equals(C,A)?"true":"false");  //true
   printf("%s\n", equals(A,C)?"true":"false");  //true


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   printf("index is %d ", index(A));

   insertBefore(A, -1);            // at index 6
   printList(stdout, A);

   for(i=0; i<9; i++) moveNext(A); // at index 15
   printf("index is %d ", index(A));

   insertAfter(A, -2);
   printList(stdout, A);
   for(i=0; i<5; i++) movePrev(A); // at index 10

   //testing delete function
   printf("index is %d ", index(A));
   printf("\n");
   printf("val at index is %d ", get(A));
   printf("\n");
   delete(A);

   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   ///my tests now 
   moveBack(C);
   insertBefore(C, -1); 
   printf("%s\n", equals(A,C)?"true":"false");  //false

   //testing functions in random orders
   freeList(&A);
   freeList(&B);
   freeList(&C);

   //test all ADT functions
   bool before = false;
   List L = newList();
   append(L, 0);
   moveFront(L);
   List G = copyList(L);
   moveFront(G);
   for(int i = 1; i < 10; i++){
      moveFront(L);
      printf("Cursor is at front of list: %d\n", get(L));
      if (before){
         insertBefore(L, i);
         insertAfter(G, i);
         before = false;
      }
      else{
         insertBefore(G, i);
         insertAfter(L, i);
         before = true;
      }
      moveNext(L);
   }

   printf("Length is %d\n", length(L));
   printf("Index is %d\n", index(L));
   printf("Front is %d\n", front(L));
   printf("Back is %d\n", back(L));
   printf("Cursor element has value %d\n", get(L));
   printf("Lists L and G are equal: %s\n", equals(L,G)?"true":"false");  //false

   moveBack(G);
   movePrev(G);
   set(G, 99);
   delete(G);
   prepend(G, 9);
   append(G, 10);
   deleteFront(G);
   deleteBack(G);
   clear(G);

   freeList(&G);
   freeList(&L);


   return(0);
}

