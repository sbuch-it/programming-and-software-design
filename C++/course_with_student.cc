#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Student {
 private:
    std::string name;
    int id = 0;

 public:
    // default costructor
    Student() { }
    // costructor with parameters
    Student(const std::string& name_, 
        const int id_) : name(name_), id(id_) { }

    inline const std::string& GetName() const {
        return name;
    }
    inline int GetId() const {
        return id;
    }

    // friendship to access private data
    friend std::ostream& operator<<(
        std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
}; // end Student


std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.id << " " << s.name << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    is >> s.id;
    std::getline(is, s.name);

    if (s.name.length() > 1) {
        // if we have " Mario Rossi"
        s.name = s.name.substr(1); // delete the first character
        // we get the string "Mario Rossi"
    } else {
        std::cerr << "Invalid name" << std::endl;
    }

    return is;
}

class Course {
 private:
    std::vector<Student> stud; // vector of students

 public:
    // constructor that reads students from file
    Course(const std::string& filename);

    bool Find(const std::string& name) const;
    bool Find(const int id) const;
};

Course::Course(const std::string& filename) {

    std::ifstream is(filename);
    if (!is.good()) {
        std::cerr << "Can not find file " << filename << std::endl;
        return;
    }

    // reads students from file
    int num_stud = 0;
    is >> num_stud;

    if (num_stud <= 0) {
        std::cerr << "I need at least 1 student to have a class \n";
        return;
    }
    stud.reserve(num_stud);

    // skip the line that started with the number 5
    std::string name;
    std::getline(is, name);  // read a blank line

    for (int i = 0 ; i < num_stud; ++i) {
        Student s;
        is >> s;
        stud.push_back(s);
    }
}

bool Course::Find(const std::string& name) const {
    for (const Student& s : stud) {
        if (s.GetName() == name)
            return true;
    }
    return false;
}

bool Course::Find(const int id) const {
    for (const Student& s : stud) {
        if (s.GetId() == id)
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