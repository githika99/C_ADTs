## List.h
This is a headerfile that defines all the functions that are written in List.cpp. It is to be used by the client, so that they do not have to open List.cpp and see the implementation of each function. 

## List.cpp
This is the file that contains the List ADT. All the functions of the ADT are written here. The client does not see this. 

## ListTest.cpp
This is a test file for the List ADT. It tests all functions of the ADT. 

## BigInteger.h
This is a headerfile that defines all the functions that are written in BigInteger.cpp. It is to be used by the client, so that they do not have to open BigInteger.cpp and see the implementation of each function. 

## BigInteger.cpp
This is the file that contains the BigInteger ADT. All the functions of the ADT are written here. The client does not see this. 

## BigIntegerTest.cpp
This is a test file for the BigInteger ADT. It tests all functions of the ADT. 

## Arithmetic.cpp
This is a file that uses the BigInteger ADT to call operations on 2 BigIntegers. Arithmetic.cpp must be called with an input file and output file: ./Arithmetic <inputFile.txt> <outputFile.txt>

## Makefile
The Makefile creates the executables Arithmetic, ListTest, and BigIntegerTest. It has the ability to clean the executables and .o files created during compilation with the command 'make clean'. It also checks for memory leaks using 'make ArithmeticCheck', 'make ListCheck', and 'make BigIntegerCheck'.

### Author: 
Githika Annapureddy
CruzID: gannapur
Assignment: pa6