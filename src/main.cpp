#include <iostream>
#include "matrix.h"

int main(int argc, char **argv)
{
    int n;
    std::cin >> n;
    assert(std::cin.good());

    std::vector<double> elems;

    for(int i = 0; i < n * n; ++i) {
        double q;
        std::cin >> q;
        assert(std::cin.good());

        elems.push_back(q);
    }

    try {
        matrix<double> matr(n, n, elems.begin(), elems.end());

        std::cout << matr.determenant() << std::endl;
    } catch (matrix_exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
