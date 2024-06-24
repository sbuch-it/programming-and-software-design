#include <string>
#include <iostream>
#include <fstream>

class TextAnalizer {
public:
    TextAnalizer() {}

    bool Find(const std::string& filename, const std::string& word) {
        std::ifstream is(filename);
        if (!is.good()) {
            std::cerr << "I can not open the file \n";
            return false; 
        }

        std::string str;
        while (is >> str) {
            if (str == word) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::ofstream of("text_analyzer.txt");
    of << "Ieri sono andato al mare ed ho trovato Pippo che prendeva il sole.";
    of.close();

    TextAnalizer ta;
    
    if (ta.Find("text_analyzer.txt", "Pippo")) {
        std::cout << "Pippo ci sta\n";
    } else {
        std::cout << "Pippo non ci sta\n";
    }

    if (ta.Find("text_analyzer.txt", "Pluto")) {
        std::cout << "Pluto ci sta\n";
    } else {
        std::cout << "Pluto non ci sta\n";
    }

    return 0;
}