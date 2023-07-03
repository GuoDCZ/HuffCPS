#include <iostream>
#include "bstream.h"
#include <string>
#include <cstdio>
#include "huffmanTree.h"

//#include "huffmanTreeFiner.cpp"

int main(int argc, char *argv[]) {

    bool CPS = false, DEC = false, RM = false;

    std::vector<std::string> filenameList;

    for (int i = 1; i < argc; ++i) {
	    const std::string arg = argv[i];
	    if (arg == "-c" || arg == "--compress") CPS = true;
        else if (arg == "-d" || arg == "--decompress") DEC = true;
        else if (arg == "-r" || arg == "--remove") RM = true;
	    else filenameList.push_back(arg);
    }

    for (const std::string &filename : filenameList) {
        if (CPS && !DEC) {
            Compress(filename, filename+".cps");
        }
        else if (!CPS && DEC) {
            std::string outFilename;
            if (filename.substr(filename.find_last_of('.')+1) == "cps") {
                outFilename = filename.substr(0, filename.size()-4);
            } else {
                outFilename = filename + ".txt";
            }
            Decompress(filename, outFilename);
        }
        else {
            std::string outFilename;
            if (filename.substr(filename.find_last_of('.')+1) == "cps") {
                outFilename = filename.substr(0, filename.size()-4);
                Decompress(filename, outFilename);
            } else {
                outFilename = filename + ".cps";
                Compress(filename, outFilename);
            }
        }
        if (RM) {
            remove(filename.c_str());
        }
    }

    // Compress("t1.txt", "t2.txt");
    // Decompress("t2.txt", "t3.txt");


    // std::ifstream ifs("t2.txt", std::ios::binary);
    // char ch;
    // while (ifs.get(ch)) std::cout << (int) ch << ' ';
    // std::cout << std::endl;
    // std::string str;
    // while (getline(std::cin, str)) {
    //     std::cout << ibs.bitstr.size() << std::endl;
    //     std::cout << ibs.bp.it - ibs.str.begin() << std::endl;
    //     std::cout << ibs.bp.it - ibs.str.begin() << std::endl;
    //     std::cout << str << std::endl;
    //     ibs.bp.get();
    //     ibstream ibs(str);
    //     bool bit;
    //     ibs >> bit;
    //     char ch;
    //     ibs >> ch;
    //     std::cout << ch << std::endl;
    // }
    return 0;
}
