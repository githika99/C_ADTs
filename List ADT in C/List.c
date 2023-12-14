/*
Githika Annapureddy
CruzId: gannapur
Assignment: pa1
*/
//-----------------------------------------------------------------------------
// LINKED LIST List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node prev;
   Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   int length;
   int index;     //index of cursor
   Node cursor;
} ListObj;

// Helper Function that is not included in List.h----------------------

// Returns true if Q is empty, otherwise returns false.
bool isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object. 
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = NULL;
   L->length = 0;
   L->cursor = NULL;     
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL);          //instead of Dequeue()
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->index <0 || L->index >= L->length){
      return(-1);
   }

   return(L->index);
}

// Returns front element of L
// Pre: !isEmpty(Q)
ListElement front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// Returns back element of L. Pre: length()>0
ListElement back(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

// Returns cursor element of L. Pre: length()>0, index()>=0
ListElement get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      printf("List Error: calling get() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

// Returns true iff Lists A and B are in same
// state (disregarding the cursor), and returns false otherwise.
bool equals(List A, List B){
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L){
   //first clear all elements of L
   if(L!=NULL) { 
      while( !isEmpty(L) ) { 
         deleteFront(L);          //instead of Dequeue()
      }
   }
   // should be true after the loop: L-> front = L-> back = NULL
   L -> cursor = NULL;
   L -> index = -1;
}

// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
 //used to manipulate list
void set(List L, int x){
   if( L==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      printf("List Error: calling set() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L){
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      return;
      //don't cause error if isEmpty, just don't do anything
      printf("List Error: calling moveFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   L -> index = 0;
   L -> cursor = L->front;
}

// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      return;
      //don't cause error if isEmpty, just don't do anything
      printf("List Error: calling moveBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   L -> index = L->length - 1;
   L -> cursor = L->back;
}

// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L){
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      return;
   }
   if( isEmpty(L) ){
      printf("List Error: calling movePrev() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index == 0){
      L -> index = -1;
      L -> cursor = NULL;
   }else{
      L -> index--;
      L -> cursor = L -> cursor -> prev;
   }
   
}

// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      return;
   }
   if( isEmpty(L) ){
      printf("List Error: calling moveNext() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index >= L->length - 1){
      L -> index = -1;
      L -> cursor = NULL;
   }else{
      L -> index++;
      L -> cursor = L -> cursor -> next;
   }
   

}

// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, int x){
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);

   if( isEmpty(L) ) { 
      L->front = L->back = N; 
   }else{ 
      N -> next = L->front;
      L->front->prev = N; 
      //makes the current back 's next = N
      L->front = N; 
      //makes the new back = N
      
   }
   L-> index++;
   L->length++;
}

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = newNode(x);
   if( isEmpty(L) ) { 
      L->front = L->back = N; 
   }else{ 
      N -> prev = L->back;
      L->back->next = N; 
      //makes the current back 's next = N
      L->back = N; 
      //makes the new back = N
      
   }
   L->length++;
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      printf("List Error: calling insertBefore() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode(x);
   if (L->index == 0){
      N -> next = L-> cursor;
      L->cursor -> prev = N;
      L->front = N;
   }
   else{
      Node P = NULL;
      P = L -> cursor -> prev;
      P -> next = N;
      N -> prev = P;
      L-> cursor-> prev = N;
      N -> next = L-> cursor;
   }
   
   L-> length++;
   L->index++;
}

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x){
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      printf("List Error: calling insertAfter() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode(x);
   if (L->index == L->length - 1){
      N -> prev = L-> cursor;
      L->cursor -> next = N;
      L->back = N;
   } 
   else {
      Node A = NULL;                
      A = L -> cursor -> next;
      A -> prev = N;
      N -> next = A;
      L-> cursor-> next = N;
      N -> prev = L-> cursor;
   }
   
   L-> length++;
}

// Deletes data at front of L.
// Pre: !isEmpty(L)
void deleteFront(List L){
   if( L==NULL ){
      printf("List Error: calling deleteFront(List L) on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront(List L) on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = NULL;
   N = L->front;
   //check this before we modify L->front
   if (L->cursor == L->front){
      L->cursor = NULL;
      L->index = -1;
   }
   else{
      L->index--;
   }

   if( L->length >1 ) { 
      L->front = L->front->next; 
         //do we have to do this, or will it automatically be handled by freeing L->front
      L->front->prev = NULL;
   }else{ 
      L->front = L->back = NULL; 
   }

   L->length--;

   freeNode(&N);
}

// Deletes data at back of L.
// Pre: !isEmpty(L)
void deleteBack(List L){
   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = NULL;
   N = L->back;

   //check this before modifying L->back
   if (L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   
   if( L->length >1 ) { 
      L->back = L->back->prev; 
      L->back->next = NULL;
   }else{ 
      L->front = L->back = NULL; 
   }
   L->length--;

   freeNode(&N);
}

// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete(List L){
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0){
      printf("List Error: calling delete() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }

   //edge cases: 
   if (L->length == 1){
      L->front = L->back = NULL;
      L->cursor = NULL;
      L->index = -1;
   }
   //cursor was front
   else if (L-> cursor == L->front){
      //cursor is freed, cursor = NULL, length--, index = -1 in deleteFront
      deleteFront(L);
   }
   //cursor was back
   else if (L-> cursor == L->back){
      //cursor is freed, cursor = NULL, length--, index = -1 in deleteBack
      deleteBack(L);
   }
   else{
      L -> cursor -> prev -> next = L -> cursor -> next;
      L -> cursor -> next -> prev = L -> cursor -> prev;
      free((L->cursor));
      L -> length--;
      L-> index = -1;
      L->cursor = NULL;
   }

   //should I do free(L->cursor) or just set it to null
}

// Other Functions ------------------------------------------------------------

// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node N = NULL;
   for(N = L->front; N != NULL; N = N->next){
      printf(FORMAT" ", N->data);
   }
   printf("\n");
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
   if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List cpy = newList();
   Node N = NULL;
   for(N = L->front; N != NULL; N = N->next){
      append(cpy, N->data);
   }
   cpy -> length = L->length;

   return cpy;
}

// Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A and B.
 // The states of A and B are unchanged.
List concatList(List A, List B){
   //not sure if this is how i should handle null on this funct
   if( A==NULL || B==NULL){
      printf("List Error: calling concatList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List C = newList();
   Node N = NULL;
   for(N = A->front; N != NULL; N = N->next){
      append(C, N->data);
   }
   for(N = B->front; N != NULL; N = N->next){
      append(C, N->data);
   }

   C -> length = A->length + B->length;
   return C;
}
