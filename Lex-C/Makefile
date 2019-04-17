#PatrickStumps
#pstumps@ucsc.edu
#CMPS 101
#PA2
#Makefile for PA2

all:	ListClient

List.o: List.c List.h
	gcc -c -std=c99 -Wall List.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o: ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

Lex: Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o: Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

clean:
	rm -f Lex Lex.o ListClient.o List.o out



