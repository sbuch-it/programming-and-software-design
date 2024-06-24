#include "vector.h"

// clear method
void Vector::Clear() {
    if (data != nullptr)
        delete[] data;
    data = nullptr;
    length = 0;
}

// constructor
Vector::Vector() { }

// constructor with parameters
Vector::Vector(const int length_) {
    length = length_;
    data = new Element[length]();
}

// copy constructor
Vector::Vector(const Vector& v) {
    length = v.length;
    data = new Element[length];
    for (int i = 0; i < length; ++i) {
        data[i] = v.data[i];
        // Set(i, v.Get(i));
    }
}

// internal operator to Vector then Vector ::
Vector& Vector::operator=(const Vector& right) {
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

// destructor
Vector::~Vector() {
    Clear();
}

bool Vector::Set(const int i, const Element element) {
    if (i < 0 || i >= length) {
        std::cerr << "Writing element not valid at pos " << i << std::endl;
        return false;
    }
    data[i] = element;
    return true;
}

// external operator to Vector
std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << v.length << std::endl;
    for (int i = 0; i < v.length; ++i) {
        out << v.data[i] << " ";
    }
    out << std::endl;
    return out;
}

// external operator to Vector
std::istream& operator>>(std::istream& in, Vector& v) {
    v.Clear();
    in >> v.length;
    v.data = new Vector::Element[v.length];
    for (int i = 0; i < v.length; ++i) {
        in >> v.data[i];
    }
    return in;
}