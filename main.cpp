#include "library.h"
int main(){
    //BF a("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
    //std::cout << a << '\n';
    //BF a("01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
    //BF a("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    BF a("01001011");//11000000 baa //10111110 cor
    //BF a("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    BF b = (a.mobius());
    std::cout << "MT = " << b << '\n';
    std::cout << "ANF = " <<  b.ANF() << '\n';
    std::cout << "deg = " << BF::deg(b) << '\n';



    auto *mas = new int32_t [BASE(1) << a.get_n()];
    mas = a.WHt(mas);
    std::cout << "WHt = ";
    for(size_t i = 0; i < BASE(1) << a.get_n(); i++){
        std::cout << mas[i] << ' ';
    }
    std::cout << '\n' << "cor(f) = " << a.cor(mas) << '\n';
    std::cout << "Nf = " << a.Nf(mas) << '\n';
    std::cout << "Best affine approximation:\n";
    a.best_affine_approximation(mas);
    mas = a.autocor(mas);
    std::cout << "Autocorrelation vector = ";
    for(size_t i = 0; i < BASE(1) << a.get_n(); i++){
        std::cout << mas[i] << ' ';
    }
    std::cout << "\n" << "Propagation Critetion degree = " << a.PropCrit(mas) << "\n";
    std::cout << "CNf = " << a.CNf(mas) << "\n";
    BASE * TheoremMatrix = new BASE [a.weight()];
    TheoremMatrix = a.AImatrix(TheoremMatrix);
    for(int j = 0; j < a.weight(); j++){//(fun.get_n() - 1)/2 + 1
        //if(fun.f[0] && (0x1 << j)) {
        std::cout << std::bitset<8>(TheoremMatrix[j]) << '\n';
        //}
    }
    delete [] TheoremMatrix;
    delete [] mas;
//aaa
    //zakr();


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
