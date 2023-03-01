#include "library.h"
int main(){
    BF a;
    for(size_t i = 2; i < 32; i++){
        a = BF(i, 2);
        std::cout << i << ' ';
        //std::cout << a << ' ';
        std::cout << double(a.weight())/ double(0x1 << i) << '\n';
        a.~BF();
    }
    return 0;
}
