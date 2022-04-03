#pragma once

#include <vector>
#include <cassert>
#include <iostream>

template <typename T>
class Matrix {
    std::vector<std::vector<T>> content;
    size_t n, m;
    
public:
    Matrix() : content(), n(0), m(0) {};
    Matrix(const Matrix &) = default;
    Matrix(const size_t &n, const size_t &m) : content(std::vector<std::vector<T>>(n, std::vector<T>(m, T()))), n(n), m(m) {};
    Matrix(const std::vector<T> &v) : content(std::vector<std::vector<T>>(1, v)), n(1), m(v.size()) {};
    
    // Addition

    Matrix<T> & operator+=(const Matrix<T> &A) {
        assert(A.n == this->n);
        assert(A.m == this->m);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                content[i][j] += A[i][j]; 
        return *this;
    }
    
    friend Matrix<T> operator+(Matrix<T> A, const Matrix<T> &B) {
        return A += B;
    }

    // Subtraction

    Matrix<T> & operator-=(const Matrix<T> &A) {
        assert(A.n == n);
        assert(A.m == m);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                content[i][j] -= A[i][j];    
        return *this;
    }

    friend Matrix<T> operator-(Matrix<T> A, const Matrix<T> &B) {
        return A -= B;
    }

    // Multiplication

    friend Matrix<T> operator*(const Matrix<T> &A, const Matrix<T> &B) {
        assert(A.m == B.n);
        Matrix<T> C(A.n, B.m);

        for (size_t i = 0; i < C.n; ++i)
            for (size_t j = 0; j < C.m; ++j)
                for (size_t k = 0; k < A.m; ++k)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    friend Matrix<T> operator*(const T &c, const Matrix<T> &A) {
        Matrix<T> B(A);
        for (size_t i = 0; i < B.getN(); ++i)
            for (size_t j = 0; j < B.getM(); ++j)
                B[i][j] *= c;
        return B;
    }

    Matrix<T> & operator*=(const Matrix<T> &A) {
        *this = *this * A;
        return *this;
    }

    friend std::vector<T> operator*(const Matrix<T> &A, const std::vector<T> &b) {
        assert(A.m == b.size());
        std::vector<T> c(A.n, 0);

        for (size_t i = 0; i < A.n; ++i)
            for (size_t j = 0; j < A.m; ++j)
                c[i] += A[i][j] * b[j];
        return c;
    }

    // Element access

    std::vector<T> & operator[](const size_t &idx) {
        return content[idx];
    }

    const std::vector<T> & operator[](const size_t &idx) const {
        return content[idx];
    }

    // Transpose

    Matrix<T> transpose() const {
        Matrix<T> A(m, n);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                A[j][i] = content[i][j];
        return A;
    }

    Matrix<T> inverse() const {
        assert(n == m);

        Matrix<T> A(*this), B(n, n);
        for (size_t i = 0; i < n; ++i)
            B[i][i] = 1;

        for (size_t i = 0; i < n; ++i) {
            assert(A[i][i] != 0.0);
            for (size_t j = 0; j < n; ++j) {
                if (i != j) {
                    T ratio = A[j][i] / A[i][i];
                    for (size_t k = 0; k < n; ++k)
                        A[j][k] -= ratio * A[i][k];
                    for (size_t k = 0; k < n; ++k)
                        B[j][k] -= ratio * B[i][k];
                }
            }
        }

        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                B[i][j] /= A[i][i];
        
        return B;
    }

    // Add row

    void addRow(const std::vector<T> &v) {
        assert(n == 0 || v.size() == m);
        content.push_back(v);
        if (!n) m = v.size();
        ++n;
    }

    // Getters

    const size_t & getN() const { return n; }
    const size_t & getM() const { return m; }
};

template <typename T>
std::vector<T> operator*(const T &c, const std::vector<T> &v) {
    std::vector<T> res(v);
    for (T &i : res)
        i *= c;
    return res;
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
    assert(a.size() == b.size());
    std::vector<T> v(a);
    for (size_t i = 0; i < v.size(); ++i)
        v[i] += b[i];
    return v;
}

template <typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
    assert(a.size() == b.size());
    std::vector<T> v(a);
    for (size_t i = 0; i < v.size(); ++i)
        v[i] -= b[i];
    return v;
}

template <typename T>
Matrix<T> Id(const size_t &n) {
    Matrix<T> I(n, n);
    for (size_t i = 0; i < n; ++i)
        I[i][i] = 1;
    return I;
}