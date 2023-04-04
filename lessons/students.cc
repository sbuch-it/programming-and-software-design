#include <map>
#include <string>
#include <fstream>
#include <iostream>

class Students {
 private:
    typedef std::map<std::string, int> Student2Mark;
    Student2Mark student2mark;

 public:
    // constructor
    Students(const std::string& filename) {

        // file has the following structure
        // mark1 name1
        // mark2 name2
        // ...

        std::ifstream is(filename);
        if (!is.good()) {
            std::cerr << "Error \n";
            return;
        }

        // if the name were one word
        /*
        std::string name;
        int mark = 0;
        while (is >> name >> mark) {
            student2mark[name] = mark;
        }
        */

        // if the name were more than a word
        int mark = 0;
        while (is >> mark) {
            std::string name;
            std::getline(is, name);
            name = name.substr(1);

            if (student2mark.find(name) != student2mark.end()) {
                std::cerr << "Student" << name << "already inserted";
                std::cerr << std::endl;
            }
            student2mark[name] = mark;
        }
    }

    static const int INVALID_MARK = -1;
    
    // method to find a mark of a student
    inline int GetMark(const std::string& name) const {
        // Student2Mark::const_iterator iter = 
            // student2mark.find(name);

        auto iter = student2mark.find(name); // in C++11
        if (iter == student2mark.end()) {
            return INVALID_MARK;
        }
        return iter->second;
    }

    // method to check if a mark is valid
    inline bool HasMark(const std::string& name) const {
        return student2mark.find(name) != student2mark.end();
    }

    // method to check if the map has been initialized correctly
    inline bool Good() const {
        return (student2mark.size() > 0);
    }

    // method for printing marks
    void Print() const {
        // per C++11
        /*
        for (const std::pair<std::string, int>& s : student2mark) {
            std::cout << s.first << " => " << s.second << std::endl;
        }
        */

        // in C++11
        for (const auto& s : student2mark) {
            std::cout << s.first << " => " << s.second << std::endl;
        }
    }
};


int main() {
    Students students("students.txt");

    if(!students.Good()) {
        std::cerr << "I can not load the students \n";
        return 1;
    }

    students.Print();

    const std::string name = "Mario Rossi";
    if (students.HasMark(name)) {
        std::cout << name << " ha preso " << students.GetMark(name);
        std::cout << std::endl;
    } else {
        std::cout << name << " non ha fatto l'esame" << std::endl;
    }

    return 0;
}