#include <iostream>

class Matrix {
 private:
    int n = 0; // number of rows
    int m = 0; // number of columns

    // float* data = nullptr; // Solution 1
    float** data = nullptr; // Solution 2

    bool valid = false;

    // method that initializes the array
    void Init(const int n_, const int m_) {
        if (n_ <= 0 || m_ <= 0) {
            return;
        }
        n = n_;
        m = m_;

        // data = new float[n * m]; // Solution 1
        data = new float*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new float[m]();
        }
        valid = true;
    }

 public:
    // Constructor
    Matrix(const int n_, const int m_) {
        Init(n_, m_);
    }

    // Copy Constructor
    Matrix(const Matrix& matrix) {
        Init(matrix.n, matrix.m);
        // Solution 1
        /*
        for (int i = 0; i < n * m; ++i)
            data[i] = matrix.data[i];
        */
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                data[i][j] = matrix.data[i][j];
            }
        }
    }

    // Destructor
    ~Matrix() {
        if (data == nullptr) {
            return;
        }

        // delete[] data; // Solution 1
        for (int i = 0; i < n; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Getter to read an array value
    float Get(const int i, const int j) const {
        // return data[i * m + j]; // Solution 1
        return data[i][j];
    }

    bool GetSafe(const int i, const int j, float* value) const {
        if (i < n && j < m) {
            *value = Get(i, j);
            return true;
        }
        return false;
    }

    // Setter to modify an array value
    void Set(const int i, const int j, const float value) {
        // data[i * m + j] = value; // Solution 1
        data[i][j] = value;
    }

    // Method for printing the matrix
    void Print() const {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cout << Get(i, j) << " ";
            }
            std::cout << std::endl;
        }
        // equivalent for both solutions
    }

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

    // Method for the product between two matrices
    bool Prod(const float alpha) {
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
};

int main() {
    Matrix m1(3, 3);
    m1.Set(1, 1, 5.0);
    std::cout << "Print m1" << std::endl;
    m1.Print();

    Matrix m2(m1);
    std::cout << "Print m2" << std::endl;
    m2.Print();

    m1.Sum(m2);
    std::cout << "Print m1 after Sum" << std::endl;
    m1.Print();

    m1.Prod(0.33f);
    std::cout << "Print m1 after Prod" << std::endl;
    m1.Print();

    float value = 0.0f;
    if (m1.GetSafe(1, 1, &value)) {
        std::cout << "Element is " << value << std::endl;
    } else {
        std::cout << "Not valid index" << std::endl;
    }
    return 0;
}