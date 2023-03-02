#include "library.h"
int main(){
    BF a("00000000000000010000000000000011");
    std::cout << a;
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
