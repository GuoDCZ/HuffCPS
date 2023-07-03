#include "binaryTree.h"
#include <string>

Node *BinaryTree::merge(Node *l, Node *r) {
    return new Node{-1, l->n + r->n, l, r};
}

void BinaryTree::free(const Node *n) {
    if (!n) return;
    free(n->l);
    free(n->r);
    delete n;
}

Node *BinaryTree::copy(const Node *n) {
    if (!n) return nullptr;
    return new Node{0, n->n, copy(n->l), copy(n->r)};
}

std::string BinaryTree::findPath(const Node *n, char s) {
    if (!n) return "-1";
    if (n->c == s) return "";
    const std::string &str_l = findPath(n->l, s);
    if (str_l != "-1") return (char)0 + str_l;
    const std::string &str_r = findPath(n->r, s);
    if (str_r != "-1") return (char)1 + str_r;
    return "-1";
}

int BinaryTree::depth(const Node *n) {
    if (!n) return 0;
    int depth_l = depth(n->l);
    int depth_r = depth(n->r);
    return 1 + (depth_l > depth_r ? depth_l : depth_r);
}

void BinaryTree::encode(const Node *n, obstream &obs) {
    if (!n->l && !n->r) {
        obs << (bool)0 << n->c;
    } else {
        encode(n->l, obs);
        encode(n->r, obs);
        obs << (bool)1;
    }
}

bool BinaryTree::compare(const Node *l, const Node *r) {
    if (l->n != r->n) return l->n > r->n;
    else              return l->c > r->c;
}
