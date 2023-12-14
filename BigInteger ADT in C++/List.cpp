/*
Githika Annapureddy
CruzId: gannapur
pa6
*/
//-----------------------------------------------------------------------------
// List.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include <vector>
#include <algorithm> 
#include "List.h"

//do you not have to check if the List is NULL?

//Question: how do I call another function in the class from one question in the class


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
// Every element of the list is a Node*
List::List(){
   Node* fr = new Node(-1337);
   Node* bk = new Node(-1337);
   fr -> next = bk;
   bk -> prev = fr;

   frontDummy = fr;                         //Node*         that's why you can do -> cause its a pointer
   backDummy = bk;                          //Node*
   beforeCursor = frontDummy;               //Node*
   afterCursor = backDummy;                 //Node*
   pos_cursor = 0;
   num_elements = 0;
}


// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   Node* fr = new Node(-1337);
   Node* bk = new Node(-1337);
   fr -> next = bk;
   bk -> prev = fr;

   frontDummy = fr;                         //Node*
   backDummy = bk;                          //Node*
   beforeCursor = frontDummy;               //Node*
   afterCursor = backDummy;                 //Node*
   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this List
   Node* N = L.frontDummy -> next;
   while( N!=L.backDummy ){
      this->insertBefore(N->data);
      N = N->next;
   }

   pos_cursor = L.pos_cursor;           //first mark the position of pos_cursor
   N = L.frontDummy -> next;
   moveFront();
   while( N!=nullptr ){
      if (N == L.afterCursor) {          //afterCursor and beforeCursor should be set up properly by moveNext()
          break;
      }
      N = N->next;
      moveNext();
   }

}


// Destructor
List::~List(){
    if (length() > 0) {
        moveFront();
        while( length()>0 ){
            eraseAfter();
        }
    }
   delete frontDummy;
   delete backDummy;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of List.
int List::length() const{
   return(num_elements);
}


// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if(length() ==0 ){                      //or num_elements == 0
      throw std::length_error("List: front(): empty list");
   }
   return(frontDummy->next->data);
}


// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if(length() ==0 ){                      //or num_elements == 0
      throw std::length_error("List: back(): empty list");
   }
   return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    //not sure if I need pre condition
    if(pos_cursor < 0 || pos_cursor > num_elements) {
        throw std::range_error("List: position(): cursor out of bounds");
    }
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    //not sure if i should have this precondition
    if(length() ==0 ){                      //or num_elements == 0
      throw std::length_error("List: peekNext(): empty list");
    }
    if(pos_cursor == num_elements) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    if(pos_cursor < 0 || pos_cursor >= num_elements) {
        throw std::range_error("List: peekNext(): cursor out of bounds");
    }
    return(afterCursor->data);
}


// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    //not sure if i should have this precondition
    if(length() ==0 ){                      //or num_elements == 0
      throw std::length_error("List: peekPrev(): empty list");
    }
    if(pos_cursor == 0 || pos_cursor > num_elements) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    if(pos_cursor <= 0 || pos_cursor > num_elements) {
        throw std::range_error("List: peekPrev(): cursor out of bounds");
    }
    return(beforeCursor->data);
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    if(length() ==0 ){                      
      pos_cursor = 0;
      beforeCursor = frontDummy;
      afterCursor = backDummy;
      return;
    }
    moveFront();
    while(num_elements > 0){
        eraseAfter();
    }
    pos_cursor = 0;
    //the following should be true
    //assert(beforeCursor == frontDummy);
    //assert(afterCursor == backDummy);   
    //assert(num_elements == 0);  
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    if(length() == 0 ){                      //or num_elements == 0
      pos_cursor = 0;
      beforeCursor = frontDummy;
      afterCursor = backDummy;
      return;
    }
   pos_cursor = 0;
   beforeCursor = frontDummy;
   afterCursor = frontDummy -> next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    if(length() == 0 ){                      //or num_elements == 0
      pos_cursor = 0;
      beforeCursor = frontDummy;
      afterCursor = backDummy;
      return;
    }
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy -> prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() { 
    //added this precodnition, the next one checks for the same thing, this is just a more clear error message
    if(length() ==0 ){                      
      throw std::length_error("List: moveNext(): empty list");
    }
    if(pos_cursor == num_elements) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    if(pos_cursor < 0 || pos_cursor >= num_elements) {
        throw std::range_error("List: moveNext(): cursor out of bounds");
    }
    pos_cursor++;
    ListElement temp = afterCursor->data;
    afterCursor = afterCursor -> next;
    beforeCursor = beforeCursor -> next;
    return (temp);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    //added this precodnition, the next one checks for the same thing, this is just a more clear error message
    if(length() ==0 ){                      
      throw std::length_error("List: movePrev(): empty list");
    }
    if(pos_cursor == 0) {
        throw std::range_error("List: movePrev(): cursor at front");
    }
    if(pos_cursor <= 0 || pos_cursor > num_elements) {
        throw std::range_error("List: movePrev(): cursor out of bounds");
    }
    pos_cursor--;
    ListElement temp = beforeCursor->data;
    afterCursor = afterCursor -> prev;
    beforeCursor = beforeCursor -> prev;
    return (temp);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    if(pos_cursor < 0 || pos_cursor > num_elements) {
        throw std::range_error("List: insertAfter(): cursor out of bounds");
    }
    Node* N = new Node(x);
    N -> next = afterCursor;
    afterCursor -> prev = N;

    N->prev = beforeCursor;
    beforeCursor -> next = N;

    afterCursor = N;                    //this is how he does it in Queue.cpp
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    if(pos_cursor < 0 || pos_cursor > num_elements) {
        throw std::range_error("List: insertBefore(): cursor out of bounds");
    }
    Node* N = new Node(x);
    N -> next = afterCursor;
    afterCursor -> prev = N;

    N->prev = beforeCursor;
    beforeCursor -> next = N;

    beforeCursor = N;                    //this is how he does it in Queue.cpp
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    //added this precodnition, the next one checks for the same thing, this is just a more clear error message
    if(length() ==0 ){                      
      throw std::length_error("List: setAfter(): empty list");
    }
    if(pos_cursor == num_elements) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    if(pos_cursor < 0 || pos_cursor >= num_elements) {
        throw std::range_error("List: setAfter(): cursor out of bounds");
    }
    afterCursor -> data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    //added this precodnition, the next one checks for the same thing, this is just a more clear error message
    if(length() ==0 ){                      
      throw std::length_error("List: setBefore(): empty list");
    }
    if(pos_cursor == 0) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    if(pos_cursor <= 0 || pos_cursor > num_elements) {
        throw std::range_error("List: setBefore(): cursor out of bounds");
    }
    beforeCursor -> data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    //added this precodnition, the next one checks for the same thing, this is just a more clear error message
    if(length() ==0 ){                      
      throw std::length_error("List: eraseAfter(): empty list");
    }
    if(pos_cursor == num_elements) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    if(pos_cursor < 0 || pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): cursor out of bounds");
    }
    beforeCursor -> next = afterCursor -> next;
    afterCursor -> next -> prev = beforeCursor;

    delete afterCursor;
    afterCursor = beforeCursor -> next;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    //added this precodnition, the next one checks for the same thing, this is just a more clear error message
    if(length() ==0 ){                      
      throw std::length_error("List: eraseBefore(): empty list");
    }
    if(pos_cursor == 0) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    if(pos_cursor <= 0 || pos_cursor > num_elements) {
        throw std::range_error("List: eraseBefore(): cursor out of bounds");
    }
    beforeCursor -> prev -> next = afterCursor;
    afterCursor -> prev = beforeCursor -> prev;

    delete beforeCursor;
    beforeCursor = afterCursor -> prev;
    pos_cursor--;
    num_elements--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and return/s -1. 
