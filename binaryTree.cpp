#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) :
    str(str), num(num), left(left), right(right) {}

Node* Node::leftSubtree() const{
    return left;
}

void Node::setleft(Node *n) {
    left = n;
}

Node* Node::rightSubtree() const{
    return right;
}

void Node::setright(Node *n) {
    right = n;
}

string Node::getstr() const {
    return str; 
}

int Node::getnum() const {
    return num;
}

void Node::incnum() {
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    return new Node(leftNode->getstr() + rightNode->getstr(),
                    leftNode->getnum() + rightNode->getnum(),
                    leftNode, rightNode);
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode) : 
    root(rootNode) { }

void BinaryTree_deconstructor_helper (const Node *n) {
    if (!n) return;
    BinaryTree_deconstructor_helper(n->leftSubtree());
    BinaryTree_deconstructor_helper(n->rightSubtree());
    delete n;
}

BinaryTree::~BinaryTree() {
    BinaryTree_deconstructor_helper(root);
}

string findPath_helper(const string &s, const Node *n) {
    if (!n) return "-1";
    if (n->getstr() == s) return "";
    const string &str_l = findPath_helper(s, n->leftSubtree());
    if (str_l != "-1") return "0" + str_l;
    const string &str_r = findPath_helper(s, n->rightSubtree());
    if (str_r != "-1") return "1" + str_r;
    return "-1";
}

string BinaryTree::findPath(const string &s) const {
    return findPath_helper(s, root);
}

int sum_helper(const Node *n) {
    if (!n) return 0;
    int sum_l = sum_helper(n->leftSubtree());
    int sum_r = sum_helper(n->rightSubtree());
    return n->getnum() + sum_l + sum_r;
}

int BinaryTree::sum() const {
    return sum_helper(root);
}

inline int intMax(int a, int b) {return a > b ? a : b;}

int depth_helper(const Node *n) {
    if (!n) return 0;
    int depth_l = depth_helper(n->leftSubtree());
    int depth_r = depth_helper(n->rightSubtree());
    return 1 + intMax(depth_l, depth_r);
}

int BinaryTree::depth() const {
    return depth_helper(root);
}

void preorder_num_helper(const Node *n) {
    if (!n) return;
    cout << n->getnum() << ' ';
    preorder_num_helper(n->leftSubtree());
    preorder_num_helper(n->rightSubtree());
}

void BinaryTree::preorder_num() const {
    preorder_num_helper(root);
    cout << endl;
}

void inorder_str_helper(const Node *n) {
    if (!n) return;
    inorder_str_helper(n->leftSubtree());
    string str = n->getstr();
    if (str == "\n") str = "\\n";
    cout << str << ' ';
    inorder_str_helper(n->rightSubtree());
}

void BinaryTree::inorder_str() const {
    inorder_str_helper(root);
    cout << endl;
}

void postorder_num_helper(const Node *n) {
    if (!n) return;
    postorder_num_helper(n->leftSubtree());
    postorder_num_helper(n->rightSubtree());
    cout << n->getnum() << ' ';
}

void BinaryTree::postorder_num() const {
    postorder_num_helper(root);
    cout << endl;
}

inline int intMin(int a, int b) {return a < b ? a : b;}

int minPathSum(const Node *n) {
    if (!n) return 0;
    int max_l = minPathSum(n->leftSubtree());
    int max_r = minPathSum(n->rightSubtree());
    return n->getnum() + intMin(max_l, max_r);
}

bool BinaryTree::allPathSumGreater(int sum) const {
    return minPathSum(root) > sum;
}

bool covered_by_helper(const Node *a, const Node *b) {
    if (!a) return true;
    if (!b) return false;
    return a->getnum() == b->getnum()
        && covered_by_helper(a->leftSubtree(), b->leftSubtree())
        && covered_by_helper(a->rightSubtree(), b->rightSubtree());
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return covered_by_helper(root, tree.root);
}

bool contained_by_helper(const Node *a, const Node *b) {
    if (!b) return false;
    return covered_by_helper(a, b)
        || contained_by_helper(a, b->leftSubtree())
        || contained_by_helper(a, b->rightSubtree());
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    return contained_by_helper(root, tree.root);
}

Node *copy_helper(const Node *n) {
    if (!n) return nullptr;
    Node *n_l = copy_helper(n->leftSubtree());
    Node *n_r = copy_helper(n->rightSubtree());
    return new Node(n->getstr(), n->getnum(), n_l, n_r);
}

BinaryTree BinaryTree::copy() const {
    return BinaryTree(copy_helper(root));
}
