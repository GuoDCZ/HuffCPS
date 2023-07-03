#ifndef HUFFCPS_BSTREAM_H
#define HUFFCPS_BSTREAM_H

#include <cstring>
#include <string>

class bstream {
    std::string bitstr;
    std::size_t index = 0;

 public:
    inline void get(bool &bit);
    inline void get(char &ch);
    inline void get(char str[]);
    inline void get(std::string &str);

    inline bool good();

    inline void set(bool bit);
    inline void set(char ch);
    inline void set(const char str[]);
    inline void set(const std::string &str);
};

class ibstream : protected bstream {

 public:
    ibstream();
    ibstream(bool bit);
    ibstream(char ch);
    ibstream(const std::string &str);
    ibstream(const char str[]);

    bool good();

    void read(bool *p, std::size_t s = 1);
    void read(char *p, std::size_t s = 1);
    void read(std::string &str);

    ibstream &operator>>(bool &bit);
    ibstream &operator>>(char &ch);
    ibstream &operator>>(char str[]);
    ibstream &operator>>(std::string &str);
};

class obstream : protected bstream {

 public:
    std::string str();

    void write(const bool *p, std::size_t s = 1);
    void write(const char *p, std::size_t s = 1);
    void write(const std::string &str);

    obstream &operator<<(bool bit);
    obstream &operator<<(char ch);
    obstream &operator<<(const std::string &str);
    obstream &operator<<(const char str[]);

};

#endif