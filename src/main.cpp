#include <iostream>
#include "matrix.h"
#include <vector>

int main() {

    double aa[] = {1, 2, 3, 4};
    double bb[] = {1, 2, 3, 4, 5, 6, 7, 8,9};

    matrix<double> m(2, 2, aa);
    matrix<double> mm(3, 3, bb);


    matrix<double> d(2, 2, aa);


    std::cout << "DET: " << d.determenant() << std::endl;





    return 0;
}
