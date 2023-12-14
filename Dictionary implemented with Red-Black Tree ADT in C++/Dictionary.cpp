/*
Githika Annapureddy
Cruz Id: gannapur
pa8
*/
#include<iostream>
#include<string>
#include <stdexcept>
#include "Dictionary.h"

// For reference, do not comment out: Exported types ----------------------------
// typedef std::string keyType;  // must be comparable using <, <=, >, >=, ==, !=
// typedef int         valType;

// Private Constructor --------------------------------------------------------

    // Node constructor
    Dictionary::Node::Node(keyType k, valType v){
      // // // std::cout << "entered Node constructor for key: "<< k <<" and v:" << v << std::endl;
      key = k;
      val = v;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      color = 0;        //0 means black and 1 means red
    }

    // No node destructor needed since we delete nodes in Dictionary destructor using 


// Dictionary ADT Functions ----------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
   void Dictionary::inOrderString(std::string& s, Node* R) const{
      // // // std::cout << "inOrderString() entered \n" << std::endl;
      if (R != nullptr && R != nil){
         inOrderString(s, R->left);
         s += (R->key + " : ");
         s += (std::to_string(R->val) + "\n");
         inOrderString(s, R->right);
      }

   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string will consist of keys only, with the order determined by a pre-order
   // tree walk. The keys stored in black Nodes will be appended as "key\n", and
   // the keys stored in red Nodes will be appended as "key (RED)\n". The output 
   // of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
   void Dictionary::preOrderString(std::string& s, Node* R) const{
      // // std::cout << "preOrderString() entered\n" << std::endl;
      if (R != nullptr && R != nil){
         if (R->color == 1) {
            s += (R->key + " (RED)\n");
         } else {
            s += (R->key + "\n");
         }
         preOrderString(s, R->left);
         preOrderString(s, R->right);
      }
      // // std::cout << "s: " << s << std::endl;
   }

   // BST_insert()
   // Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
   void Dictionary::BST_insert(Node* M){
      // std::cout << "BST_insert() entered\n" << std::endl;
      //modified setValue() from pa7
      Node* prev = nil;
      Node* curr = root;
      //loop searches for place to insert M 
      while(curr != nullptr && curr != nil) {
         prev = curr;
         int res = (curr->key).compare(M->key);
         if (res == 0) {
            break;
         } else if (res < 0) {   //res < 0, R->key < k, k is to right of R
            curr = curr->right;
         } else {                //res > 0, R->key > k, k is to left of R
            curr = curr->left;
         }
      }
      //if (curr == nullptr || curr == nil){
         M->parent = prev;
         if (prev == nullptr || prev == nil) {            // Dictionary was empty
            root = M; 
            M->parent = nil;  
         } else if (M->key < prev->key) {
            prev->left = M;
         } else {
            prev->right = M;
         }
         num_pairs++;
      //} 
      //else node already exists in Dictionary
   }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node* R, Node* N){
      //// std::cout << "preOrderCopy() entered\n" << std::endl;
      if(R != nil && R != N){
         setValue(R->key, R->val);
         preOrderCopy(R->left, N);
         preOrderCopy(R->right, N);
      }
   }

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
   void Dictionary::postOrderDelete(Node* R){
      // // std::cout << "postOrderDelete() entered\n" << std::endl;
      if (R != nullptr && R != nil){
         postOrderDelete(R->left);
         postOrderDelete(R->right);
         delete R;
         R = nullptr;
         //do we not have to do R = nullptr here bc there is no reference to R in the Dictionary?
         //or is it still good to do it to avoid a dangling pointer?
         num_pairs--;
      }
      //when this function returns 
   }

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
      // // std::cout << "search() entered\n" << std::endl;
      if (R == nullptr || R == nil) {
         return nil;
      } 
      int res = (R->key).compare(k);
      // // std::cout << "R is: " << (R->key) << std::endl;
      if (res == 0) {
         return R;
      } else if (res < 0) {   //res < 0, R->key < k, k is to right of R
         return search(R->right, k);
      } else {                //res > 0, R->key > k, k is to left of R
         return search(R->left, k);
      }
   }


   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMin(Node* R){
      // std::cout << "findMin() entered for Node w/ key:" << (R->key) <<std::endl << std::endl;
      if (R == nil){
         throw std::length_error("Dictionary: findMin(): Subtree rooted at R is empty");
      }
      Node * curr;
      while (R != nil){
         curr = R;
         R = R->left;
      }
      return curr;
   }

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMax(Node* R){
      // std::cout << "findMax() entered\n" << std::endl;
      if (R == nil){
         throw std::length_error("Dictionary: findMax(): Subtree rooted at R is empty");
      }
      Node * curr;
      while (R != nil){
         curr = R;
         R = R->right;
      }
      return curr;
   }

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   Dictionary::Node* Dictionary::findNext(Node* N){
      // std::cout << "findNext() entered\n" << std::endl;
      if (N->right != nullptr && N->right != nil) {
         return findMin(N->right);
      }
      Node* Y = N->parent;
      while(Y != nullptr && Y != nil && N == Y->right) {
         N = Y;
         Y = Y->parent;
      }
      return Y;
   }

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   Dictionary::Node* Dictionary::findPrev(Node* N){
      // std::cout << "findPrev() entered\n" << std::endl;
      if (N->left != nullptr && N->left != nil) {
         return findMax(N->left);
      }
      Node* Y = N->parent;
      while(Y != nullptr && Y != nil && N == Y->left) {
         N = Y;
         Y = Y->parent;
      }
      return Y;
   }
// RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N){
      // std::cout << "LeftRotate() entered\n" << std::endl;
      // set y
      Node* Y = N->right;

      N->right = Y->left;

      // turn y's left subtree into x's right subtree
      if (Y->left != nil) {     // not necessary if using sentinal nil node
         Y->left->parent = N;
      }

      // link y's parent to x
      Y->parent = N->parent;
      if(N->parent == nil) {
         root = Y;
      } else if (N == N->parent->left) {
         N->parent->left = Y;
      } else {
         N->parent->right = Y;
      }

      // put x on y's left
      Y->left = N; 
      N->parent = Y;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N){
      // std::cout << "RightRotate() entered\n" << std::endl;
      // set y
      Node* Y = N->left;

      N->left = Y->right;

      // turn y's left subtree into x's right subtree
      if (Y->right != nil) {     // not necessary if using sentinal nil node
         Y->right->parent = N;
      }

      // link y's parent to x
      Y->parent = N->parent;
      if (N->parent == nil)
         root = Y;
      else if (N == N->parent->right)
         N->parent->right = Y;
      else 
         N->parent->left = Y;

      // put x on y's left
      Y->right = N; 
      N->parent = Y;
   }

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N){
      // std::cout << "RB_InsertFixUp() entered\n" << std::endl;
      while (N->parent->color == 1){
         // std::cout << "entered main while loop\n" << std::endl;
         if (N->parent == N->parent->parent->left){
            // std::cout << "N->parent is left child\n" << std::endl;
            Node* Y = N->parent->parent->right;
            if (Y->color == 1){          //Y is red
               // std::cout << "case 1\n" << std::endl;
               N->parent->color = 0;                // case 1
               Y->color = 0;                        // case 1
               N->parent->parent->color = 1;        // case 1
               N = N->parent->parent;               // case 1
            }
            else {
               if (N == N->parent->right){
                  // std::cout << "case 2\n" << std::endl;
                  N = N->parent;                    // case 2
                  LeftRotate(N);                    // case 2
               }
               // std::cout << "case 3\n" << std::endl;
               N->parent->color = 0;                // case 3
               N->parent->parent->color = 1;        // case 3
               RightRotate(N->parent->parent);      // case 3
            }
         }
         else { 
            // std::cout << "N->parent is right child\n" << std::endl;
            Node* Y = N->parent->parent->left;
            if (Y->color == 1){          //Y is red
               // std::cout << "case 4\n" << std::endl;
               N->parent->color = 0;                // case 4
               Y->color = 0;                        // case 4
               N->parent->parent->color = 1;        // case 4
               N = N->parent->parent;               // case 4        
            }     
            else {
               if (N == N->parent->left){
                  // std::cout << "case 5\n" << std::endl;
                  N = N->parent;                     // case 5
                  RightRotate(N);                    // case 5
               }
               // std::cout << "case 6\n" << std::endl;
               N->parent->color = 0;                 // case 6
               N->parent->parent->color = 1;         // case 6
               LeftRotate(N->parent->parent);        // case 6
            }
         }
      }
      root->color = 0;
   }

   // RB_Transplant()
   //Replaces subtree u with subtree v (u is basically deleted is no longer linked to tree)
   //make sure you delete u somewhere
   //called for (verticals, wattles)
   void Dictionary::RB_Transplant(Node* u, Node* v){
      // std::cout << "RB_Transplant() entered\n" << std::endl;
      if (u->parent == nil){     //u is root
          root = v;
      } else if (u == u->parent->left) {
         u->parent->left = v;
      } else {
         u->parent->right = v;
      }
      v->parent = u->parent;
   }

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N){
      // std::cout << "RB_DeleteFixUp() entered\n" << std::endl;
      while (N != root and N->color == 0) {
         if (N == N->parent->left){
            Node* W = N->parent->right; 
            if (W->color == 1) {          //W is red
               //if statement is safe, W is only red if it is defined
               W->color = 0;                           // case 1
               N->parent->color = 1;                   // case 1
               LeftRotate(N->parent);                  // case 1
               W = N->parent->right;                   // case 1
               //new W could be nil
            }
            if (W->left->color == 0 and W->right->color == 0) {    //should it be: W->left-> color == 0 && N->right->color == 0
               W->color = 1; //W must not be nullptr  // case 2   
               N = N->parent;                         // case 2
            }
            else {
               if (W->right->color == 0) {
                  // W->left must not be nil
                  W->left->color = 0;                 // case 3
                  // W must not be nil
                  W->color = 1;                       // case 3
                  RightRotate(W);                     // case 3
                  W = N->parent->right;               // case 3
               }
               //W must not be nullptr
               W->color = N->parent->color;           // case 4
               N->parent->color = 0;                  // case 4
               //W->right must not be nullptr
               W->right->color = 0;                   // case 4
               LeftRotate(N->parent);                 // case 4
               N = root;                              // case 4
            }
         }
         else {
            Node* W = N->parent->left;
            if (W->color == 1){          //W is red
               W->color = 0;                           // case 5
               N->parent->color = 1;                   // case 5
               RightRotate(N->parent);                 // case 5
               W = N->parent->left;                    // case 5
            }
            // both black: both nodes must be either nullptr or have the color black
            // W must not be nil
            if (W->left->color == 0 and W->right->color == 0){       //should it be: W->right->color == 0 && N->left->color == 0 
               W->color = 1;                            // case 6    
               N = N->parent;                           // case 6
            }
            else { 
               // W must not be nil
               if (W->left->color == 0){  
                  // W->right must not be nil
                  W->right->color = 0;                // case 7
                  W->color = 1;                       // case 7
                  LeftRotate(W);                      // case 7
                  W = N->parent->left;                // case 7
               }
               W->color = N->parent->color;          // case 8
               N->parent->color = 0;                 // case 8
               W->left->color = 0;                   // case 8
               RightRotate(N->parent);               // case 8
               N = root;                             // case 8
            }
         }
      }
      N->color = 0;
   }
   

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N){
      // std::cout << "RB_Delete() entered\n" << std::endl;
      Node* Y = N;
      Node* X = nil;
      int y_original_color = Y->color;
      if (N->left == nil){
         X = N->right;
         RB_Transplant(N, N->right);
      }
      else if (N->right == nil){
         X = N->left;
         RB_Transplant(N, N->left);
      }
      else {
         Y = findMin(N->right);
         y_original_color = Y->color;
         X = Y->right;
         if (Y->parent == N){
            X->parent = Y;       //don't think we need this line since X is already Y->right
                                 //if X is nil, does this change nil's parent field for all nil? 
                                 //that could be the problem? 
         }
         else {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
         }
         RB_Transplant(N, Y);
         Y->left = N->left;
         Y->left->parent = Y;
         Y->color = N->color;
      }
      if (y_original_color == 0) {
         RB_DeleteFixUp(X);
      }
   }



