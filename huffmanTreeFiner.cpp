#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "binaryTree.h"
#include <string>

void Fig::autoFill() {
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

Fig::Fig(): pos({0,0}) {
        autoFill();
    }

void Fig::print() {
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
void Fig::operator<= (Item item) {fig[pos.row].push_back(item); }
void Fig::downToLeft() {pos.row++; autoFill(); }
void Fig::downToRight() {pos.row++; pos.col++; autoFill(); }
void Fig::UpFromLeft() {pos.row--; autoFill(); }
void Fig::UpFromRight() {pos.row--; pos.col--; autoFill(); }

bool isPrintableChar(char ch) {
    return ch > 32;
}

void printTree_finer_helper(Fig &fig, const Node *n) {
    if (n->l) {
        fig.downToLeft();
        printTree_finer_helper(fig, n->l); 
        fig.UpFromLeft();
    }
    if (n->r) {
        fig.downToRight();
        printTree_finer_helper(fig, n->r);
        fig.UpFromRight();
    }
    std::string sym;
    if (!n->l || !n->r) {
        sym = "";
        if (isPrintableChar(n->c)) {
            char str[] = " ";
            str[0] = n->c;
            fig <= Item({std::string(str), sym});
        }
        else {
            fig <= Item({std::to_string(n->c), sym});
        }
    } else {
        if (n->l) sym = "/  ";
        if (n->r) sym = "\\";
        if (n->r && n->l) sym = "/ \\";
        fig <= Item({std::to_string(n->n), sym});
    }
}

void printTree_finer(const Node *n) {
    Fig fig;
    printTree_finer_helper(fig, n);
    fig.print();
}
