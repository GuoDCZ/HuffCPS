#ifndef HUFFCPS_BSTREAM_H
#define HUFFCPS_BSTREAM_H

#include <cstring>
#include <string>

typedef std::string::iterator str_it;
typedef std::string::const_iterator const_str_it;

class bptr {
 public:
    str_it it;
    int o;
 public:
    bptr(str_it it, int o = 0);
    bool operator==(const_str_it it_) const;
    bool operator!=(const_str_it it_) const;
    bool get() const;
    void set(bool bit) const;
    bptr operator+(int i) const;
    bptr operator-(int i) const;
    bptr &operator++();
    bptr &operator--();
    bptr operator++(int);
    bptr operator--(int);
};

class bstream {
 protected:
 public:
    std::string str;
    bptr bp;
    bstream(std::string str);
    bstream();
    bool good() const;
};

class ibstream : public bstream {
 public:
    ibstream(const std::string &str);
    ibstream(const char str[]);
    ibstream(const char &ch);
    void write(bool *p, int size = 1);
    void write(char *p, int size = 1);
    bool getbit();
    char getchar();
};

class obstream : public bstream {
 public:
    obstream();
    const std::string &getstr() const;
    void read(const bool *p, int size = 1);
    void read(const char *p, int size = 1);
    void setbit(bool bit);
    void setchar(char ch);
};

#endif