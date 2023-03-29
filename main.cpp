#include "library.h"
int main(){
    BF a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BF b = (a.mobius());
    std::cout << b << '\n';
    std::cout << b.ANF();
//    BF zero1(3, 0);
//    BF zero("00000000");
//    std::cout << (zero1 == zero);

//    BF a;
//    for(size_t i = 2; i < 32; i++){
//        a = BF(i, 2);
//        std::cout << i << std::endl;
//        //std::cout << a << ' ';
//        std::cout << double(a.weight())/(size_t(0x1) << i) << '\n';
//    }
    return 0;
}
