//
// Created by Дмитрий on 18.11.2022.
//
#pragma once
#include <iostream>
#include <cassert>

#define PRECISION 1e-4

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
    matrix(int col, int rows) : n_cols_(col), n_rows_(rows) { data_ = new T[col * rows]; };
    matrix(int col, int rows, const T *data);

    ~matrix() {
        delete data_;
        n_cols_ = -1;
        n_rows_ = -1;
    }

    matrix(const matrix<T> &rhs);
    matrix(matrix &&rhs) = default;

    matrix<T> &operator=(const matrix &rhs);
    matrix<T> &operator*=(const int n);
    matrix<T> &operator+=(const matrix &rhs);
    matrix<T> &operator-=(const matrix &rhs);

    int get_rows() const {return n_rows_; };
    int get_cols() const {return n_cols_; };

    T determenant();
    void transpose();
    void print() const;

    proxy_row operator[](int row) const {
        return proxy_row{ data_ + (row - 1) * n_cols_ };
    }
};

template<typename T>
matrix<T>::matrix(int col, int rows, const T* data): matrix(col, rows) {
    int num_of_elem = col * rows;

    for(int i = 0; i < num_of_elem; ++i) {
        data_[i] = data[i];
    }

}

template<typename T>
matrix<T>::matrix(const matrix<T> &rhs): matrix(rhs.get_rows(),rhs.get_rows()) {
    //assert(n_cols_ >= 0 || n_rows_ >= 0);
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

template<typename T>
matrix<T> &matrix<T>::operator=(const matrix &rhs) {
    if(this == &rhs)
        return *this;

    n_cols_ = rhs.get_cols();
    n_rows_ = rhs.get_rows();
    data_ = new T[n_cols_ * n_rows_];

    for(int i = 0; i < n_rows_; ++i) {
        for(int j = 0; j < n_cols_; ++j) {
            data_[i * n_cols_ + j] = rhs[i + 1][j + 1];
        }
    }

    return *this;
}

template<typename T>
matrix<T> &matrix<T>::operator*=(const int n) {
    for(int i = 0; i < n_rows_; ++i) {
        for(int j = 0; j < n_cols_; ++j) {
            data_[i * n_cols_ + j] *= n;
        }
    }
    return *this;
}

template<typename T>
matrix<T> &matrix<T>::operator+=(const matrix &rhs) {
    for(int i = 0; i < n_rows_; ++i) {
        for(int j = 0; j < n_cols_; ++j) {
            data_[i * n_cols_ + j] += rhs[i + 1][j + 1];
        }
    }

    return *this;
}

template<typename T>
matrix<T> &matrix<T>::operator-=(const matrix &rhs) {
    for(int i = 0; i < n_rows_; ++i) {
        for(int j = 0; j < n_cols_; ++j) {
            data_[i * n_cols_ + j] -= rhs[i + 1][j + 1];
        }
    }
    return *this;
}


template<typename T>
void matrix<T>::transpose() {
    int n = 0;

    for(int i = 0; i < n_rows_; ++i) {
        for(int j = n; j < n_cols_; ++j) {
            std::swap(data_[i * n_cols_ + j], data_[j * n_cols_ + i]);
        }
        n++;
    }


}

template<typename T>
T matrix<T>::determenant() {
    if(n_cols_ == 2 && n_rows_ == 2)
        return data_[0] * data_[3] - data_[1] * data_[2];

    return 0;
}

template<typename T>
bool operator==(const matrix<T> &lhs, const matrix<T> &rhs)
{
    int l_rows = lhs.get_rows();
    int r_rows = rhs.get_rows();
    int l_cols = lhs.get_cols();
    int r_cols = rhs.get_cols();

    if(l_cols != r_cols || l_rows != r_rows) {
        return false;
    }

    for(int i = 0; i < l_rows; ++i) {
        for(int j = 0; j < l_cols; ++j) {
            if (std::abs(lhs[i + 1][j + 1] - rhs[i + 1][j + 1]) > PRECISION) {
                return false;
            }
        }
    }

    return true;
}


