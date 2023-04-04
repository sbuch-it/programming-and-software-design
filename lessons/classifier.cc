#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// Classe Base
class ClassifierBase {
 public:
    virtual bool Classify(const std::string& text) const = 0;
    virtual ~ClassifierBase() { }
};

// Classe Foglia
class ClassifierLeaf : public ClassifierBase {
 protected:
    const std::set<std::string> keywords;  // unsorted_set

 public:
    ClassifierLeaf(const std::set<std::string>& keywords_) :
        keywords(keywords_) {}

    virtual bool Classify(const std::string& text) const {
        unsigned int count = 0;
        std::istringstream is(text);
        std::string word;
        while (is >> word) {
            // O(num_parole_nel_testo * log(num_keyword))
            if (keywords.find(word) != keywords.end()) {
                count++;
            }
        }
        return (count > 2);
    }
    virtual ~ClassifierLeaf() {}
};

// Classe Composite
class ClassifierComposite : public ClassifierBase {
 protected:
    std::vector<const ClassifierBase*> classifiers;

 public:
    void AddClassifier(const ClassifierBase* classifier) {
        classifiers.push_back(classifier);
    }

    virtual bool Classify(const std::string& text) const {
        for (const ClassifierBase* c : classifiers) {
            if (c->Classify(text)) {
                return true;
            }
        }
        return false;
    }
    virtual ~ClassifierComposite() {
        for (const ClassifierBase* c : classifiers) {
            delete c;
        }
    }
};

class SoccerClassifier : public ClassifierComposite {
 public:
    SoccerClassifier() {
        std::set<std::string> keywords_c5{"calcetto", "campetto", "cinque", "goal"};
        ClassifierBase* c5 = new ClassifierLeaf(keywords_c5);
        std::set<std::string> keywords_c11{"calcio", "campo", "11", "goal"};
        ClassifierBase* c11 = new ClassifierLeaf(keywords_c11);
        this->AddClassifier(c5);
        this->AddClassifier(c11);
    }
    virtual ~SoccerClassifier() {}
};

class TennisClassifier : public ClassifierComposite {
 public:
    TennisClassifier() {
        std::set<std::string> keywords_tt{"tavolo", "racchettina", "difesa", "schiacciata"};
        ClassifierBase* tt = new ClassifierLeaf(keywords_tt);
        std::set<std::string> keywords_tn{"campo", "smash", "dritto", "nadal"};
        ClassifierBase* tn = new ClassifierLeaf(keywords_tn);
        this->AddClassifier(tt);
        this->AddClassifier(tn);
    }
    virtual ~TennisClassifier() {}
};

class SportClassifier : public ClassifierComposite {
 public:
    SportClassifier() {
        ClassifierBase* t = new TennisClassifier();
        ClassifierBase* c = new SoccerClassifier();
        this->AddClassifier(t);
        this->AddClassifier(c);
    }
    virtual ~SportClassifier() {}
};

int main() {
    const SportClassifier sport;
    const std::string text1 = "nadal effettua uno smash dopo un dritto potente";
    std::cout << text1 << " -> " << (sport.Classify(text1) ? "SPORT" : "NO_SPORT") << std::endl;
    const std::string text2 = "conte e letta si incontrano a palazzo chigi";
    std::cout << text2 << " -> " << (sport.Classify(text2) ? "SPORT" : "NO_SPORT") << std::endl;
    return 0;
}