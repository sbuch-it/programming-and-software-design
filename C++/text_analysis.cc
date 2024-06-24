#include <map>
#include <string>
#include <fstream>
#include <iostream>

class TextAnalysis {
 private:
    std::map<std::string, float> word2freq;

 public: 
    TextAnalysis(const std::string& filename) {
        std::ifstream is(filename);
        std::string word;
        while (is >> word)
            word2freq[word]++;
    }

    void Print() const {
        // C++94
        /*
        std::map<std::string, float>::const_iterator iter = 
            word2freq.begin();
        for (; iter != word2freq.end(); ++iter) {
            std::cout << iter->first << "->" << iter->second << "\n";
        }
        */

        // C++11
        for (const auto& iter : word2freq) {
            std::cout << iter.first << " -> " << iter.second << "\n";
        }
    }

    float GetFreq(const std::string& word) const {
        // C++94
        /*
        std::map<std::string, float>::const_iterator iter = 
            word2freq.find(word);
        */

        // C++11
        auto iter = word2freq.find(word);
        // return (iter != word2freq.end() ? iter->second : 0.0f);
        if (iter != word2freq.end()) {
            return iter->second;
        } else {
            return 0.0f;
        }
    }
};

int main() {

    TextAnalysis ta("text.txt");

    ta.Print();

    std::cout << "plastica: " << ta.GetFreq("plastica") << "\n";
    std::cout << "pippo:" << ta.GetFreq("pippo") << "\n";
    
    return 0;
}