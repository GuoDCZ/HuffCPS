#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "huffmanTree.cpp"

struct Pos {int row, col;};
struct Item {std::string str, leaf;};

class Fig {
    std::vector<std::vector<Item>> fig;
    Pos pos;
    void autoFill() {
        while (pos.row >= fig.size()) {
            fig.push_back(std::vector<Item>({}));
        }
        while (pos.col > fig[pos.row].size()) {
            fig[pos.row].push_back({"",""});
        }
        while (pos.col < fig[pos.row].size()) {
            pos.col++;
        }
    }
 public:
    Fig(): pos({0,0}) {
        autoFill();
    }
    void print() {
        int depth = fig.size();
        for (auto row : fig) {
            std::cout << std::setw(2*depth) << "";
            for (auto str : row) {
                std::cout << std::setw(4) << str.str;
            }
            std::cout << std::endl;
            std::cout << std::setw(2*depth+1) << "";
            for (auto str : row) {
                std::cout << std::setw(4) << str.leaf;
            }
            std::cout << std::endl;
            depth--;
        }
    }
    void operator<= (Item item) {fig[pos.row].push_back(item); }
    void downToLeft() {pos.row++; autoFill(); }
    void downToRight() {pos.row++; pos.col++; autoFill(); }
    void UpFromLeft() {pos.row--; autoFill(); }
    void UpFromRight() {pos.row--; pos.col--; autoFill(); }
};

void printTree_finer_helper(Fig &fig, const Node *n) {
    bool l = n->leftSubtree(), r = n->rightSubtree();
    if (l) {
        fig.downToLeft();
        printTree_finer_helper(fig, n->leftSubtree()); 
        fig.UpFromLeft();
    }
    if (r) {
        fig.downToRight();
        printTree_finer_helper(fig, n->rightSubtree());
        fig.UpFromRight();
    }
    std::string sym;
    if (l & r) sym = "/ \\";
    else if (l) sym = "/  ";
    else if (r) sym = "\\";
    else sym = "";
    if (n->getstr().length() != 1) {
        fig <= Item({std::to_string(n->getnum()), sym});
    } else if (n->getstr()=="\n") {
        fig <= Item({"\\n", sym});
    } else {
        fig <= Item({n->getstr(), sym});
    }
    
}

void printTree_finer(const HuffmanTree &tree) {
    Fig fig;
    printTree_finer_helper(fig, tree.root);
    fig.print();
}
