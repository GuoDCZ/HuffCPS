all: main

main: bstream.o main.o binaryTree.o
	g++ -o main bstream.o main.o binaryTree.o

bstream.o: bstream.cpp bstream.h
	g++ -c bstream.cpp

main.o: main.cpp
	g++ -c main.cpp

binaryTree.o: binaryTree.cpp
	g++ -c binaryTree.cpp

clear:
	rm *.o