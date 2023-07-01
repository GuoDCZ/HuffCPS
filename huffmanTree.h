#ifndef P4_HUFFMANTREE_H
#define P4_HUFFMANTREE_H

#include "binaryTree.h"
#include "bstream.h"

class HuffmanTree : public BinaryTree {
    // Huffman tree

public:
    HuffmanTree(Node *rootNode = nullptr); 

    HuffmanTree(ibstream &ibs);
    
    void decode(ibstream &ibs);

    void encode(obstream &obs);
    
};

#endif