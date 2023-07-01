#include "bstream.h"

// ------- bptr: Bit Pointer ------- // 

bptr::bptr(str_it it, int o) : 
    it(it), o(o) { }

bool bptr::operator==(const_str_it it_) const {
    return it == it_;
}

bool bptr::operator!=(const_str_it it_) const {
    return it != it_;
}

bool bptr::get() const {
    return *it & 0x80 >> o;
}

void bptr::set(bool bit) const {
    if (bit) *it |= 0x80 >> o;
    else     *it &= (0x80 >> o) ^ 0xff;
}

bptr bptr::operator+(int i) const {
    if (i < 0) return operator-(-i);
    return {it + (o + i) / 8, (o + i) % 8};
}

bptr bptr::operator-(int i) const {
    if (i < 0) return operator+(-i);
    return {it + (o - i - 7) / 8, (o - i - 8) % 8 + 8};
}

bptr &bptr::operator++() {
    return *this = operator+(1);
}

bptr &bptr::operator--() {
    return *this = operator-(1);
}

bptr bptr::operator++(int) {
    bptr temp = *this;
    operator++();
    return temp;
}

bptr bptr::operator--(int) {
    bptr temp = *this;
    operator--();
    return temp;
}

// ------- bstream: basic Bit Stream ------- // 

bstream::bstream(std::string str_) :
    str(str_), bp(str.begin()) { }

bstream::bstream() :
    bp(str.begin()) { }

bool bstream::good() const {
    return bp != str.end();
}

// ------- ibstream: IN Bit Stream ------- // 

ibstream::ibstream(const std::string &str) :
    bstream(std::string(str)) { }

ibstream::ibstream(const char str[]) :
    bstream(std::string(str)) { }

ibstream::ibstream(const char &ch) :
    bstream(std::string(1, ch)) { }

void ibstream::write(bool *p, int size) {
    while (size-- > 0) *(p++) = getbit();
}

void ibstream::write(char *p, int size) {
    while (size-- > 0) *(p++) = getchar();
}

bool ibstream::getbit() {
    if (good()) return (bp++).get();
    return 0;
}

char ibstream::getchar() {
    obstream obs;
    for (int i = 0; i < 8; ++i) obs.setbit(getbit());
    return obs.getstr()[0];
}

// ------- obstream: OUT Bit Stream ------- // 

obstream::obstream() :
    bstream() { }

const std::string &obstream::getstr() const {
    return str;
}

void obstream::read(const bool *p, int size) {
    while (size-- > 0) setbit(*(p++));
}

void obstream::read(const char *p, int size) {
    while (size-- > 0) setchar(*(p++));
}

void obstream::setbit(bool bit) {
    (bp++).set(bit);
}

void obstream::setchar(char ch) {
    ibstream ibs(ch);
    for (int i = 0; i < 8; ++i) setbit(ibs.getbit());
}
