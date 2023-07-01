#include "huffmanTree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

HuffmanTree::HuffmanTree(Node *rootNode) {
    this->root = rootNode;
}

HuffmanTree::HuffmanTree(ibstream &ibs) {
    decode(ibs);
}

void HuffmanTree::decode(ibstream &ibs) {
    std::vector<Node*> ns;
    char str[] = " ";
    char &ch = str[0];
    bool bit;
    bool good = true;
    while (good) {
        ibs >> bit;
        while (bit) {
            if (ns.size() < 2) {
                good = false;
                break;
            }
            auto *n_r = ns.back();
            ns.pop_back();
            auto *n_l = ns.back();
            ns.pop_back();
            auto *n_n = Node::mergeNodes(n_l, n_r); 
            ns.push_back(n_n);
            ibs >> bit;
        }
        ibs >> ch;
        ns.push_back(new Node(str, 0));
    }
    root = ns[0];
}

void encode_helper(obstream &obs, const Node *n) {
    if (!n) return;
    Node *n_l = n->leftSubtree(), *n_r = n->rightSubtree();
    if (!n_l && !n_r) {
        obs << (bool)0 << n->getstr()[0];
    }
    else {
        encode_helper(obs, n_l);
        encode_helper(obs, n_r);
        obs << (bool)1;
    }
}

void HuffmanTree::encode(obstream &obs) {
    encode_helper(obs, root);
    obs << (bool)1;
}