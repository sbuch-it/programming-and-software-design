#include <fstream>
#include <iostream>
#include <map>
#include <deque>
#include <string>

class TextAnalysis {
 private:
    typedef std::map<std::string, float> Word2Freq;
    Word2Freq word2freq;

 public:
    TextAnalysis(const std::string& filename) {
        std::ifstream is(filename);
        std::string word;
        while (is >> word) {
            word2freq[word]++;
        }
    }

    void Print() const {
        for (const auto& iter : word2freq) {
            std::cout << iter.first << " -> " << iter.second << "\n";
        }
    }

    float GetFreq(const std::string& word) const {
        auto iter = word2freq.find(word);
        return (iter != word2freq.end() ? iter->second : 0.0f);
    }

    std::deque<std::string> GetWordsOrderedByFreq() const {
        std::map<int, std::deque<std::string>, std::less<int> > freq2words;
        // Per default usiamo std::less<int> altrimenti
        // cambiamo al posto di less con greater (decrescente)
        for (const std::pair<std::string, float>& elem : word2freq) {
            freq2words[elem.second].push_back(elem.first);
        }
        std::deque<std::string> words;
        for (const auto& elem : freq2words) {
            for (const std::string& word : elem.second) {
                words.push_back(word);
            }
        }

        // Con tracciatura delle frequenze
        /*
        std::deque<std::pair<std::string, float>> words;
        for (const auto& elem : freq2words) {
            const float freq = elem.first;
            const std::deque<std::string>& words = elem.second;
            for (const std::string& word : words) {
                auto p = std::pair<std::string, float>(word, freq);
                auto p = std::make_pair(word, freq);
                words.push_back(p);
            }
        }
        */
        return words;
    }
};

int main() {
    TextAnalysis ta("text.txt");

    std::cout << "plastica freq:" << ta.GetFreq("plastica") << std::endl;
    std::cout << "pippo freq:" << ta.GetFreq("pippo") << std::endl;

    const auto words = ta.GetWordsOrderedByFreq();
    for (const std::string& word : words) {
        std::cout << word << std::endl;
    }

    return 0;
}