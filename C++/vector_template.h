#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

template <typename Element>
class Vector {
 private:
    int length = 0;
    Element* data = nullptr;

    void Clear();

 public:
    Vector();
    Vector(const int length_);
    Vector(const Vector& v);
    Vector& operator=(const Vector& right);
    ~Vector();

    inline int GetLength() const { 
        return length;
    }
    inline Element& operator[](const int i) const {
        return data[i];
    }
    inline Element Get(const int i) {
        return data[i];
    }
    bool Set(const int i, const Element element);
}; // end Vector


// implementation with template
template <typename Element>
void Vector<Element>::Clear() {
    if (data != nullptr)
        delete[] data;
    data = nullptr;
    length = 0;
}

template<typename Element>
Vector<Element>::Vector() { }

template<typename Element>
Vector<Element>::Vector(const int length_) {
    length = length_;
    data = new Element[length]();
}

template<typename Element>
Vector<Element>::Vector(const Vector<Element>& v) {
    length = v.length;
    data = new Element[length];
    for (int i = 0; i < length; ++i) {
        data[i] = v.data[i];
        // Set(i, v.Get(i));
    }
}

template<typename Element>
Vector<Element>& Vector<Element>::operator=(
const Vector<Element>& right) 
{
    if (this == &right)
        return *this;
    Clear();

    length = right.length;
    data = new Element[length]();
    for (int i = 0; i < length; ++i) {
        data[i] = right.data[i];
        // Set(i, right.Get(i));
    }

    return *this;
}

template<typename Element>
Vector<Element>::~Vector() {
    Clear();
}

template<typename Element>
bool Vector<Element>::Set(const int i, const Element element) {
    if (i < 0 || i >= length) {
        std::cerr << "Writing element not valid at pos " << i;
        std::cout << std::endl;
        return false;
    }
    data[i] = element;
    return true;
}

#endif