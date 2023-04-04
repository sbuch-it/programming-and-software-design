#include <iostream>

class String {
 private:
    int length = 0; // string length
    char* str = nullptr;
    // pointer to the first character of the string

 public:
    // Costructor with parameters
    String(const int length_) {
        length = length_;
        str = new char[length];
        for (int i = 0; i < length; ++i) {
            str[i] = ' ';
        }
    }
    // Copy Constructor
    String(const String& s) {
        length = s.length;
        str = new char[length];
        for (int i = 0; i < length; ++i) {
            str[i] = s.str[i];
        }
    }
    // Destructor
    ~String() {
        delete[] str;
    }

    int GetLength() const {
        return length;
    }
    char Get(const int i) const {
        if (i < 0 || i >= length) {
            std::cerr << "Char not valid at pos " << i << std::endl;
            return ' ';
        }
        return str[i];
    }
    void Set(const int i, const char c) {
        if (i < 0 || i >= length) {
            std::cerr << "Writing char not valid at pos " << i;
            return;
        }
        str[i] = c;
    }

    void Print() const {
        for (int i = 0; i < length; ++i) {
            std::cout << str[i];
        }
        std::cout << std::endl;
    }

    void Concat(const String& s) {
        char* str1 = new char[length + s.length];
        for (int i = 0; i < length; ++i) {
            str1[i] = str[i];
        }
        for (int i = 0; i < s.length; ++i) {
            str1[i + length] = s.str[i];
        }
        delete[] str;
        str = str1;
        length += s.length;
    }
};

int main() {
    String s(4);
    String s1(4);
    s.Set(0, 'a');
    s.Set(1, 'b');
    s.Set(2, 'c');
    s.Set(3, 'a');

    s.Concat(s1);
    s.Print();
    String s2(s);
    s2.Print();
    
    return 0;
}