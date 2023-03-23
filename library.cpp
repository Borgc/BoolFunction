#include "library.h"

#include <iostream>


bool BF::is_exp_of_2(size_t n)
{
    return ( n & (n - 1) ) == 0;
}
size_t Rand(const size_t & min, const size_t & max) {
    static thread_local std::mt19937* generator = nullptr;
    if (!generator) generator = new std::mt19937(clock());
    std::uniform_int_distribution<size_t> distribution(min, max);
    return distribution(*generator);
}
BF::BF(size_t _n, int value) {
    BASE one = 1;
    switch (value) {
        case 0://zero terminated function
            n = _n;
            if ((one << _n) <= BASE_len) {
                f = new BASE[1]{};
                nw = 1;
            } else {
                nw = (one << _n) / sizeof(BASE) + 1;
                f = new BASE[nw]{};
            }
            break;
        case 1://one terminated function
            n = _n;
            if ((one << _n) <= BASE_len) {
                f = new BASE[1]{};
                f[0] = (one << (one << _n)) - 1;
                nw = 1;

            } else {
                nw = (one << _n) / sizeof(BASE) + 1;
                f = new BASE[nw]{};
                for (size_t i = 0; i < nw; i++) {
                    f[i] = - 1;
                }
            }
            break;
        case 2://random terminated function
            n = _n;
            if ((one << _n) < BASE_len) {
                f = new BASE[1];

                f[0] = Rand(0, BASE(0x0) - 1) & (one << (one << _n)) - one;;
                nw = 1;
            } else {
                nw = 0x1;
                nw = nw << _n;
                nw = nw / BASE_len;
                f = new BASE[nw];
                for (size_t i = 0; i < nw; i++) {
                    f[i] = Rand(0, BASE(0x0) - 1);
                }

            }
            break;
    }
}
std::ostream & operator << (std::ostream & out, BF & fun){
    BASE one = 1;
    if(fun.f != nullptr){
        if((one << fun.n) < BASE_len){
            std::string s;
            s = (std::bitset<BASE_len>(fun.f[0])).to_string();
            out << s.substr(s.length() - (one << fun.n));
        } else {
            for(size_t i = 0; i < fun.nw; i++){
                out << std::bitset<BASE_len>(fun.f[i]);
            }
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

BF::BF(const std::string& s) {
    if(!is_exp_of_2(s.length())){
        n = 0;
        nw = 0;
        f = nullptr;
    } else {
        auto tmp = size_t(s.length());
        n = 0;
        nw = (tmp + BASE_len - 1) / BASE_len;
        while(tmp){
            n++;
            tmp = tmp >> 1;
        }
        n -=1;
        if(s.length() < BASE_len){
            std::bitset<BASE_len> bits(s);
            f = new BASE[1];
            f[0] = bits.to_ullong();
        } else {
            f = new BASE[nw];
            for(size_t i = 0; i < nw; i++){
                std::bitset<BASE_len> bits(s.substr(i * BASE_len, (i+1)*BASE_len));
                f[i] = bits.to_ullong();
            }
        }
    }
}

BF::BF(BF &fun) {
    n = fun.n;
    nw = fun.nw;
    f = new BASE[nw];
    for(size_t i = 0; i < nw; i++){
        f[i] = fun.f[i];
    }
}

bool BF::operator==(const BF &fun) const {
    if(fun.n != this->n)return false;
    if(fun.nw != this->nw)return false;
    for(size_t i = 0; i < nw; i++){
        if(fun.f[i] != this->f[i])return false;
    }
    return true;
}
BF BF::mobius(){
    BASE m1 = 0xaaaaaaaa;
    BASE m2 = 0xcccccccc;
    BASE m3 = 0xf0f0f0f0;
    BASE m4 = 0xff00ff00;
    BASE m5 = 0xffff0000;
    BF tmp = *this;
    switch (n) {
        case 0: return {};
        case 1: return *this;
        case 2: tmp.f[0] ^= (tmp.f[0] & m1) >> 1;
                tmp.f[0] ^= (tmp.f[0] & m2) >> 2;
            return tmp;
        case 3: tmp.f[0] ^= (tmp.f[0] & m1) >> 1;
                tmp.f[0] ^= (tmp.f[0] & m2) >> 2;
                tmp.f[0] ^= (tmp.f[0] & m3) >> 4;
            return tmp;
        case 4: tmp.f[0] ^= (tmp.f[0] & m1) >> 1;
            tmp.f[0] ^= (tmp.f[0] & m2) >> 2;
            tmp.f[0] ^= (tmp.f[0] & m3) >> 4;
            tmp.f[0] ^= (tmp.f[0] & m4) >> 8;
            return tmp;
        case 5: tmp.f[0] ^= (tmp.f[0] & m1) >> 1;
            tmp.f[0] ^= (tmp.f[0] & m2) >> 2;
            tmp.f[0] ^= (tmp.f[0] & m3) >> 4;
            tmp.f[0] ^= (tmp.f[0] & m4) >> 8;
            tmp.f[0] ^= (tmp.f[0] & m5) >> 16;
            return tmp;
    }
    size_t steps = n - 6;
    for(size_t i = 0; i < ((size_t)1 << steps); i++){
        tmp.f[i] ^= (tmp.f[i] & m1) >> 1;
        tmp.f[i] ^= (tmp.f[i] & m2) >> 2;
        tmp.f[i] ^= (tmp.f[i] & m3) >> 4;
        tmp.f[i] ^= (tmp.f[i] & m4) >> 8;
        tmp.f[i] ^= (tmp.f[i] & m5) >> 16;
    }
    return tmp;
}



