#include <string>
#include <iostream>
#include <fstream>

class TextAnalizer {
 private:
    std::string text; // std::ifstream is;
    bool valid = false;

 public:
    TextAnalizer(const std::string& filename) {
        
        std::ifstream is(filename);

        if (!is.good()) {
            std::cerr << "I can not open the file \n";
            valid = false;
            return;
        }
        // File opened
        valid = true;
        std::string word;

        // read one word at a time until the end
        while (is >> word) {
            if (text.length() > 0) {
                text += " ";
            }
            text += word;
            // text += (text.empty() ? "" : " ") + word;
        }
    }

    bool Find(const std::string& word) {
        if (!valid) {
            std::cerr << "Can not search over an unopened file";
            return false;
        }
        
        return text.find(word) != std::string::npos;
    }
};

int main() {
    
    std::ofstream of("text_analyzer.txt");
    of << "Ieri sono andato al mare ed ho trovato Pippo che prendeva il sole.";
    of.close();

    TextAnalizer ta("text_analyzer.txt");
    
    if (ta.Find("Pippo")) {
        std::cout << "Pippo ci sta\n";
    } else {
        std::cout << "Pippo non ci sta\n";
    }

    if (ta.Find("Pluto")) {
        std::cout << "Pluto ci sta\n";
    } else {
        std::cout << "Pluto non ci sta\n";
    }

    return 0;
}