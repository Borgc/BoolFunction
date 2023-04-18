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
                nw = (one << _n) / BASE_len;
                f = new BASE[nw]{};
            }
            break;
        case 1://one terminated function
            n = _n;
            if ((one << _n) <= BASE_len) {
                f = new BASE[1]{};
                f[0] = -1;
                f[0] >> (one << n);
                nw = 1;

            } else {
                nw = (one << _n) / BASE_len;
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
    BASE m1 = 0xaaaaaaaaaaaaaaaa;
    BASE m2 = 0xcccccccccccccccc;
    BASE m3 = 0xf0f0f0f0f0f0f0f0;
    BASE m4 = 0xff00ff00ff00ff00;
    BASE m5 = 0xffff0000ffff0000;
    BASE m6 = 0xffffffff00000000;
    BF tmp = *this;
    switch (n) {
        case 0: return *this;
        case 1: tmp.f[0] ^= (tmp.f[0] & m1) >> 1;
            return *this;
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
        tmp.f[i] ^= (tmp.f[i] & m6) >> 32;
    }
    size_t range = 1;
    for(BASE l = 1; l <= steps; l++){
        BASE temp = 0;
        while(temp < ((size_t)1 << steps)){
            BASE next = temp + range;
            for(BASE q = 0; q < range; q++){
                tmp.f[next + q] = tmp.f[next + q] ^ tmp.f[temp + q];
            }
            temp += 2 * range;
        }
        range *= 2;
    }
    return tmp;
}

std::string BF::ANF(){ //use only with mobius vector
    std::string str;
    if(nw == 1){
        BASE mask = BASE(0x1) << ((0x1 << n) - 1);
        BASE mask2;
        if((f[0] & mask) != 0){
            str += "1 + ";
        } else {
            if(n == 0){
                str = "0 + ";
            }
        }
        mask = mask >> 1;
        std::string tmp;
        for(size_t i = 1; i < ((size_t)1 << n); i++){
            if((f[0] & mask) != 0){
                mask2 = 0x1;
                for(size_t j = 0; j < n; j++) {
                    tmp = ((i & mask2) ? "X" + std::to_string(n - j) + tmp: "" + tmp);
                    mask2 <<= 1;
                }
                str += tmp + " + ";
                tmp = "";
            }
            mask >>= 1;
        }
        if (!str.empty()) {
            str.resize(str.length() - 3);
        } else {
            return "0";
        }
        return str;
    } else {
        BASE mask = (BASE(0x0) - 0x1) ^ ((BASE(0x0) - 0x1) >> 1);
        BASE mask2;
        if((f[0] & mask) != 0){
            str = "1 + ";
        }
        mask >>= 1;
        std::string tmp;
            for(size_t i = 1; i < ((size_t)1 << n); i++){
                if((f[i/BASE_len] & mask) != 0){
                    mask2 = 0x1;
                    for(size_t j = 0; j <= n; j++) {
                        tmp = ((i & mask2) ? "X" + std::to_string(n - j) + tmp: "" + tmp);
                        mask2 <<= 1;
                    }
                    str += tmp + " + ";
                    tmp = "";
                }
                mask >>= 1;
                if(!mask){
                    mask = (BASE(0x0) - 0x1) ^ ((BASE(0x0) - 0x1) >> 1);
                }
            }
        if (!str.empty()) {
            str.resize(str.length() - 3);
        }
        return str;
    }
}



BASE BF::deg(BF mob) {
    BASE deg = 0;
    BASE tmp;
    BASE res = 0;
    if(mob.nw == 1) {
        BASE mask = BASE(0x1) << ((0x1 << mob.n) - 1);
        for (BASE i = 0; i < BASE(1) << mob.n; i++) {
            if (mob.f[0] & mask) {
                tmp = i;
                while (tmp != 0) {
                    res++;
                    tmp = tmp & (tmp - 1);
                }
                if (res > deg)deg = res;
                res = 0;
            }
            mask >>= 1;
        }
    } else {
        for (BASE k = 0; k < mob.nw; k++) {
            BASE mask = (BASE(0x0) - 0x1) ^ ((BASE(0x0) - 0x1) >> 1);
            for (BASE i = 0; i < BASE_len; i++) {
                if (mob.f[k] & mask) {
                    tmp = k * BASE_len + i;
                    while (tmp != 0) {
                        res++;
                        tmp = tmp & (tmp - 1);
                    }
                    if (res > deg)deg = res;
                    res = 0;
                }
                mask >>= 1;
            }
        }
    }
    return deg;
}

int32_t * BF::WHt(int32_t *mas) {//create "auto *mas = new int32_t [BASE(1) << a.get_n()];" before use
        BASE bound = (BASE(1) << n <= BASE_len)? 1 << n: BASE_len;
        for(size_t k = 0; k < this->nw; k++){
            BASE mask = (n <= BASE_len/8)? 1 << ((1 << n) -1): (BASE(0x0) - 0x1) ^ ((BASE(0x0) - 0x1) >> 1);
            for(BASE i = 0; i < bound; i++) {
                if(this->f[k] & mask){
                    mas[k * BASE_len + i] = -1;
                } else {
                    mas[k * BASE_len + i] =  1;
                }
                mask >>= 1;
            }
        }

        int64_t x;
        int64_t y;
        int64_t r = 1;
        for(BASE i = 0; i < n; i++, r <<= 1) {
            for(BASE k = 0; k < 1 << n; k += 2 * r) {
                for (BASE j = k; j < k + r; j ++) {
                    x = mas[j];
                    y = mas[j + r];
                    mas[j] = x + y;
                    mas[j + r] = x - y;
                }
            }
        }
        return mas;
}

size_t BF::get_n() const{
    return this->n;
}

size_t BF::cor(std::int32_t *mas) const{
    for(BASE w = 1; w < n; w++){
        //zakrevskiy
        size_t a = ((BASE(1) << w) -1) << (this->n - w);
        size_t b;
        size_t c;
        size_t tmp;
        size_t res = 0;
        size_t next = 0;
        do{
            if(mas[a] != 0){
                return w - 1;
            }
            b = (a + 1) & a;
            tmp = (b - 1) ^ a;
            while(tmp){
                res++;
                tmp = tmp & (tmp - 1);
            }
            c = res - 2;
            res = 0;
            next = (((((a + 1) ^ a) << 1) + 1) << c) ^ b;
            a = next;
        }while(a != (BASE(1) << w) -1);
    }
    if(mas[((BASE(1) << n) -1)] != 0){
        return n - 1;
    }
    return n;
}
