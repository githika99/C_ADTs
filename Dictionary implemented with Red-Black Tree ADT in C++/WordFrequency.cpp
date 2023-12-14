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

    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    string key, line;


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
    in.close();
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
    Dictionary D;

    while (getline(in, line)) {
        len = line.length();

        // Get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        key = line.substr(begin, (end - begin));

        while (key != "") {
            // make lower case and update token buffer
            for (size_t c = 0; c < key.length(); c++) {
                key[c] = tolower(key[c]);
            }

            // Add to dictionary
            if (D.contains(key)) {
                D.getValue(key)++;
            } else {
                D.setValue(key, 1);
            }

            // get next token
            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            key = line.substr(begin, (end - begin));
        }
    }

    out << D << endl;

   // close files 
   in.close();
   out.close();
   return(EXIT_SUCCESS);
}