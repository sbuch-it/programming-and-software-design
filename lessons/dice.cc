#include <iostream>
#include <cstdlib>

class Dice {
 private:
    int num_faces = 0;
    float * stats = nullptr;

 public:
    Dice(const int num_faces_) {
        srand(time(NULL));
        num_faces = num_faces_;
        if (num_faces > 1) {
            stats = new float[num_faces]();
        } else {
            std::cerr << "I can not create a dice with less than 2 faces \n";
        }
    }

    int Roll(){
        const int num_generated = rand() % num_faces;
        stats[num_generated]++;
        return num_generated + 1;
    }

    void PrintStats() const {
        std::cout << "Probability Distribution" << std::endl;
        float sum = 0.0f;
        for (int i = 0; i < num_faces; i++){
            sum += stats[i];
        }
        for (int i = 0; i < num_faces; i++){
            std::cout << i + 1 << ": " << stats[i] / sum << "\n";
        }
        std:: cout << std::endl;
    }

    void Clear(){
        /* ... for i = 0 i < num_faces : stats[i] = 0 */
    }

    ~Dice(){
        if (stats != nullptr){
            delete[] stats;
        }
    }
}; // end Dice

int main(){
    Dice dice(8);
    for(int i = 0; i < 100000; i++){
        dice.Roll();
    }
    dice.PrintStats();
    return 0;
}