#include "vector_unique_ptr.h"

Vector::Vector() { }

Vector::Vector(const int length_) :
    length(length_), data(new Element[length]()) {}

Vector::Vector(const Vector& v) :
    length(v.length), data(new Element[v.length]()) {
    for (int i = 0; i < length; ++i) {
        data[i] = v.data[i];
    }
}

Vector& Vector::operator=(const Vector& right) {
    if (this == &right)
        return *this;

    if (length != right.length) {
        length = right.length;
        data.reset(new Element[length]());
    }

    for (int i = 0; i < length; ++i) {
        data[i] = right.data[i];
    }

    return *this;
}

bool Vector::Set(const int i, const Element element) {
    if (i < 0 || i >= length) {
        std::cerr << "Writing element not valid at pos " << i << std::endl;
        return false;
    }
    data[i] = element;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << v.length << std::endl;
    for (int i = 0; i < v.length; ++i) {
        out << v.data[i] << " ";
    }
    out << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Vector& v) {
    in >> v.length;
    v.data.reset(new Vector::Element[v.length]);
    for (int i = 0; i < v.length; ++i) {
        in >> v.data[i];
    }
    return in;
}