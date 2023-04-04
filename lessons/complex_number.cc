#include <cstdio> // C Standard Input and Output Library

class ComplexNumber {
 private:
    double real; // real part
    double imm; // imaginary part

    // Setters for the real part
    void SetReal(const double real_) {
        real = real_;
    }
    // Setters for the imaginary part
    void SetImm(const double imm_) {
        imm = imm_;
    }

 public:
    // Default Constructor
    ComplexNumber() {
        real = 0.0;
        imm = 0.0;
    }

    // Constructor with parameters
    ComplexNumber(const double real_, const double imm_) {
        real = real_;
        imm = imm_;
    }

    // Getters for the real part
    double GetReal() {
        return real;
    }
    // Getters for the imaginary part
    double GetImm() {
        return imm;
    }

    // Addition with copy
    ComplexNumber Add(ComplexNumber& c) {
        ComplexNumber result(real + c.real, imm + c.imm);
        return result;
    }

    // Addition without copy
    void AddWithoutCopy(ComplexNumber& c, ComplexNumber* result) {
        // result->real = real + c.real;
        // result->imm = imm + c.imm;

        // result->real = real + c.GetReal();
        // result->imm = imm + c.GetImm();

        result->SetReal(real + c.real);
        result->SetImm(imm + c.imm);
    }

    // Method to check if the two complex numbers are equal
    bool Equals(ComplexNumber& c) {
        return (real == c.GetReal() && imm == c.GetImm());
    }

    // Method for printing a complex number
    void Print() {
        printf("real:%lf imm:%lf\n", real, imm);
    }

    // Product with copy
    ComplexNumber Prod(ComplexNumber& c) {
        double new_real = real * c.real - imm * c.imm;
        double new_imm = imm * c.real + real * c.imm;
        ComplexNumber result(new_real, new_imm);
        return result;
    }

    // Product without copy
    void ProdWithoutCopy(ComplexNumber& c, ComplexNumber* result){
        result->SetReal(real * c.real - imm * c.imm);
        result->SetImm(imm * c.real + real * c.imm);
    }

}; // end ComplexNumber

int main() {
    ComplexNumber c1(1.0, 1.0);
    ComplexNumber c2(3.0, 2.3);

    // Addition
    ComplexNumber c1_plus_c2 = c1.Add(c2);
    ComplexNumber c1_plus_c2_without_copy;
    c1.AddWithoutCopy(c2, &c1_plus_c2_without_copy);

    // Check
    if (c1_plus_c2.Equals(c1_plus_c2_without_copy)) {
        printf("Sum is same \n");
    } else {
        printf("Something wrong \n");
        c1_plus_c2.Print();
        c1_plus_c2_without_copy.Print();
        return 1;
    }

    // Product
    ComplexNumber c1_times_c2 = c1.Prod(c2);

    // Print
    c1_times_c2.Print();

    return 0;
}