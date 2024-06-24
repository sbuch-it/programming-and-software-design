#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

class Vector {
 private:
    typedef double Element;
    int length = 0;
    Element* data = nullptr;

    void Clear();

 public:
    Vector(); // default constructor
    Vector(const int length_); // constructor with parameters
    Vector(const Vector& v); // copy constructor
    Vector& operator=(const Vector& right); // operator=
    ~Vector(); // destructor

    // getter for length
    inline int GetLength() const {
        return length;
    }

    // operator[]
    inline Element& operator[](const int i) const {
        return data[i];
    }

    // getter for the i-th element
    inline Element Get(const int i) {
        return data[i];
    }

    // setter for the i-th element
    bool Set(const int i, const Element element);

    friend std::ostream& operator<<(
        std::ostream& out, const Vector& v);
    friend std::istream& operator>>(std::istream& in, Vector& v);
}; // end Vector

std::ostream& operator<<(std::ostream& out, const Vector& v);
std::istream& operator>>(std::istream& in, Vector& v);

#endif