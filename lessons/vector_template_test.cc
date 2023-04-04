#include <fstream>
#include <iostream>

#include "vector_template.h"

int main() {
    // default constructor with parameters
    Vector<int> v(4);

    // setter method
    v.Set(0, 0.1);
    v.Set(1, 0.23);
    v.Set(2, 0.1);
    v.Set(3, 2.1);

    // copy constructor
    Vector<int> v1(v);

    // default constructor
    Vector<int> v2;

    // operator=
    v2 = v1;

    return 0;
}