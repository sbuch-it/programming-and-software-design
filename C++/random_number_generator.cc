#include <cstdlib> // C Standard General Utilities Library
#include <cstdio> // C Standard Input and Output Library
#include <ctime> // C Time Library

class RandomNumbers {
 private:
    float max_num; // maximum number
    float min_num; // minimum number
    bool valid; // check for (max_num <= min_num)

 public:
    // Costructor with parameters
    RandomNumbers(float min_num_, float max_num_) {
        max_num = max_num_;
        min_num = min_num_;
        
        if (max_num <= min_num) {
            valid = false;
            printf("Generator in inconsistent state \n");
        } else {
            valid = true;
        }

        srand(time(NULL));
        // makes use of the computer's internal
        // clock to control the choice of the seed
    }

    // Method for generating a random number
    float Random() {
        if (!valid) {
            printf("Generator in inconsistent state\n");
            return max_num + 1.0;
        }

        // return min_num + rand() % (max_num - min_num);

        return min_num + ( (float) rand() / (float) RAND_MAX ) 
            * (max_num - min_num);
        // Using srand() and rand() to generate random numbers
    }
};  // end RandomNumbers


int main() {

    RandomNumbers generator(0.0, 1.0);
  
    for (int i = 0; i < 100; ++i) {
        printf("%f \n", generator.Random());
    }

    return 0;
}