#include <vector>
#include <cassert>

template <typename T>
class Matrix {
    std::vector<std::vector<T>> content;
    size_t n, m;
    
public:
    Matrix() = default;
    Matrix(const Matrix &) = default;
    Matrix(const size_t &n, const size_t &m) : content(std::vector<std::vector<T>>(n, std::vector<T>(m, 0))), n(n), m(m) {};
    Matrix(const std::vector<T> &v) : content(std::vector<std::vector<T>>(1, v)), n(1), m(v.size()) {};
    
    // Addition

    Matrix<T> & operator+=(const Matrix<T> &A) {
        assert(A.n == this->n);
        assert(A.m == this->m);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                (*this)[i][j] += A[i][j];    
        return *this;
    }
    
    friend Matrix<T> operator+(const Matrix<T> &A, const Matrix<T> &B) {
        Matrix<T> C(A);
        return C += B;
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

    friend Matrix<T> operator-(const Matrix<T> &A, const Matrix<T> &B) {
        Matrix<T> C(A);
        return C -= B;
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