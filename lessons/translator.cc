#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class BaseClass {
 public:
    bool FromFile(const std::string& filename);
    std::string Translate(const std::string& phrase);
};


class ChildClass : public BaseClass {
 protected:
    std::map<std::string, std::string> words;

 public:
    bool FromFile(const std::string& filename) {
        std::ifstream is(filename);
        if (!is.good()) {
            std::cerr << "Can not open file";
            return false;
        }
        
        int num_words; 
        is >> num_words;
        std::string word_original;
        std::string word_translated;
        for (int i = 0; i < num_words; i++) {
            is >> word_original >> word_translated;
            words[word_original] = word_translated;
        }
        return true;
    }

    std::string Translate(const std::string& phrase) {
        std::istringstream ss(phrase);
        std::string word;
        std::string phrase_translated = "";
        while (ss >> word) {
            std::map<std::string, std::string>::const_iterator iter;
            int size = words.size();
            for (iter = words.begin(); iter != words.end(); iter++) {
                if (iter->first == word) {
                    phrase_translated = phrase_translated + " " + iter->second;
                } else {
                    size--;
                }
            }
            if (size == 0) {
                phrase_translated = phrase_translated + " UNKNOWN";
            }
        }
        return phrase_translated + "\n";
    }
};


int main() {
    ChildClass cc;

    cc.FromFile("translator.txt");
    std::cout << cc.Translate("Il tavolo è verde e rosso");
    std::cout << cc.Translate("Il gatto è bianco e nero");

    return 0;
}