int List::findNext(ListElement x){
    // don't need this precondition, but it helps clarify code
    if(length() ==0 ){ 
      pos_cursor = 0;                     
      return -1;
    }
    // if (pos_cursor == 0) {
    //     moveNext();
    // }
    moveNext();
    while(pos_cursor < num_elements && beforeCursor -> data != x) {
        moveNext();
    }
    if(beforeCursor -> data == x) {
        return pos_cursor;
    }
    moveBack();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    // don't need this precondition, but it helps clarify code
    if(length() ==0 ){  
      pos_cursor = 0;                    
      return -1;
    }
    // if (pos_cursor == num_elements) {
    //     movePrev();
    // }
    movePrev();
    while(pos_cursor > 0 && afterCursor -> data != x) {
        movePrev();
    }
    if(afterCursor -> data == x) {
        return pos_cursor;
    }
    moveFront();
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    //since we can't move the cursor, we can iterate through nodes and -> next
    //instead of creating an array with heap memory and having garbage values, i'd rather use vector and resize
    // std::vector<int> myVector;
    // myVector.reserve(num_elements);
    
    
    std::vector<int> myVector;
    myVector.reserve(num_elements);
    Node * N = frontDummy -> next;
    int index = 1;
    while(N != backDummy) {

        //not sure if I can use std::find or if I should write it myself
        auto it = std::find(myVector.begin(), myVector.end(), N->data);
        if (it != myVector.end()) {
            //std::cout << "element: " << index << " is in myVector" << std::endl;

            Node* temp = N->next; // Store the next node before deletion

            if (index <= pos_cursor && beforeCursor != N){                    //bc if N = beforeCursor, then pos_cursor will be decremented in eraseBefore()
                pos_cursor--;
            }

            if(beforeCursor == N) {
                eraseBefore();
            } else if (afterCursor == N) {
                eraseAfter();
            } else {
                N->prev->next = N->next;
                N->next->prev = N->prev;
                delete N;
                num_elements--;
            }
            N = temp; // Move to the next node
            //std::cout << *this << std::endl;
        }
        else {
            //std::cout << "element: " << index << " is not in myVector" << std::endl;
            myVector.push_back(N->data);
            N = N -> next;
            index ++;
        }
    }
    
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    //copy join of Queue, but make sure to address prev pointer as well
   List J;
   Node* N = this->frontDummy->next;
   Node* M = L.frontDummy->next;
   while( N!=this->backDummy ){
      J.insertBefore(N->data);
      N = N->next;
   }
   while( M!=L.backDummy ){
      J.insertBefore(M->data);
      M = M->next;
   }
   J.moveFront();
   return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
   Node* N = nullptr;
   std::string s = "(";
   if (length() == 0) {
    s += ")";
    return s;
   }
   for(N=frontDummy->next; N!=backDummy->prev; N=N->next){
      s += std::to_string(N->data)+", ";
   }
   s += std::to_string(N->data)+")";
   return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
   bool eq = false;
   Node* N = R.frontDummy -> next;
   Node* M = this->frontDummy -> next;

   eq = ( this->num_elements == R.num_elements );
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    //std::cout << "We are in operator= function" << std::endl; 
    if( this != &L ){ // not self assignment

      //clear 
      clear();

      // make a copy of L  
      List temp = L; 
      
      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(num_elements, temp.num_elements);

   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return

   //we use copy and swap because it is better at exception handling than regular assignment
}