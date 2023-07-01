#include "binaryTree.h"
#include "huffmanTree.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

class VecNode {
    std::vector<Node*> v;
    void merge() {
        if (v.size() == 1) return;
        std::sort(v.begin(), v.end(), cmpNode);
        auto *n_r = v.back(); v.pop_back();
        auto *n_l = v.back(); v.pop_back();
        v.push_back(Node::mergeNodes(n_l, n_r));
        merge();
    }
 public:
    void recordStr(const std::string &str) {
        for (auto &n : v) {
            if (n->getstr() == str) {
                n->incnum();
                return;
            }
        }
        v.push_back(new Node(str, 1));
    }
    static bool cmpNode(const Node *n1, const Node *n2) {
        if (n1->getnum() != n2->getnum()) {
            return n1->getnum() > n2->getnum();
        } else {
            return n1->getstr()[0] > n2->getstr()[0];
        }
    }
    Node *getNode() {
        merge();
        return v[0];
    }
};

int main(int argc, char *argv[]) {
    std::string fileName;
    bool treeMode = false;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-tree") {
            treeMode = true;
        } else {
            fileName = argv[i];
        }
    }
    VecNode vn;
    std::ifstream ifs(fileName);
    char str[2] = " ";
    while (ifs.get(str[0])) {
        vn.recordStr(std::string(str));
    }
    ifs.close();
    HuffmanTree tree(vn.getNode());
    //printTree_finer(HuffmanTree(node));
    if (treeMode) {
        tree.printTree();
        return 0;
    }
    
    std::ifstream ifs2(fileName);
    while (ifs2.get(str[0])) {
        std::cout << tree.findPath(std::string(str)) << ' ';
    }
    std::cout << std::endl;
    ifs2.close();
    return 0;
}