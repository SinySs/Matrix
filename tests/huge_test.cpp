#include <iostream>
#include <fstream>

#include "../include/matrix.h"

int main()
{

    std::ifstream data("tests_data/huge_data.txt");
    std::ifstream answers("tests_data/huge_answers.txt");


    int n;
    data >> n;
    std::vector<double> elems = {};

    for(int i = 0; i < n * n; ++i) {
        double q;
        data >> q;

        elems.push_back(q);
    }

    matrix<double> matr(n, n, elems.begin(), elems.end());

    double answ, result;
    answers >> answ;
    result = matr.determenant();
    if(result - answ < PRECISION) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
        std::cout << "Result: " << result << std::endl;
        std::cout << "Answer: " << answ << std::endl;


    }


}
