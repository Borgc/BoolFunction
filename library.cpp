#include "library.h"

#include <iostream>


bool BF::is_exp_of_2(size_t n) const
{
    return ( n & (n - 1) ) == 0;
}
BF::BF(size_t _n, int value) {
    switch (value) {
        case 0://zero terminated function
            n = _n;
            if ((0x1 << _n) <= BASE_len) {
                f = new BASE[1]{};
                nw = 1;
            } else {
                nw = (0x1 << _n) / sizeof(BASE) + 1;
                f = new BASE[nw]{};
            }
            break;
        case 1://one terminated function
            n = _n;
            if ((0x1 << _n) <= BASE_len) {
                f = new BASE[1]{};
                f[0] = (0x1 << (0x1 << _n)) - 1;
                nw = 1;

            } else {
                nw = (0x1 << _n) / sizeof(BASE) + 1;
                f = new BASE[nw]{};
                for (size_t i = 0; i < nw; i++) {
                    f[i] = f[i] - 1;
                }
            }
            break;
        case 2://random terminated function
            n = _n;
            std::mt19937 gen((unsigned int) time(nullptr));
            gen.seed(std::time(nullptr));
            if ((0x1 << _n) < BASE_len) {
                f = new BASE[1];
                f[0] = gen() & (0x1 << (0x1 << _n)) - 1;;
                nw = 1;
            } else {
                nw = (0x1 << _n) / BASE_len;
                f = new BASE[nw];
                for (size_t i = 0; i < nw; i++) {
                    f[i] = gen();
                }

            }
            break;
    }
}
std::ostream & operator << (std::ostream & out, BF & fun){
    if(fun.f != nullptr){
        if((0x1 << fun.n) < BASE_len){
            std::string s;
            s = (std::bitset<BASE_len>(fun.f[0])).to_string();
            out << s.substr(s.length() - (0x1 << fun.n));
        } else {
            ssize_t i = ssize_t(fun.nw) - 1;
            do {
                out << std::bitset<BASE_len>(fun.f[i]);
                i--;
            } while (i >= 0);
        }
    }
    return out;
}
size_t BF::weight() const{
    size_t res = 0;
    for(size_t i = 0; i < nw; i++){
        size_t tmp = f[i];
        while(tmp){
            res++;
            tmp = tmp & (tmp - 1);
        }
    }
    return res;
}
BF & BF::operator = (const BF & fun){
    if(& fun != this){
        this->~BF();
        n = fun.n;
        nw = fun.nw;
        f = new BASE [nw];
        for(size_t i = 0; i < nw; i++){
            f[i] = fun.f[i];
        }
    }
    return *this;
}
