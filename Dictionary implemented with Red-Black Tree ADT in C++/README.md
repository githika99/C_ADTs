## Dictionary.h
This is a headerfile that defines all the functions that are written in Dictionary.cpp. It is to be used by the client, so that they do not have to open Dictionary.cpp and see the implementation of each function. 

## Dictionary.cpp
This is the file that contains the Dictionary ADT. All the functions of the ADT are written here. The client does not see this. 

## DictionaryTest.cpp
This is a test file for the Dictionary ADT. It tests all functions of the ADT. 

## Order.cpp
This is a file that uses the Dictionary ADT to read in dictionary values and output the key, value pairs in alphabetical order and the values in the order obtained from a pre-order tree walk. Order.cpp must be called with an input file and output file: ./Order <inputFile.txt> <outputFile.txt>

## WordFrequency.cpp
This is a file that uses the Dictionary ADT to read in strings, puts them into a Dictionary, and outputs them alphabtized with the value being the number of that strings occurance in the inputfile. WordFrequency.cpp must be called with an input file and output file: ./WordFrequency <inputFile.txt> <outputFile.txt>

## Makefile
The Makefile creates the executables Order and DictionaryTest. It has the ability to clean the executables and .o files created during compilation with the command 'make clean'. It also checks for memory leaks using 'make OrderCheck' and 'make DictionaryCheck'.

### Author: 
Githika Annapureddy
CruzID: gannapur
Assignment: pa7