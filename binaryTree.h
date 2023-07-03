#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <vector>
#include "bstream.h"

struct Node {
    char c;
    int n;
    Node *l, *r;
};

class BinaryTree {
 public:
    static Node *merge(Node *l, Node *r);
    static void free(const Node *n);
    static Node *copy(const Node *n);
    static std::string findPath(const Node *n, char c);
    static int depth(const Node *n);
    static void encode(const Node *n, obstream &obs);
    static bool compare(const Node *l, const Node *r);
};


struct Pos {int row, col;};
struct Item {std::string str, leaf;};

class Fig {
    std::vector<std::vector<Item>> fig;
    Pos pos;
    void autoFill();
 public:
    Fig();
    void print();
    void operator<= (Item item);
    void downToLeft();
    void downToRight();
    void UpFromLeft();
    void UpFromRight();
};

bool isPrintableChar(char ch);

void printTree_finer_helper(Fig &fig, const Node *n);
void printTree_finer(const Node *n);


#endif