#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "binaryTree.h"
#include "bstream.h"
#include <string>
#include <fstream>

class Compress : public BinaryTree {
    std::ifstream ifs;
    std::ofstream ofs;
    obstream obs;
    Node *root;
    void buildTree();
    void encodeTree();
    void encodeContent();
    void output();
 public:
    Compress(const std::string &infilename, 
             const std::string &outfilename);
};

class Decompress : public BinaryTree {
    std::ifstream ifs;
    std::ofstream ofs;
    Node *root;
    void decodeTree(ibstream&);
    void decodeContent(ibstream&);
 public:
    Decompress(const std::string &infilename, 
               const std::string &outfilename);
};

#endif