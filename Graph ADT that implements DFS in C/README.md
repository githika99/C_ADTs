## List.h
This is a headerfile that defines all the functions that are written in List.c. It is to be used by the client, so that they do not have to open List.c and see the implementation of each function. 

## List.c
This is the file that contains the List ADT. All the functions of the ADT are written here. The client does not see this. 

## Graph.h
This is a headerfile that defines all the functions that are written in Graph.c. It is to be used by the client, so that they do not have to open Graph.c and see the implementation of each function. 

## Graph.c
This is the file that contains the Graph ADT. All the functions of the ADT are written here. In addition to standard Graph functions, this file computes Depth First Search and finds the transpose of a give Graph. The client does not see these functions.

## GraphTest.c
This is a test file for the Graph ADT. It tests all functions of the ADT. 

## FindComponents.c
This is a file that uses the Graph ADT to find the strongly connected components of the Graph given by verticies in inputFile. The executable FindComponents must be called with an input file and output file: ./FindComponents <inputFile.txt> <outputFile.txt>

## Makefile
The Makefile creates the executables FindComponents and GraphTest. It has the ability to clean the executables and .o files created during compilation with the command 'make clean'. It also checks GraphTest and FindComponents for memory leaks using 'make checkTest' and 'make checkFind'.

### Author: 
Githika Annapureddy
CruzID: gannapur
Assignment: pa3
