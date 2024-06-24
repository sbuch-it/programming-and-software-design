#include <iostream>

class Vector {
 private:
    int length = 0; // vector length
    float* data = nullptr;
    // pointer to the first element of the vector which is
    // initially null since we use dynamic memory allocation

 public:
    // Constructor with parameters that creates
    // length dimension vector with all values equal to 0.0f
    Vector(const int length_) {
        length = length_;
        data = new float[length]();
    }

    // Copy Constructor must be defined otherwise the pointer of v
    // is copied and the two vectors would point to the same date
    Vector(const Vector& v) {
        length = v.length;
        data = new float[length];
        for (int i = 0; i < length; ++i) {
            data[i] = v.data[i];
        }
    }

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Getter to return the i-th character
    float Get(const int i) const {
        if (!Good(i)) {
            return ' ';
        }

        return data[i];
    }

    // Setter to change a value in the i-th position with a new
    bool Set(const int i, const float element) {
        if (!Good(i)) {
            return false;
        }

        data[i] = element;
        return true;
    }

    bool Good(const int i) const {
        if (i < 0 || i >= length) {
            std::cerr << "Writing element not valid at pos " << i;
            std::cerr << std::endl;
            return false;
        }
        return true;
    }

    void Print() const {
        for (int i = 0; i < length; ++i) {
            std::cout << data[i] << std::endl;
        }
    }
};

int main() {
    Vector v1(4);
    v1.Set(0, 0.1);
    v1.Set(1, 0.23);
    v1.Set(2, 0.1);
    v1.Set(3, 2.1);
    std::cout << "Vector 1" << std::endl;
    v1.Print();

    Vector v2(v1);
    std::cout << "Vector 2" << std::endl;
    v2.Print();
    
    return 0;
}