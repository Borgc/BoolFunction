#ifndef BF_LIBRARY_H
#define BF_LIBRARY_H
#define BASE_len (sizeof(BASE)*8)
#include <string>
#include <iostream>
#include <bitset>
#include <ctime>
#include <random>
typedef uint16_t BASE;
class BF{
private:
    size_t n;
    size_t nw;
    BASE *f;

public:
    BF(){f = new BASE[1] {}; n = 1; nw = 1;}
    BF(size_t n, int value);
    //BF(const char *s);
    BF & operator = (const BF &fun);
    //BF(std::string s);
    //BF(const BF & fun);
    ~BF(){delete [] f; n = 0; nw = 0; f = nullptr;}
    friend std::ostream & operator << (std::ostream & out, BF & fun);
    bool is_exp_of_2(size_t n) const;
    size_t weight() const;
};
void hello();

#endif //BF_LIBRARY_H
