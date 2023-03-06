//
// Created by Дмитрий on 18.11.2022.
//
#pragma once
#include <iostream>
#include <cassert>


template<typename T>
class matrix {
    int n_cols_ = 0, n_rows_ = 0;
    T* data_ = nullptr;

    struct proxy_row {
        T* p_row;

        T& operator [](int col){
            return p_row[col - 1];
        }
        const T& operator [](int col) const{
            return p_row[col - 1];
        }
    };


public:
    matrix() = default;
    matrix(int col, int rows) : n_cols_(col), n_rows_(rows) { data_ = new T[col*rows]; };
    matrix(int col, int rows, const T* data);
    matrix(const matrix<T> &rhs);

    int get_rows() const {return n_rows_; };
    int get_cols() const {return n_cols_; };

    void print() const;

    proxy_row operator[](int row) const {
        return proxy_row{ data_ + (row - 1) * n_cols_ };
    }
};

template<typename T>
matrix<T>::matrix(int col, int rows, const T *data): matrix(col, rows) {
    int num_of_elem = col * rows;
    data_ = new T[num_of_elem];

    for(int i = 0; i < num_of_elem; ++i) {
        data_[i] = data[i];
    }

}

template<typename T>
matrix<T>::matrix(const matrix<T> &rhs): matrix(rhs.get_rows(),rhs.get_rows()) {
    for(int i = 0; i < n_rows_; ++i) {
        for(int j = 0; j < n_cols_; ++j) {
            data_[i * n_cols_ + j] = rhs[i + 1][j + 1];
        }
    }
}

template<typename T>
void matrix<T>::print() const {
    std::cout << "cols: " << n_cols_<< " rows: " << n_rows_ << std::endl;
    for(int i = 0; i < n_rows_; ++i) {
        for(int j = 0; j < n_cols_; ++j) {
            std::cout << data_[i * n_cols_ + j] << ' ';
        }
        std::cout << std::endl;
    }

}




