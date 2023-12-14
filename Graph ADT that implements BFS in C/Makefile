#Githika Annapureddy
#CruzId: gannapur
#Assignment: pa2
#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------
BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) ./FindPath FindPath.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) ./GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

#take out if ever resubmitting, this is for compiling a file I made called midterm-review.c
midterm-review : midterm-review.o $(BASE_OBJECTS)
	$(LINK) ./midterm-review midterm-review.o $(BASE_OBJECTS)

midterm-review.o : midterm-review.c $(HEADERS)
	$(COMPILE) midterm-review.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphTest FindPath.o GraphTest.o midterm-review midterm-review.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) ./FindPath in7.txt junk7.txt

checkTest : GraphTest
	$(MEMCHECK) ./GraphTest

#take out if ever resubmitting, this is for compiling a file I made called midterm-review.c
checkReview: midterm-review
	$(MEMCHECK) ./midterm-review