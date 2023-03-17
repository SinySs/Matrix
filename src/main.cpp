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

    matrix<double> matr(n, n, elems.begin(), elems.end());

    std::cout << matr.determenant();

    return 0;
}
