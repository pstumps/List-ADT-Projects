BASE_SOURCES   = List.c Graph.c
BASE_OBJECTS   = List.o Graph.o 
HEADERS        = List.h Graph.h 
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

clean :
	$(REMOVE) GraphTest GraphTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in3 junk3

checkTest : GraphTest
	$(MEMCHECK) GraphTest