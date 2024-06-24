#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Course {
 private:
    std::vector<std::string> stud; // vector of students
    std::vector<std::string> stud_id; // vector of students id

 public:
    // copy constructor
    Course(const std::string& filename);

    // method to find a student
    bool Find(const std::string& name) const;
};

Course::Course(const std::string& filename) {

    std::ifstream is(filename);
    if (!is.good()) {
        std::cerr << "Can not find file " << filename << std::endl;
        return;
    }

    // read the number of students from file
    int num_stud = 0;
    is >> num_stud;
    if (num_stud <= 0) {
        std::cerr << "I need at least 1 student to have a class \n";
        return;
    }

    stud.reserve(num_stud);
    stud_id.reserve(num_stud);

    // skip the line that started with the number 5
    std::string id;
    std::string name;
    std::getline(is, name); // read a blank line

    for (int i = 0 ; i < num_stud; ++i) {
        is >> id;
        std::getline(is, name); // return the string by one line
        name = name.substr(1);
        stud.push_back(name);
        stud_id.push_back(id);
    }
}

bool Course::Find(const std::string& name) const {
    // Basic mode with index, also C++94
    /*
    for (unsigned int i = 0; i < stud.size(); ++i) {
        if (stud[i] == name)
            return true;
    }
    */

    // With iterators, also c++94
    /*
    std::vector<std::string>::const_iterator iter = stud.begin();
    for (; iter != stud.end(); ++iter) {
        if (*iter == name)
            return true;
    }
    */

    // With iterators and auto, C++11
    /*
    auto iter = stud.begin();
    for (; iter != stud.end(); ++iter) {
        if (*iter == name)
            return true;
    }
    */

    // With C++11, which is preferred
    for (const std::string& s : stud) {
        if (s == name)
            return true;
    }
    
    return false;
}

int main() {
    Course c("course.txt"); // call constructor
    std::cout << "Mario Rossi " << c.Find("Mario Rossi");
    std::cout << std::endl;
    std::cout << "Carla Bruni " << c.Find("Carla Bruni");
    std::cout << std::endl;
    std::cout << "Marco Lorenzo Franceschi in de Neri ";
    std::cout << c.Find("Marco Lorenzo Franceschi in de Neri");
    std::cout << std::endl;

    return 0;
}