//
// Created by Дмитрий on 18.11.2022.
//
#pragma once
#include <iostream>

//template<typename T>

template<typename T>
class matrix {
    int n_col_ = 0, n_rows_ = 0;
    T* data = nullptr;

public:
    matrix(int col, int rows) : n_col_(col), n_rows_(rows) {};
    matrix() = default;

    void print() const {
        std::cout << "cols: " << n_col_<< " rows: " << n_rows_ << std::endl;
    }
};



