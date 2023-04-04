#include <iostream>
#include <fstream>

class Vector {
 private:
    typedef double Element;
    int length = 0;
    Element* data = nullptr;

    // deallocate previous data
    void Clear(){
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        length = 0;
    } 

 public:
    // default constructor
    Vector() { }

    // costructor with parameters
    Vector(const int length_) {
        length = length_;
        data = new Element[length]();
    }

    // copy constructor
    Vector(const Vector& v) {
        length = v.length;
        data = new Element[length];
        for (int i = 0; i < length; ++i) {
            data[i] = v.data[i];
            // Set(i, v.Get(i));
        }
    }

    // operator=
    Vector& operator=(const Vector& right) {
        if(this == &right)
            return *this; // avoid self-assignment

        Clear();
        length = right.length;
        data = new Element[length](); // allocate memory

        for(int i = 0; i < length; ++i) {
            data[i] = right.data[i];
            // Set(i, right.Get(i));
        }
        return *this;
    }

    // destructor
    ~Vector() {
        Clear();
    }

    inline int GetLength() const{
        return length;
    }

    // operator[]
    inline Element& operator[](const int i) const {
        return data[i];
    }

    // getter to return a vector element
    Element Get(const int i) const {
        if (!Good(i)) {
            return ' ';
        }
        return data[i];
    }

    // setter to modify a vector element
    bool Set(const int i, const Element element) {
        if (!Good(i)) {
            return false;
        }
        data[i] = element;
        return true;
    }

    // check if vector index is good
    bool Good(const int i) const {
        if (i < 0 || i >= length) {
            std::cerr << "Writing element not valid at pos " << i;
            std::cerr << std::endl;
            return false;
        }
        return true;
    }
    
    // friendship
    friend std::ostream& operator<<(
        std::ostream& out, const Vector& v);
    friend std::istream& operator>>(std::istream& in, Vector& v);

}; // end Vector


// operator <<
std::ostream& operator<<(std::ostream& out, const Vector& v) {
    out << v.length << std::endl;
    for (int i = 0; i < v.length; ++i){
        out << v.data[i] << " ";
    }
    out << std::endl;
    return out;
}

// operator >>
std::istream& operator>>(std::istream& in, Vector& v){
    v.Clear();
    in >> v.length;
    v.data = new Vector::Element[v.length];
    for (int i = 0; i < v.length; ++i){
        in >> v.data[i];
    }
    return in;
}

int main() {
    Vector v(4);
    v.Set(0, 0.1);
    v.Set(1, 0.23);
    v.Set(2, 0.1);
    v.Set(3, 2.1);

    /*
    for (int i = 0; i < v.GetLength(); ++i) {
        std::cout << v.Get(i) << " with operator[] " << v[i];
        std::cout << std::endl;
    }
    */
   
    std::cout << v;
    Vector v1(v);
    Vector v2; // default constructor
    v2 = v1; // call operator=

    /*
    for (int i = 0; i < v2.GetLength(); ++i) {
        std::cout << v2.Get(i) << std::endl;
    }
    */
   
    std::cout << v2; // print on the screen

    // write to file
    std::ofstream of("vector.dat");
    if(of.good()){
        of << v;
    }
    of.close(); // closing the stream

    std::ifstream ifs("vector.dat");
    if(ifs.good()){
        ifs >> v2;
        std::cout << "Print after operator>> " << v2;
    }

    return 0;
}