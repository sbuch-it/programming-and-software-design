#include <iostream>
#include <fstream>

class Matrix {
 public:
    typedef double Element;

 private:
    int n = 0; // rows
    int m = 0; // columns

    // Element* data = nullptr; // Solution 1
    Element** data = nullptr;

    bool valid = false;

    void Init(const int n_, const int m_) {
        if (n_ <= 0 || m_ <= 0) {
            return;
        }
        n = n_;
        m = m_;

        // data = new Element[n*m]; // Solution 1
        data = new Element*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new Element[m]();
        }
        valid = true;
    }

    void Clear() {
        if (data != nullptr) {
            // delete[] data; // Solution 1
            for (int i = 0; i < n; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
        n = 0;
        m = 0;
        valid = false;
    }

    // copy constructor
    void CopyElements(const Matrix& matrix) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                data[i][j] = matrix.data[i][j];
            }
        }
    }

 public:
    // constructor with parameters
    inline Matrix(const int n_, const int m_) {
        Init(n_, m_);
    }

    // copy constructor
    Matrix(const Matrix& matrix) {
        Init(matrix.n, matrix.m);
        CopyElements(matrix);
    }

    // operator=
    Matrix& operator=(const Matrix& matrix) {
        if (this == &matrix)
            return *this;
        Clear();
        Init(matrix.n, matrix.m);
        CopyElements(matrix);
        return *this;
    }

    // destructor
    ~Matrix() {
        Clear();
    }

    // getter for valid
    inline bool GetValid() const {
        return valid;
    }

    // operator[] const
    inline const Element* operator[](const int i) const {
        return data[i];
    }

    // operator[] non-const
    inline Element* operator[](const int i) {
        return data[i];
    }

    // get an element
    inline Element Get(const int i, const int j) const {
        // return data[i * m + j]; // Solution 1
        return data[i][j];
    }
    inline bool GetSafe(
        const int i, const int j, Element* value) const {

        if (i < n && j < m) {
            *value = Get(i, j);
            return true;
        }
        return false;
    }

    // set an element
    inline void Set(const int i, const int j, const Element value) {
        // data[i * m + j] = value; // Solution 1
        data[i][j] = value;
    }

    // addition method
    inline void Add(const int i, const int j, const Element value) {
        // data[i][j] += value;
        Set(i, j, Get(i, j) + value);
    }

    // print method
    void Print() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << this->Get(i, j) << " ";
            }
        std::cout << std::endl;
        }
    }

    // sum method
    bool Sum(const Matrix& matrix) {
        if (!valid || !matrix.valid || 
            n != matrix.n || m != matrix.m) {
            return false;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // data[i][j] += matrix.data[i][j];
                Set(i, j, Get(i, j) + matrix.Get(i, j));
            }
        }
        return true;
    }

    // product method
    bool Prod(const Element alpha) {
        if (!valid) {
            return false;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // data[i][j] *= alpha;
                Set(i, j, Get(i, j) * alpha);
            }
        }
        return true;
    }

    static Matrix SumNonInPlace(const Matrix& m1, const Matrix& m2) {
        if (!m1.valid || !m2.valid || m1.n != m2.n || m1.m != m2.m) {
            return Matrix(0, 0);
            // Matrix m(0, 0); return m;
        }
        Matrix m3(m1.n, m1.m);
        for (int i = 0; i < m3.n; ++i) {
            for (int j = 0; j < m3.m; ++j) {
                const Element s = m1.Get(i, j) + m2.Get(i, j);
                m3.Set(i, j, s);
            }
        }
        return m3;
    }

    // getters for rows and columns
    inline int GetN() const {
        return n;
    }
    inline int GetM() const {
        return m;
    }

    /*
    friend Matrix& operator++(Matrix& matrix);

    Matrix& operator++() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // data[i][j]++;
                this->Set(i, j, this->Get(i, j) + 1.0);
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& right) {
        if (GetN() != right.GetN() || GetM() != right.GetM()) {
            return Matrix(0, 0);
        }

        Matrix res(GetN(), GetM());
        for (int i = 0; i < GetN(); ++i) {
            for (int j = 0; j < GetM(); ++j) {
                res.Set(i, j, Get(i, j) + right.Get(i, j));
            }
        }
        return res;
    }
    */

    friend Matrix& operator+=(Matrix& left, const Matrix& right);
    friend std::istream& operator>>(
        std::istream& in, Matrix& matrix);

}; // end Matrix


