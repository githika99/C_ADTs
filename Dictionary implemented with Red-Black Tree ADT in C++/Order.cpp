/*
Githika Annapureddy
Cruz Id: gannapur
pa8
*/
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;


int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      in.close();
      return(EXIT_FAILURE);
   } 

   Dictionary A;
   string line;
   int count = 1;
   while(getline(in, line))  {
      A.setValue(line, count);
      count++;
   }
   
   out << A << endl;
   out << A.pre_string() << endl;





    // close files 
    in.close();
    out.close();
    return(EXIT_SUCCESS);
}

//comment