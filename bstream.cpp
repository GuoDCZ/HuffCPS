#include "bstream.h"

#include <iostream>

// ------- bstream: Basic Bit Stream ------- //

void bstream::get(bool &bit) {
    if (good()) bit = bitstr[index++];
    else bit = 0;
}

void bstream::get(char &ch) {
    ch = 0;
    bool bit;
    for (int i = 7; i >= 0; --i) {
        get(bit);
        ch |= bit << i;
    }
}

void bstream::get(char str[]) {
    while (good()) get(*(str++));
    *str = 0;
}

void bstream::get(std::string &str) {
    str.clear();
    char ch;
    while (good()) {
        get(ch);
        str += ch;
    }
}

bool bstream::good() {
    // std::cout << "IN GOOD: " << bitstr.size() - index << std::endl;
    return index < bitstr.size();
}

void bstream::set(bool bit) {
    // std::cout << "IN SET BIT 1: " << bitstr << std::endl;
    bitstr += bit;
    // std::cout << "IN SET BIT 2: " << bitstr << std::endl;
}

void bstream::set(char ch) {
    // std::cout << "IN SET CH 1: " << bitstr << std::endl;
    for (int i = 7; i >= 0; --i) set((bool)(ch & 1 << i));
    // std::cout << "IN SET CH 2: " << bitstr << std::endl;
}

void bstream::set(const char str[]) {
    // std::cout << "IN SET STR 1: " << bitstr << std::endl;
    set(std::string(str));
    // std::cout << "IN SET STR 2: " << bitstr << std::endl;
}

void bstream::set(const std::string &str) {
    // std::cout << "IN SET STR 1: " << bitstr << std::endl;
    for (char ch : str) set(ch);
    // std::cout << "IN SET STR 2: " << bitstr << std::endl;
}

// ------- ibstream: IN Bit Stream ------- //

ibstream::ibstream() { };

ibstream::ibstream(bool bit) {
    set(bit);
}

ibstream::ibstream(char ch) {
    set(ch);
}

ibstream::ibstream(const std::string &str) {
    // std::cout << "IN bstream CONS 1: " << bitstr << std::endl;
    set(str);
    // std::cout << "IN bstream CONS 2: " << bitstr << std::endl;
}

ibstream::ibstream(const char str[]) :
    ibstream(std::string(str)) { }


bool ibstream::good() {
    // std::cout << "IN GOOD: " << bitstr.size() - index << std::endl;
    return bstream::good();
}

void ibstream::read(bool *p, std::size_t s) {
    while (s--) get(*(p++));
}

void ibstream::read(char *p, std::size_t s) {
    while (s--) get(*(p++));
}

void ibstream::read(std::string &str) {
    get(str);
}

ibstream &ibstream::operator>>(bool &bit) {
    get(bit);
    return *this;
}

ibstream &ibstream::operator>>(char &ch) {
    get(ch);
    return *this;
}

ibstream &ibstream::operator>>(char str[]) {
    get(str);
    return *this;
}

ibstream &ibstream::operator>>(std::string &str) {
    get(str);
    return *this;
}

// ------- obstream: OUT Bit Stream ------- //

std::string obstream::str() {
    std::string s;
    get(s);
    return s;
}

void obstream::write(const bool *p, std::size_t s) {
    while (s--) set(*(p++));
}

void obstream::write(const char *p, std::size_t s) {
    while (s--) set(*(p++));
}

void obstream::write(const std::string &str) {
    set(str);
}

obstream &obstream::operator<<(bool bit) {
    set(bit);
    return *this;
}

obstream &obstream::operator<<(char ch) {
    set(ch);
    return *this;
}

obstream &obstream::operator<<(const std::string &str) {
    set(str);
    return *this;
}

obstream &obstream::operator<<(const char str[]) {
    set(str);
    return *this;
}
