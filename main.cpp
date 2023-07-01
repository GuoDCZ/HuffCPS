#include <iostream>
#include "bstream.h"
#include <string>
//#include "huffmanTree.h"

//#include "huffmanTreeFiner.cpp"

int main() {
    std::string str;
    char c_str[100];
    while (getline(std::cin, str)) {
        ibstream ibs(str);
        // std::cout << ibs.bp.it - ibs.str.begin() << std::endl;
        // std::cout << ibs.bp.it - ibs.str.begin() << std::endl;
        //std::cout << str << std::endl;
        //ibs.bp.get();
        while (ibs.good()) {
            std::cout << ibs.getbit(); 
            std::cout << ibs.getchar();
        }
        std::cout << std::endl;
    }
    return 0;
}