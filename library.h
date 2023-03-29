#ifndef BF_LIBRARY_H
#define BF_LIBRARY_H
#define BASE_len (sizeof(BASE)*8)
#if defined (_MSC_VER)  // Visual studio
#define thread_local __declspec( thread )
#elif defined (__GCC__) // GCC
#define thread_local __thread
#endif
#include <string>
#include <iostream>
#include <bitset>
#include <ctime>
#include <random>
#include <thread>
typedef uint64_t BASE;
class BF{
private:
    size_t n;
    size_t nw;
    BASE *f;

public:
    BF(){f = new BASE[1] {}; n = 1; nw = 1;}
    BF(size_t n, int value);
    BF(BF & fun);
    bool operator == (const BF & fun) const;
    BF & operator = (const BF &fun);
    BF(const std::string& s);
    ~BF(){delete [] f; n = 0; nw = 0; f = nullptr;}
    friend std::ostream & operator << (std::ostream & out, BF & fun);
    static bool is_exp_of_2(size_t n) ;
    size_t weight() const;

    BF mobius();

    std::string ANF();
};
void hello();

#endif //BF_LIBRARY_H
