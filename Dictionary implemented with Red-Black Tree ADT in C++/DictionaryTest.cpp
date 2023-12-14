/*
Githika Annapureddy
Cruz Id: gannapur
pa8
*/
//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string S[] =   { // words to insert
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   { // words to delete
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };


   
   Dictionary A;
   Dictionary B;

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }

   cout << A << endl;
   
    //I ADDED THIS
       A.setValue(S[0], 0+1);
       A.setValue(S[1], 1+1);
       A.setValue(S[2], 2+1);
   
   // call operator=()
   B = A;

   cout << B << endl;

   
   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

    
   // call copy constructor
   Dictionary C = B;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;
     
    
   // check copy constructor
   cout << "copy constructor creates identical trees: " << endl;
   cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   cout << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << "A.getValue(\"hemiolia\") = " << A.getValue("hemiolia") << endl << endl;
   

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

    
   // remove some pairs from A
   for(int i=0; i<13; i++){ 
      cout << "removing '" << T[i] << "' from A\n" << endl;
      A.remove(T[i]);
      cout << "successfully removed, A in pre_order:\n" << A.pre_string() << endl;
   }

    
   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   cout << "forward iteration on B, changing values:" << endl;
   for(B.begin(); B.hasCurrent(); B.next()){
      cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   }
   cout << endl;

   
   // do reverse iteration on C
   cout << "reverse iteration on C, changing values" << endl;
   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   }
   cout << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;  
   

   return( EXIT_SUCCESS );
}

/*

A.size() = 26
ambusher : 2
cantling : 23
cohabit : 21
crosby : 3
cul : 14
depressants : 13
deschooler : 18
dissocialised : 20
forms : 8
glagolitic : 26
glamorized : 24
hemiolia : 22
impales : 9
millesimal : 25
norm : 16
pardoner : 5
pic : 10
plaices : 1
potables : 15
pythons : 6
recoining : 19
recriminator : 12
reinsurer : 17
second : 7
verticals : 11
wattles : 4

B.size() = 26
ambusher : 105
cantling : 23
cohabit : 21
crosby : 3
cul : 104
depressants : 13
deschooler : 101
dissocialised : 20
forms : 8
glagolitic : 103
glamorized : 24
hemiolia : 22
impales : 9
millesimal : 25
norm : 16
pardoner : 5
pic : 10
plaices : 1
potables : 15
pythons : 6
recoining : 19
recriminator : 12
reinsurer : 102
second : 7
verticals : 11
wattles : 4

C.size() = 26
ambusher : 105
cantling : 23
cohabit : 21
crosby : 3
cul : 104
depressants : 13
deschooler : 101
dissocialised : 20
forms : 8
glagolitic : 103
glamorized : 24
hemiolia : 22
impales : 9
millesimal : 25
norm : 16
pardoner : 5
pic : 10
plaices : 1
potables : 15
pythons : 6
recoining : 19
recriminator : 12
reinsurer : 102
second : 7
verticals : 11
wattles : 4

copy constructor creates identical trees: 
true

A==B is false
B==C is true
C==A is false

A.getValue("hemiolia") = 22
A.getValue("hemiolia") = 220

A.size() = 26
ambusher : 2
cantling : 23
cohabit : 21
crosby : 3
cul : 14
depressants : 13
deschooler : 18
dissocialised : 20
forms : 8
glagolitic : 26
glamorized : 24
hemiolia : 220
impales : 9
millesimal : 25
norm : 16
pardoner : 5
pic : 10
plaices : 1
potables : 15
pythons : 6
recoining : 19
recriminator : 12
reinsurer : 17
second : 7
verticals : 11
wattles : 4

A pre-order: 
impales
depressants (RED)
crosby
cantling
ambusher (RED)
cohabit (RED)
cul
dissocialised
deschooler
glamorized (RED)
forms
glagolitic (RED)
hemiolia
pythons (RED)
plaices
pardoner (RED)
norm
millesimal (RED)
pic
potables
second
recriminator
recoining (RED)
reinsurer (RED)
wattles
verticals (RED)

A.size() = 13
ambusher : 2
cantling : 23
cohabit : 21
crosby : 3
dissocialised : 20
glagolitic : 26
glamorized : 24
hemiolia : 220
millesimal : 25
pardoner : 5
plaices : 1
pythons : 6
wattles : 4

A pre-order: 
millesimal
dissocialised (RED)
cantling
ambusher
crosby
cohabit (RED)
glamorized
glagolitic
hemiolia
pythons
pardoner
plaices (RED)
wattles

forward iteration on B, changing values:
(ambusher, 105) (ambusher, 106)
(cantling, 23) (cantling, 24)
(cohabit, 21) (cohabit, 22)
(crosby, 3) (crosby, 4)
(cul, 104) (cul, 105)
(depressants, 13) (depressants, 14)
(deschooler, 101) (deschooler, 102)
(dissocialised, 20) (dissocialised, 21)
(forms, 8) (forms, 9)
(glagolitic, 103) (glagolitic, 104)
(glamorized, 24) (glamorized, 25)
(hemiolia, 22) (hemiolia, 23)
(impales, 9) (impales, 10)
(millesimal, 25) (millesimal, 26)
(norm, 16) (norm, 17)
(pardoner, 5) (pardoner, 6)
(pic, 10) (pic, 11)
(plaices, 1) (plaices, 2)
(potables, 15) (potables, 16)
(pythons, 6) (pythons, 7)
(recoining, 19) (recoining, 20)
(recriminator, 12) (recriminator, 13)
(reinsurer, 102) (reinsurer, 103)
(second, 7) (second, 8)
(verticals, 11) (verticals, 12)
(wattles, 4) (wattles, 5)

reverse iteration on C, changing values
(wattles, 4) (wattles, 5)
(verticals, 11) (verticals, 12)
(second, 7) (second, 8)
(reinsurer, 102) (reinsurer, 103)
(recriminator, 12) (recriminator, 13)
(recoining, 19) (recoining, 20)
(pythons, 6) (pythons, 7)
(potables, 15) (potables, 16)
(plaices, 1) (plaices, 2)
(pic, 10) (pic, 11)
(pardoner, 5) (pardoner, 6)
(norm, 16) (norm, 17)
(millesimal, 25) (millesimal, 26)
(impales, 9) (impales, 10)
(hemiolia, 22) (hemiolia, 23)
(glamorized, 24) (glamorized, 25)
(glagolitic, 103) (glagolitic, 104)
(forms, 8) (forms, 9)
(dissocialised, 20) (dissocialised, 21)
(deschooler, 101) (deschooler, 102)
(depressants, 13) (depressants, 14)
(cul, 104) (cul, 105)
(crosby, 3) (crosby, 4)
(cohabit, 21) (cohabit, 22)
(cantling, 23) (cantling, 24)
(ambusher, 105) (ambusher, 106)

test pre-condition errors:
Dictionary: getValue(): key "blah" does not exist
   continuing without interruption
Dictionary: remove(): key "blah" does not exist
   continuing without interruption
Dictionary: currentKey(): current undefined
   continuing without interruption
Dictionary: currentVal(): current undefined
   continuing without interruption
Dictionary: next(): current undefined
   continuing without interruption
Dictionary: prev(): current undefined
   continuing without interruption

*/