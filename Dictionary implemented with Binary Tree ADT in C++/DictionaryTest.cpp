/*
Githika Annapureddy
Cruz Id: gannapur
pa7
*/
//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;
 
int main(){

   Dictionary D;
   //cout << "declared D" << endl;
   D.setValue("Account 1", 400);
   // cout << "I set the value of D" << endl;
   cout << D << endl;
   D.setValue("Account 2", 800);
   cout << D << endl;
   D.setValue("Account 2", 600);
   cout << D << endl;
   D.setValue("Account 3", 1200);
   cout << D << endl;
   D.setValue("Account 4", 700);
   cout << D << endl;

   string s;
   int x;
   string S[] =   {
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
   string T[] =   {
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

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

   // call copy constructor
   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << A.getValue("hemiolia") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   // remove some pairs from A
   for(int i=0; i<13; i++){
      cout << "removing " << T[i] << " from Dictionary A" << endl; 
      A.remove(T[i]);
   }

   cout << "after remove loop" << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   //I ADDED THIS
   A.begin();
   cout << "Is current defined?:" << (A.hasCurrent()?"true":"false") << endl;
   s = A.currentKey();
   x = A.currentVal();
   cout << "("+s+", " << x << ") ";
   A.next();
   cout << "Is current defined?:" << (A.hasCurrent()?"true":"false") << endl;
   s = A.currentKey();
   x = A.currentVal();
   cout << "("+s+", " << x << ") ";
   A.prev();
   A.prev();
   cout << "Is current defined?:" << (A.hasCurrent()?"true":"false") << endl;
   A.end();
   A.next();
   cout << "Is current defined?:" << (A.hasCurrent()?"true":"false") << endl;


   // do forward iteration on A
   for(A.begin(); A.hasCurrent(); A.next()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on A
   for(A.end(); A.hasCurrent(); A.prev()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;
   
   // check exceptions
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

A==B is false
B==C is true
C==A is false

22
220

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

plaices
ambusher
crosby
cohabit
cantling
pardoner
forms
depressants
cul
deschooler
dissocialised
impales
hemiolia
glamorized
glagolitic
norm
millesimal
pic
wattles
pythons
potables
second
recriminator
recoining
reinsurer
verticals

removing second from Dictionary A
removing forms from Dictionary A
removing impales from Dictionary A
removing pic from Dictionary A
removing verticals from Dictionary A
removing recriminator from Dictionary A
removing depressants from Dictionary A
removing cul from Dictionary A
removing potables from Dictionary A
removing norm from Dictionary A
removing reinsurer from Dictionary A
removing deschooler from Dictionary A
removing recoining from Dictionary A
after remove loop
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

plaices
ambusher
crosby
cohabit
cantling
pardoner
glagolitic
dissocialised
millesimal
hemiolia
glamorized
wattles
pythons

(ambusher, 2) (cantling, 23) (cohabit, 21) (crosby, 3) (dissocialised, 20) (glagolitic, 26) (glamorized, 24) (hemiolia, 220) (millesimal, 25) (pardoner, 5) (plaices, 1) (pythons, 6) (wattles, 4) 

(wattles, 4) (pythons, 6) (plaices, 1) (pardoner, 5) (millesimal, 25) (hemiolia, 220) (glamorized, 24) (glagolitic, 26) (dissocialised, 20) (crosby, 3) (cohabit, 21) (cantling, 23) (ambusher, 2) 

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