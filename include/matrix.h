#pragma once
#include <iostream>
#include <cassert>
#include <vector>

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
    matrix(int col, int rows, T data = T{});
    matrix(int col, int rows, const T *data);

    template<typename Iter>
    matrix(int cols, int rows, Iter begin, Iter end);

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
std::pair<matrix<T>, matrix<T>> lu_decomposition(matrix<T> &matr)
{
    if(matr.get_cols() != matr.get_rows()) {
        assert("Number of rows != number of cols");
    }
    int n = matr.get_cols();

    matrix<T> L(n, n);
    matrix<T> U(n, n);

    for(int i = 1; i < n+1; ++i) {
        for(int j = 1; j < n+1; ++j) {
            if(i < j) {

                double sum = 0.0;
                for(int k = 1; k < i+1; ++k)
                    sum += L[i][k] * U[k][j];

                U[i][j] = (matr[i][j] - sum) / L[i][i];

            } else if(i == j) {

                double sum = 0.0;
                for(int k = 1; k < j+1; ++k)
                    sum += L[i][k] * U[k][j];

                L[j][j] = 1.0;
                U[j][j] = matr[j][j] - sum;

            } else {
                double sum = 0.0;
                for(int k = 1; k < j+1; k++)
                    sum += L[i][k] * U[k][j];

                L[i][j] = (matr[i][j] - sum) / U[j][j];

            }
        }
    }

    return std::make_pair(L, U);
}

template<typename T>
int reorder(matrix<T>& matrix, int row, int col) {
    int n = matrix.get_rows();
    if (matrix[row][col] != 0) {
        return 0;
    }

    for (int i = row + 1; i < n + 1; ++i) {
        if (matrix[i][col] != 0) {
            for (int j = 1; j < n + 1; ++j) {
                std::swap(matrix[row][j], matrix[i][j]);
            }
            return i - row;
        }
    }
    // zero col -> det = 0
    return -1;
}

template<typename T>
int remove_diagonal_zeros(matrix<T>& matrix) {

    int n = matrix.get_rows();
    int reorders_n = 0;

    for (int current_col = 1; current_col < n; ++current_col) {

        int degenerate = reorder(matrix, current_col, current_col);
        if(degenerate == -1 )
            return -1;
        reorders_n += degenerate;

    }
    return reorders_n;

}

template<typename T>
T matrix<T>::determenant() {

    int coef = remove_diagonal_zeros(*this);
    auto LU  = lu_decomposition(*this);

    matrix<T> L = LU.first;
    matrix<T> U = LU.second;

    T determ = -1.0;
    if(coef % 2 == 0) {
         determ = 1.0;
    }

    for(int i = 1; i < this->n_cols_ + 1; ++i) {
        determ *= U[i][i];
    }

    return determ;
}

template<typename T>
matrix<T>::matrix(int col, int rows, T data): n_cols_(col), n_rows_(rows) {
    data_ = new T[col * rows];
    for(int i = 0; i < rows * col; ++i) {
        data_[i] = data;
    }
}

template<typename T>
template<typename Iter>
matrix<T>::matrix(int cols, int rows, Iter begin, Iter end): matrix(cols, rows) {
    int size = std::distance(begin, end);

    assert(rows * cols == size);

    for(int i = 0; i < size; ++i) {
            data_[i] = *begin;
            begin++;
    }


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


