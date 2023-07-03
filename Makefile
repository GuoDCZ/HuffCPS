all: huffcps

huffcps: bstream.o main.o binaryTree.o huffmanTree.o huffmanTreeFiner.o
	g++ -o huffcps.out bstream.o main.o binaryTree.o huffmanTree.o huffmanTreeFiner.o

bstream.o: bstream.cpp
	g++ -c bstream.cpp

main.o: main.cpp
	g++ -c main.cpp

binaryTree.o: binaryTree.cpp
	g++ -c binaryTree.cpp

huffmanTree.o: huffmanTree.cpp
	g++ -c huffmanTree.cpp

huffmanTreeFiner.o: huffmanTreeFiner.cpp
	g++ -c huffmanTreeFiner.cpp

clear:
	rm *.o
