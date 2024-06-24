#include <fstream>
#include <iostream>
#include "vector.h"

int main() {
    Vector v(4);
    v.Set(0, 0.1);
    v.Set(1, 0.23);
    v.Set(2, 0.1);
    v.Set(3, 2.1);
    std::cout << v;

    Vector v1(v); // call default constructor

    Vector v2;
    
    v2 = v1; // operator=
    std::cout << v2;

    {
        std::ofstream of("vector.dat");
        if (of.good()) {
            of << v;
        }
    }

    std::ifstream ifs("vector.dat");
    if (ifs.good()) {
        ifs >> v2;
        std::cout << "Print after operator>> " << v2;
    }
    return 0;
}