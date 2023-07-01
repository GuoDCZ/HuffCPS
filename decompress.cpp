#include "binaryTree.h"
#include "huffmanTree.h"
#include <string>
#include <fstream>
#include <iostream>

std::string query(const Node *n, const std::string &code) {
    if (code.empty()) {
        return n->getstr();
    }
    if (code[0] == '0') {
        return query(n->leftSubtree(), code.substr(1));
    }
    else {
        return query(n->rightSubtree(), code.substr(1));
    }
};

int main(int argc, char *argv[]) {
    const std::string treeFilename(argv[1]), 
                      compressedFile(argv[2]);
    const HuffmanTree tree(treeFilename);
    std::ifstream ifs(compressedFile);
    std::string code;
    while (ifs) {
        ifs >> code;
        if (!ifs) break;
        std::string str = query(tree.root, code);
        std::cout << str[0];
    }
    ifs.close();
    return 0;
}