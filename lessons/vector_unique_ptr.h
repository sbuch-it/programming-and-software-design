#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <memory>

class Vector {
 private:
    typedef double Element;
    int length = 0;
    std::unique_ptr<Element[]> data;

 public:
    Vector();
    Vector(const int length_);
    Vector(const Vector& v);
    Vector& operator=(const Vector& right);

    inline int GetLength() const 
        return length;
    }
    inline Element& operator[](const int i) const {
        return data[i];
    }
    inline Element Get(const int i) {
        return data[i];
    }
    bool Set(const int i, const Element element);

    friend std::ostream& operator<<(std::ostream& out, const Vector& v);
    friend std::istream& operator>>(std::istream& in, Vector& v);
};  // End Vector

std::ostream& operator<<(std::ostream& out, const Vector& v);
std::istream& operator>>(std::istream& in, Vector& v);

#endif