// Public Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary::Dictionary(){
      nil = new Node("NIL", -111111);       //NIL has color -> BLACK automatically bc BLACK is default in Node Constructor
      nil->parent = nil;
      nil->left = nil;
      nil->right = nil;
      root = nil;               
      current = nil;
      num_pairs = 0;     
   }

   // Copy constructor.
   Dictionary::Dictionary(const Dictionary& D){
      // std::cout << "entered copy constructor\n" << std::endl;
      num_pairs = 0;
      nil = new Node("NIL", -111111);        //NIL has color -> BLACK automatically bc BLACK is default in Node Constructor
      nil->parent = nil;
      nil->left = nil;
      nil->right = nil;
      root = nil;
      current = nil;
      // std::cout << "calling pre order copy for (this) address: " << this << "of (D) address: "<< &D << std::endl;
      this->preOrderCopy(D.root, D.nil);   //first argument is where to start copying, second is where to stop copying
   }

   // Destructor
   Dictionary::~Dictionary(){
      // std::cout << "entered destructor\n" << std::endl;
      clear();
      //this deletes all nodes, including current and root
      //nil is the only node not deleted bc when clear() iterates through the Dictionary's nodes, it never encounters nil
      delete nil;
      nil = nullptr;       //although the data pointing to the nodes is freed by delete, delete frees the data that a pointer is pointing to 
      current = nullptr;   //thus, the pointer is still pointing to it, resulting in a dangling pointer
      root = nullptr;      //thus, we make nil, current, and root = nullptr so that they no longer point to that freed memory
   }


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int Dictionary::size() const{
      //// std::cout << "size() entered\n" << std::endl;
      return num_pairs;
   }

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool Dictionary::contains(keyType k) const{
      // std::cout << "contains() entered\n" << std::endl;
      // // std::cout << "calling search" << std::endl;
      if (search(root, k) == nil){
         return false;
      }
      return true;
   }

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& Dictionary::getValue(keyType k) const{
      //// std::cout << "calling search" << std::endl;
      Node* N = search(root, k);
      if (N == nil){
         throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
      }
      return (N->val);
   }

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const{
      // std::cout << "hasCurrent() entered\n" << std::endl;
      if(current == nullptr || current == nil){
         return false;
      }
      return true;
   }

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const{
      // // std::cout << "currentKey() entered\n" << std::endl;
      if(current == nullptr || current == nil){                   
         throw std::logic_error("Dictionary: currentKey(): current undefined");
      }
      return current->key;
   }

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const{
      // // std::cout << "currentVal() entered\n" << std::endl;
      if(current == nullptr || current == nil){                   
         throw std::logic_error("Dictionary: currentVal(): current undefined");
      }
      return current->val;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear(){
      // std::cout << "clear() entered\n" << std::endl;
      postOrderDelete(root);
      root = nil;            //memory that root and current point to was freed
      current = nil;         //but if we don't do this, they will be dangling pointers
   }

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void Dictionary::setValue(keyType k, valType v){
        Node* curr = root;
        Node* prev = nil;

        while (curr != nil) {
            prev = curr;
            if (k > curr->key) {
                curr = curr->right;
            } else if (k < curr->key) {
                curr = curr->left;
            } else {
                curr->val = v;
                return;
            }
        }

        Node* Z = new Node(k, v);
        Z->color = 1;   //new node is RED, children are automatically nullptr
        Z->left = nil;
        Z->right = nil;
        Z->parent = prev;

        if (prev == nil) {
            root = Z;
        } else if (k < prev->key) {
            prev->left = Z;
        } else {
            prev->right = Z;
        }

        num_pairs++;
        RB_InsertFixUp(Z); //added this line from pa7
   }



   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void Dictionary::remove(keyType k){
      // std::cout << "entered remove" << std::endl;
      // std::cout << "calling search" << std::endl;
      Node* N = search(root, k);
      if (N == nil){
         throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
      }
      RB_Delete(N);
      if(N == current) {      
         current = nil;         //do this after, otherwise, N is nil and cannot be deleted properly by N
      }                         //RB_Delete() unlinks the node N but does not delete it, so current is unlinked if it was N. Now current = nil is necessary.
      delete N;      //deletes memory that N was pointing to
      N = nullptr;   //prevents N from becoming a hanging pointer
      num_pairs--;
   }

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin(){
      // std::cout << "begin() entered\n" << std::endl;
      if (num_pairs == 0) {
         return;
      }
      //find leftmost key
      current = findMin(root);
   }

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end(){
      // std::cout << "end() entered\n" << std::endl;
      if (num_pairs == 0) {
         return;
      }
      //find rightmost key
      current = findMax(root);
   }

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next(){
      // // std::cout << "next() entered\n" << std::endl;
      if(current == nullptr || current == nil){
         //catches empty list too
         throw std::logic_error ("Dictionary: next(): current undefined");
      }
      current = findNext(current);     //findNext handles returns nil if current has no 'next' object
   }

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::prev(){
      // // std::cout << "prev() entered\n" << std::endl;
      if(current == nullptr || current == nil){
         //catches empty list too
         throw std::logic_error ("Dictionary: prev(): current undefined");
      }
      current = findPrev(current);     //findNext handles returns nil if current has no 'prev' object

   }


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string Dictionary::to_string() const{
      //// std::cout << "to_string entered \n" << std::endl;
      std::string s = "";
      inOrderString(s, root);
      return s;
   }

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string Dictionary::pre_string() const{
      std::string s = "";
      preOrderString(s, root);
      return s;
   }

   //Helper Function for equals()
   //returns true if the subtrees rooted at N and P contain the same (key, val) pairs
   bool Dictionary::node_contains(const Node* N, Node* R) const{
      if (N== nullptr || N== nil){
         return true;
      }
      Node* P = search(R, N->key);
      if (P == nil || P->val != N->val) {
         return false;
      }
      return node_contains(N->left, R) && node_contains(N->right, R);
      return true;
   }

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool Dictionary::equals(const Dictionary& D) const{
      //// std::cout << "equals() entered\n" << std::endl;
      if (num_pairs != D.num_pairs) {
         return false;
      }
      return node_contains(root, D.root);
   }


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
      //// std::cout << "operator<< entered \n" << std::endl;
      return stream << D.to_string();
   }

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   bool operator==( const Dictionary& A, const Dictionary& B ){
      //// std::cout << "operator==() entered\n" << std::endl;
      return A.equals(B);
   }

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& Dictionary::operator=( const Dictionary& D ){
      //// std::cout << "operator==() entered\n" << std::endl;
       if( this != &D ){ // not self assignment

      //clear 
      clear();

      // CALLS COPY CONSTRUCTOR TO make a copy of D  
      // // std::cout << "calling copy constructor with D: " << &D << std::endl;
      //// std::cout << "D's root's key: " << (D->root)->key << std::endl;
      Dictionary temp = D; 
      
      // then swap the copy's fields with fields of this
      std::swap(nil, temp.nil);  //copying nil first so that root has something to point to
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
      }

      // return this with the new data installed
      return *this;
   }

