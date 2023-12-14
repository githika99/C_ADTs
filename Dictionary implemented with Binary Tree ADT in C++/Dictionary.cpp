/*
Githika Annapureddy
Cruz Id: gannapur
pa7
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
      // std::cout << "entered Node constructor for key: "<< k <<" and v:" << v << std::endl;
      key = k;
      val = v;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
    }

    // No node destructor needed since we delete nodes in Dictionary destructor using 


// Dictionary ADT Functions ----------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
   void Dictionary::inOrderString(std::string& s, Node* R) const{
      //std::cout << "inOrderString() entered \n" << std::endl;
      if (R != nullptr && R != nil){
         inOrderString(s, R->left);
         s += (R->key + " : ");
         s += (std::to_string(R->val) + "\n");
         inOrderString(s, R->right);
      }

   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
   void Dictionary::preOrderString(std::string& s, Node* R) const{
      //std::cout << "preOrderString() entered\n" << std::endl;
      if (R != nullptr && R != nil){
         s += (R->key + "\n");
         preOrderString(s, R->left);
         preOrderString(s, R->right);
      }
      // std::cout << "s: " << s << std::endl;
   }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node* R, Node* N){
      // std::cout << "preOrderCopy() entered\n" << std::endl;
      if (R != nullptr && R != nil && R != N){
         //make copy of current Node      //dictionary copy constructor calls this funct on new Dict obj. This funct calls setValue with that same Dict obj.
         setValue(R->key, R->val);        //num_pairs iterated by setValue
         preOrderCopy(R->left, N);
         preOrderCopy(R->right, N);
      }
   }

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
   void Dictionary::postOrderDelete(Node* R){
      // std::cout << "postOrderDelete() entered\n" << std::endl;
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
      //std::cout << "search() entered\n" << std::endl;
      if (R == nullptr || R == nil) {
         return nil;
      } 
      int res = (R->key).compare(k);
      // std::cout << "R is: " << (R->key) << std::endl;
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
      if (num_pairs == 0){
         throw std::length_error("Dictionary: findMax(): Dictionary is empty");
      }
      Node * curr;
      while (R != nullptr){
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
      if (num_pairs == 0){
         throw std::length_error("Dictionary: findMax(): Dictionary is empty");
      }
      Node * curr;
      while (R != nullptr){
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
      while(Y != nullptr && Y != nil &&N == Y->right) {
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
      while(Y != nullptr && Y != nil &&N == Y->left) {
         N = Y;
         Y = Y->parent;
      }
      return Y;
   }

// Public Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary::Dictionary(){
      Node* n = new Node("NIL", -111111);       //Noticable value so that we know smt is up if it gets printed
      Node* r = nullptr;
      Node* c = nullptr;
      num_pairs = 0;
      nil = n;                           //the .h file says that these values are of type Node*. 
      root = r;                          //you still need to allocate memory for them here if you want them to hold memory
      current = c;                       //you cannot reassign their type here (Node* current = nullptr).
                                         //you can either do this or do current = nullptr, both work
   }

   // Copy constructor.
   Dictionary::Dictionary(const Dictionary& D){
      num_pairs = 0;
      nil = new Node("", 0);
      root = nullptr;
      current = nullptr;
      this->preOrderCopy(D.root, nullptr);   //first argument is where to start copying, second is where to stop copying
   }

   // Destructor
   Dictionary::~Dictionary(){
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
      return num_pairs;
   }

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool Dictionary::contains(keyType k) const{
      // std::cout << "calling search" << std::endl;
      if (search(root, k) == nil){
         return false;
      }
      return true;
   }

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& Dictionary::getValue(keyType k) const{
      // std::cout << "calling search" << std::endl;
      Node* N = search(root, k);
      if (N == nil){
         throw std::logic_error("Dictionary: getValue(): k \"" + k + "\" is not in Dictionary");
      }
      return (N->val);
   }

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const{
      if(current == nullptr || current == nil){
         return false;
      }
      return true;
   }

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const{
      if(current == nullptr || current == nil){                   
         throw std::logic_error("Dictionary: currentKey(): current undefined");
      }
      return current->key;
   }

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const{
      if(current == nullptr || current == nil){                   
         throw std::logic_error("Dictionary: currentVal(): current undefined");
      }
      return current->val;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear(){
      postOrderDelete(root);
      root = nullptr;            //memory that root and current point to was freed
      current = nullptr;         //but if we don't do this, they will be dangling pointers
   }

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void Dictionary::setValue(keyType k, valType v){
      Node* prev = nullptr;
      Node* curr = root;
      while(curr != nullptr && curr != nil) {
         prev = curr;
         int res = (curr->key).compare(k);
         if (res == 0) {
            break;
         } else if (res < 0) {   //res < 0, R->key < k, k is to right of R
            curr = curr->right;
         } else {                //res > 0, R->key > k, k is to left of R
            curr = curr->left;
         }
      }

      if (curr == nullptr || curr == nil){
       
         Node * Z = new Node(k, v); 
         Z->parent = prev;
         if (prev == nullptr || prev == nil) {            // Dictionary was empty
            root = Z; 
            Z->parent = nil;  
         } else if (Z->key < prev->key) {
            prev->left = Z;
         } else {
            prev->right = Z;
         }
         num_pairs++;

      } else {
         curr->val = v;
      }
   }

   //Helper Function
   //Transplant()
   //Replaces subtree u with subtree v (u is basically deleted is no longer linked to tree)
   //make sure you delete u; 
   void Dictionary::Transplant(Node*u, Node*v){
      if (u->parent == nil || u->parent == nullptr){     //u is root
          root = v;
      } else if (u == u->parent->left) {
         u->parent->left = v;
      } else {
         u->parent->right = v;
      }
      if (v != nullptr && v != nil) {
         v->parent = u->parent;
      }
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
         throw std::logic_error("Dictionary: remove(): k \"" + k + "\" is not in Dictionary");
      }
      //DELETE FROM DICTIONARY, PRESERVE CHILDREN
      if (N->left == nullptr || N->left == nil){              // case 1  or case 2.1 (right only)
         Transplant(N, N->right);
      } else if (N->right == nullptr || N->right == nil) {       // case 2.2 (left only)
         Transplant(N, N->left);
      } else {                           // case 3
         Node* Y = findMin(N->right);
         // std::cout << "min was found, min: " << (Y->key) << std::endl;
         //smt in this condition is messing it up
         if (Y->parent != N){
            // std::cout << "Y->parent != N entered"<< std::endl;
            //if Y has a right child switch them, if Y doesn't make Y nil/nullptr
            Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
         }
         
         Transplant(N, Y);
         Y->left = N->left;
         Y->left->parent = Y;
      }
      if(N == current) {      
         current = nullptr;         //do this before we delete current loll > <
      }
      if(N->parent != nullptr && N->parent->right == N){
        N->parent->right = nullptr;
      }else if(N->parent != nullptr && N->parent->left == N){
         N->parent->left = nullptr;
      }
      delete N;
      N = nullptr;
      num_pairs--;
   }

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin(){
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
      // std::cout << "to_string entered \n" << std::endl;
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
   //returns true if the key and val of the two nodes are equal, false otherwise
   //useless function bc apparently, we're just checking if each dict contains the same (key, val) pairs not if they're in the same order
   bool Dictionary::node_equals(const Node* N, const Node* P) const{
      //both NIL
      if ((N == nullptr || N == nil) && (P == nullptr || P == nil)) {
         return true;
      }
      //only one is NIL
      if (N == nullptr || N == nil || P == nullptr || P == nil) {
         return false;
      }
      //both not nil
      int res = (N->key).compare((P->key));
      if (res != 0 || N->val != P->val) {
         return false;
      } 
      return node_equals(N->left, P->left) && node_equals(N->right, P->right);
      return true;
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
      //std::cout << "operator<< entered \n" << std::endl;
      return stream << D.to_string();
   }

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   bool operator==( const Dictionary& A, const Dictionary& B ){
      return A.equals(B);

   }

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& Dictionary::operator=( const Dictionary& D ){

       if( this != &D ){ // not self assignment

      //clear 
      clear();

      // CALLS COPY CONSTRUCTOR TO make a copy of D  
      Dictionary temp = D; 
      
      // then swap the copy's fields with fields of this
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(nil, temp.nil);
      std::swap(num_pairs, temp.num_pairs);
      }

      // return this with the new data installed
      return *this;
   }

//comment