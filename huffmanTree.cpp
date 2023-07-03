#include "huffmanTree.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

void Compress::buildTree() {
    std::vector<Node*> ns;
    std::cout << "!" << std::flush;
    for (int i = 0; i < 128; ++i) {
        ns.push_back(new Node{(char)i, 0, nullptr, nullptr});
    }
    std::cout << "!" << std::flush;
    // // DEBUG
    // for (auto n : ns) {
    //     std::cout << (int) n->c << ' ';
    // }
    // std::cout << "!" << std::flush;

    char ch;
    while (ifs.get(ch)) {
        if (ch <= 0) continue; 
        ns[ch]->n++;
    }
    std::cout << "!" << std::flush;
    ns[0]->n++;
    assert(ns[0]->n == 1);
    sort(ns.begin(), ns.end(), compare);
    while (ns.back()->n == 0) {
        delete ns.back();
        ns.pop_back();
    }
    std::cout << "!" << std::flush;
    while (ns.size() > 1) {
        Node *r = ns.back(); ns.pop_back();
        Node *l = ns.back(); ns.pop_back();
        ns.push_back(merge(l, r));
        sort(ns.begin(), ns.end(), compare);
    }
    std::cout << "!" << std::flush;
    root = ns[0];
    printTree_finer(root);
}

void Compress::encodeTree() {
    encode(root, obs);
    obs << (bool)1;
}

void Compress::encodeContent() {
    std::vector<std::string> pathMap(128);
    for (int i = 0; i < 128; ++i) {
        pathMap[i] = findPath(root, (char)i);
    }
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    char ch;
    while (ifs.get(ch)) {
        //TODO: make uchar
        if (ch <= 0) continue;

        for (char bit : pathMap[ch]) {
            obs << (bool) bit;
        }
    }
    for (char bit : pathMap[0]) {
        obs << (bool) bit;
    }
    ifs.close();
}

void Compress::output() {
    ofs << obs.str();
    ofs.close();
}

Compress::Compress(const std::string &infilename, 
                   const std::string &outfilename) :
    ifs(infilename), ofs(outfilename) {
    std::cout << "!" << std::flush;
    buildTree();
    std::cout << "!" << std::flush;
    encodeTree();
    std::cout << "!" << std::flush;
    encodeContent();
    std::cout << "!" << std::flush;
    output();
    std::cout << "!" << std::flush;
}

// ---------------------------- //


void Decompress::decodeTree(ibstream &ibs) {
    std::vector<Node*> ns;
    bool good = true;
    bool bit;
    ibs >> bit;
    while (good) {
        char ch;
        ibs >> ch;
        // std::cout << ch << std::flush;
        // assert(ch >= 0);
        ns.push_back(new Node{ch, 0, nullptr, nullptr});
        // std::cout << " ? " << std::endl;
        // assert(ibs.good());
        ibs >> bit;
        // std::cout << bit << ' ';
        while (bit) {
            if (ns.size() < 2) {
                good = false;
                break;
            }
            auto *n_r = ns.back(); ns.pop_back();
            auto *n_l = ns.back(); ns.pop_back();
            ns.push_back(merge(n_l, n_r));
            ibs >> bit;
        }
    }
    // printTree_finer(ns[0]);
    root = ns[0];
}

void Decompress::decodeContent(ibstream &ibs) {

    // while (ibs.good()) {
    //     bool bit;
    //     ibs >> bit;
    //     std::cout << bit;
    // }
    // std::cout << std::endl;
    // assert(0);

    Node *step = root;
    while (true) {
        assert(ibs.good());
        bool bit;
        ibs >> bit;
        // std::cout << bit << std::flush;
        if (bit) step = step->r;
        else     step = step->l;
        if (!step->r && !step->l) {
            // std::cout << step->c << std::flush;
            if (step->c == 0) {
                // std::cout << "OK" << std::flush;
                break;
            }
            ofs << step->c;
            step = root;
        }
    }
    // std::cout << "!!!" << std::endl;
}

Decompress::Decompress(const std::string &infilename, 
                       const std::string &outfilename) :
    ifs(infilename), ofs(outfilename) {
    std::stringstream buf;
    buf << ifs.rdbuf();
    ibstream ibs(buf.str());
    // bool bit;
    // while (ibs.good()) {
    //     ibs >> bit;
    //     std::cout << bit;
    // }
    // std::cout << std::endl;
    // assert(0);

    ifs.close();
    decodeTree(ibs);
    decodeContent(ibs);
    ofs.close();
}
