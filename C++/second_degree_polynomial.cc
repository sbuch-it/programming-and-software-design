#include <cstdio> // C Standard Input and Output Library
#include <cmath> // C numerics library

class Roots {
 private:
    // C++11
    float r1 = 0.0f;
    float r2 = 0.0f;
    bool found1 = false;
    bool found2 = false;

 public:
    // In pre C++11 We had to initialize the variables in the
    // default constructor while now we can initialize them
    // when they are defined as data members
    /*
    Roots() {
        r1 = 0.0f;
        r2 = 0.0;
        foun1 = false;
        found2 = false;
    }
    */
    
    // Default Constructor
    Roots() { }

    // Constructor with parameters
    Roots(
        const float r1_, const float r2_, 
        const bool found1_, const bool found2_) {
        r1 = r1_; 
        r2 = r2_;
        found1 = found1_;
        found2 = found2_;
    }
    
    // Getters
    float GetR1() {
        return r1;
    }
    float GetR2() {
        return r2;
    }
    bool GetFound1() {
        return found1;
    }
    bool GetFound2() {
        return found2;
    }

}; // end Roots

class Polynomial {
 private:
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;

 public:
    // Constructor with parameters
    Polynomial(const float a_, const float b_, const float c_) {
        if (a_ == 0.0f) {
            printf("Initializing polynomial of grade 0 \n");
        }
        a = a_;
        b = b_;
        c = c_;
    }

    float Eval(const float x) {
        // return a * std::pow(x, 2.0f) + b * x + c;
        return a * x * x + b * x + c;
    }

    // Mode 1 (not preferable)
    void GetRootsWithPointers(float* r1, float* r2, 
        bool* found1, bool* found2) {
        
        *r1 = 0.0;
        *r2 = 0.0;
        *found1 = false;
        *found2 = false;

        const float delta_squared = b * b - 4.0f * a * c;

        if (delta_squared > 0.0f) {
            const float delta = std::sqrt(delta_squared);
            *r1 = (-b + delta) / (2 * a);
            *r2 = (-b - delta) / (2 * a);
            *found1 = true;
            *found2 = true;
        } else if (delta_squared == 0.0f) {
            *r1 = -b / (2* a);
            *found1 = true;
        }
    }

    // Mode 2 (preferable)
    Roots GetRoots() {
        if (a == 0.0f) {
            // y = b * x + c = 0
            // x = -c / b
            return Roots((b != 0.0f) ? -c / b : 
                0.0f, 0.0f, (b != 0.0f), false);
        }

        const float delta_squared = b * b - 4.0f * a * c;

        if (delta_squared > 0.0f) {
            const float delta = std::sqrt(delta_squared);
            return Roots((-b + delta) / (2.0f * a), 
                (-b - delta) / (2.0f * a), true, true);
        } else if (delta_squared == 0.0f) {
            return Roots(-b / (2.0f * a), 0.0f, true, false);
        }

        return Roots(0.0f, 0.0f, false, false);
    }
}; // end Polynomial

int main() {
    
    Polynomial p(1.0f, 4.0f, 3.0f);
    
    // Evaluate the polynomial
    printf("Eval 1: %f \n", p.Eval(1.0f));
    printf("Eval 2: %f \n", p.Eval(3.0f));
    printf("Eval 3: %f \n", p.Eval(-1.0f));

    // Mode 1 to calculate the roots
    printf("Mode 1 to calculate the roots \n");
    float r1 = 0.0f;
    float r2 = 0.0f;
    bool found1 = false;
    bool found2 = false;
    p.GetRootsWithPointers(&r1, &r2, &found1, &found2);
    if (found1) {
        printf("Root1: %f \n", r1);
    }
    if (found2) {
        printf("Root2: %f \n", r2);
    }

    // Mode 2 to calculate the roots
    printf("Mode 2 to calculate the roots \n");
    Roots roots = p.GetRoots();
    if (roots.GetFound1()) {
        printf("Root1: %f \n", roots.GetR1());
    }
    if (roots.GetFound2()) {
        printf("Root2: %f \n", roots.GetR2());
    }
    if (!roots.GetFound1() && !roots.GetFound2()) {
        printf("No Roots for this polynomial \n");
    }

    // Test with polynomial of grade 0
    printf("Test with polynomial of grade 0 \n");
    Polynomial p_grade_1(0.0f, 4.0f, 3.0f);
    Roots roots_grade_1 = p_grade_1.GetRoots();
    if (roots_grade_1.GetFound1()) {
        printf("Root_grade_1_1: %f\n", roots_grade_1.GetR1());
    }
    if (roots_grade_1.GetFound2()) {
        printf("Root_grade_1_2: %f\n", roots_grade_1.GetR2());
    }

    return 0;
}