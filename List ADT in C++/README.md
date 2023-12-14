## List.h
This is a headerfile that defines all the functions that are written in List.c. It is to be used by the client, so that they do not have to open List.c and see the implementation of each function. 

## List.cpp
This is the file that contains the List ADT. All the functions of the ADT are written here. The client does not see this. 

## ListTest.cpp
This is a test file for the List ADT. It tests all functions of the ADT. 

## Shuffle.cpp
This is a file that uses the List ADT to ... The executable Shuffle must be called with an input file and output file: ./FindPath <inputFile.txt> <outputFile.txt>

## Makefile
The Makefile creates the executables Suffle and ListTest. It has the ability to clean the executables and .o files created during compilation with the command 'make clean'. It also checks ListTest and Suffle for memory leaks using the commands 'make check1' and 'make check2' respectively.

### Author: 
Githika Annapureddy
CruzID: gannapur
Assignment: pa5