// operator<<
std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {

    out << matrix.GetN() << " " << matrix.GetM() << std::endl;

    for (int i = 0; i < matrix.GetN(); ++i) {
        for (int j = 0; j < matrix.GetM(); ++j) {
            out << matrix.Get(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}

// operator>>
std::istream& operator>>(std::istream& in, Matrix& matrix) {

    matrix.Clear();
    int N = 0;
    int M = 0;
    in >> N >> M;
    matrix.Init(N, M);

    for (int i = 0; i < matrix.GetN(); ++i) {
        for (int j = 0; j < matrix.GetM(); ++j) {

            // Option 1
            in >> matrix[i][j];

            // Option 2
            // Matrix::Element number;
            // in >> number;
            // matrix.Set(i, j, number);

            // Option 3
            // in >> matrix.data[i][j];
        }
    }
    return in;
}

// operator++
Matrix& operator++(Matrix& matrix) {
    for (int i = 0; i < matrix.GetN(); ++i) {
        for (int j = 0; j < matrix.GetM(); ++j) {
            // data[i][j]++;
            matrix.Set(i, j, matrix.Get(i, j) + 1.0);
        }
    }
    return matrix;
}

// operator+
Matrix operator+(const Matrix& left, const Matrix& right) {
    // return Matrix::SumNotInPlace(left, right);

    if (!left.GetValid() || !right.GetValid() || 
        left.GetN() != right.GetN() || left.GetM() != right.GetM()) {
        return Matrix(0, 0);
    }

    Matrix res(left.GetN(), left.GetM());

    for (int i = 0; i < left.GetN(); ++i) {
        for (int j = 0; j < left.GetM(); ++j) {
            // res.data[i][j] = left.data[i][j] + right.data[i][j];
            res.Set(i, j, left.Get(i, j) + right.Get(i, j));
        }
    }
    return res;
}

//operator*
Matrix operator*(const Matrix& left, const Matrix& right) {
    if (!left.GetValid() || !right.GetValid() ||
        left.GetM() != right.GetN()) {
        return Matrix(0, 0);
    }

    Matrix res(left.GetN(), right.GetM()); // O(n^3)

    for (int i = 0; i < res.GetN(); ++i) {
        for (int j = 0; j < res.GetM(); ++j) {
            // res.Set(i, j, 0.0); // already done by constructor
            for (int k = 0; k < left.GetM(); ++k) {
                // res.data[i][j] += left.data[i][k] * right.data[k][j];
                res.Add(i, j, left.Get(i, k) * right.Get(k, j));
            }
        }
    }
    return res;
}

/* Matrix operator* con friendship
Matrix operator*(const Matrix& left, const Matrix& right) {

    if (!left.valid || !right.valid || left.m != right.n) {
        return Matrix(0, 0);
    }

    Matrix res(left.n, right.m);

    for (int i = 0; i < res.n; ++i) {
        for (int j = 0; j < res.m; ++j) {
            for (int k = 0; k < left.m; ++k) {
                res.data[i][j] += 
                    left.data[i][k] * right.data[k][j];
            }
        }
    }
    return res;
}
*/

// operator+=
Matrix& operator+=(Matrix& left, const Matrix& right) {
    if (!left.GetValid() || !right.GetValid() || 
        left.GetN() != right.GetN() || left.GetM() != right.GetM()) {
        left.valid = false;
        return left;
    }

    for (int i = 0; i < left.GetN(); ++i) {
        for (int j = 0; j < left.GetM(); ++j) {
            left.Set(i, j, left.Get(i, j) + right.Get(i, j));
        }
    }
    return left;
}

// operator==
bool operator==(const Matrix& left, const Matrix& right) {
    if (!left.GetValid() || !right.GetValid() ||
        left.GetN() != right.GetN() || left.GetM() != right.GetM()) {
        return false;
    }

    for (int i = 0; i < left.GetN(); ++i) {
        for (int j = 0; j < left.GetM(); ++j) {
            if (left.Get(i, j) != right.Get(i, j)) {
                return false;
            }
        }
    }
    return true;
}

// operator*=
Matrix& operator*=(Matrix& left, const Matrix::Element right) {
    if (left.GetValid()) {
        for (int i = 0; i < left.GetN(); ++i) {
            for (int j = 0; j < left.GetM(); ++j) {
                left.Set(i, j, left.Get(i, j) * right);
            }
        }
    }
    return left;
}


int main() {

    Matrix m1(3, 3);
    m1.Set(1, 1, 5.0);
    std::cout << "Print m1\n";
    m1.Print();

    Matrix m2(m1);
    std::cout << "Print m2\n";
    m2.Print();

    m2 *= 0.3;
    std::cout << "Print m2 after *= scalar\n";
    m2.Print();

    if (m1 == m2) {
        std::cout << "m1 is equal to m2\n";
    } else {
        std::cout << "m1 differs from m2\n";
    }

    m1.Sum(m2);
    std::cout << "Print m1 after Sum\n";
    m1.Print();

    const Matrix m3 = Matrix::SumNonInPlace(m1, m2);
    std::cout << "Print m3 after SumNonInPlace\n";
    if (m3.GetValid()) {
        m3.Print();
    } else {
        std::cerr << "m3 is not valid!\n";
    }

    m1.Prod(0.33f);
    std::cout << "Print m1 after Prod\n";
    m1.Print();

    ++m1;
    std::cout << "Print m1 after operator++\n";
    m1.Print();

    Matrix::Element value = 0.0f;
    if (m1.GetSafe(1, 1, &value)) {
        std::cout << "Element is " << value << std::endl;
    } else {
        std::cout << "Not valid index\n";
    }

    const Matrix m4 = m1 + m2;
    std::cout << "Print m4 after operator+\n";
    if (m4.GetValid()) {
        m4.Print();
    } else {
        std::cerr << "Can not perform m1+m2\n";
    }

    m1 += m2;
    std::cout << "Print m1 after operator+=\n";
    if (m1.GetValid()) {
        m1.Print();
    } else {
        std::cerr << "Can not perform m1+=m2\n";
    }

    const Matrix m5 = m1 * m2;
    std::cout << "Print m5 after operator*\n";
    if (m5.GetValid()) {
        // m5.Print();
        std::cout << m5;
    } else {
        std::cerr << "Can not perform m1*m2\n";
    }
    std::cout << "Element 2,2 of m5 is " << m5[2][2] << std::endl;

    Matrix m6(3,3);
    m6 = m1;
    std::cout << "Print m6 after operator= " << m6;
    std::ofstream of("matrix.dat");
    if (of.good()) {
        of << m6;
    }
    of.close();

    // from terminal the file is displayed with the command
    // cat matrix.dat
    std::ifstream ifs("matrix.dat");
    if (ifs.good()) {
        ifs >> m2;
    }
    std::cout << "Print m2 after operator>> " << m2;

    return 0;
}