/*
Githika Annapureddy
CruzId: gannapur
pa6
*/
#include<iostream>
#include<fstream>
#include <string>
#include "List.h"
#include"BigInteger.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Check if there are exactly three command-line arguments (program name, input file, and output file)
    if (argc != 3) {
        cerr << "Not in format. Please use: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);    
    }

    // Extract the input and output file names from command-line arguments
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    
    // open files for read and write
    ifstream inputFile;
    inputFile.open(inputFileName);
    if(!inputFile.is_open()){
        cerr << "Unable to open file " << inputFileName << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    ofstream outputFile;
    outputFile.open(outputFileName);
    if(!outputFile.is_open()){
        inputFile.close();
        cerr << "Unable to open file " << outputFileName << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read in strings for big int
    string s1, s2;
    inputFile >> s1;
    inputFile >> s2;

    // make big int objects
    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s2);
    //𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴2, 2, 9𝐴4 + 16𝐵5

    outputFile << A << endl << endl;
    outputFile << B << endl << endl;
    outputFile << A.add(B) << endl << endl;
    outputFile << A.sub(B) << endl << endl;
    outputFile << A.sub(A) << endl << endl;
    outputFile << 3*A - 2*B << endl << endl;
    outputFile << A.mult(B) << endl << endl;
    outputFile << A.mult(A) << endl << endl;
    outputFile << B.mult(B) << endl << endl;
    outputFile << 9*(A*A*A*A) + 16*(B*B*B*B*B)<< endl << endl;

    inputFile.close();
    outputFile.close();
    exit(EXIT_SUCCESS);
}