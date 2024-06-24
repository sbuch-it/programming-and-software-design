#include <ctime>
#include <iostream>

const int N = 90;

class Tombola {
 private:
    int scoreboard[N];

 public:
    Tombola(){
        Reset();
    }

    void Reset(){
        for (int i = 0; i < N; i++) {
            scoreboard[i] = 0;
        }
    }

    int Extract() {

        if (End()) {
            return 0;
        }

        srand(time(NULL));
        int num;
        bool valid = false;

        while(!valid) {
            num = rand() % N + 1;            
            if (scoreboard[num - 1] != 1){
                scoreboard[num - 1] = 1;
                valid = true;
            }
        }
        return num;
    }

    bool End() {
        for (int i = 0; i < N; i++) {
            if (scoreboard[i] == 0) {
                return false;   
            }
        }
        return true;
    }

    void Print() {
        int start = 0;
        std::cout << "The numbers drawn are: " << std::endl;

        for (int i = 0; i < N; i++) {
            if (scoreboard[i] == 1) {
                std::cout << i + 1 << " ";
            } else {
                start++;
            }
        }

        if (start == N) {
            std::cout << "none";
        }
        std::cout << std::endl;
    }
}; // end Tombola


int main(){
    
    int c = 1;
    Tombola tombola;

    std::cout << "Play with 1, 2, 3 and 0 to exit" << std::endl;
    std::cout << "1. Delete the numbers drawn" << std::endl;
    std::cout << "2. Extract a new number" << std::endl;
    std::cout << "3. View the numbers drawn" << std::endl;

    while(c != 0) {
        std:: cout << "Command: ";
        std::cin >> c;
        switch (c) {
            case 0: {
                break;
            }
            case 1: {
                tombola.Reset();
                break;
            }
            case 2: {
                int number = tombola.Extract();
                if(number != 0){
                    std::cout << "The drawn number is " << number;
                    std::cout << std::endl;
                }else{
                    std::cout << "The game is over, all the numbers have been drawn" << std::endl;
                }
                break;
            }
            case 3: {
                tombola.Print();
                break;
            }
            default: {
                std::cout << "Command entered invalid";
                std::cout << std::endl;
                break;
            }
        }
    }
}