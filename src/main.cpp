#include <iostream>
#include "matrix.h"
#include <vector>

int main() {

    double aa[] = {1, 2, 3, 4};
    double bb[] = {1, 2, 3, 4, 5, 6, 7, 8,9};

    matrix<double> m(2, 2, aa);
    matrix<double> mm(3, 3, bb);

    matrix<double> mmm = mm;
    if(mmm == mm) {
        std::cout << "I'm work" << std::endl;
    }

    double  A = mmm[2][1];
    std::cout <<"A:" << A;

    int a = m[1][1];
    std::cout << a << std::endl;
    std::cout << m[1][1] << std::endl;

    m[1][1] = -9;
    std::cout << m[1][1] << std::endl;

    a = mm[3][3] + m[1][1];
    std::cout << a << std::endl;



    matrix<double> d(2, 2, aa);
    d.print();
    std::cout << "DET: " << d.determenant() << std::endl;




    return 0;
}
