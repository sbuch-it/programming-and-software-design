#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// public interface to all objects in the class hierarchy
class PersonBase {
 public:
    virtual std::string ToString() const = 0;
    // virtual bool FromString(const std::string& str) = 0;

    virtual bool ToFile(const std::string& filename) const = 0;
    // virtual bool FromFile(const std::string& filename) = 0;

    virtual ~PersonBase() { }
}; // end PersonBase


class Person : public PersonBase {
 protected:
    std::string name;
    std::string country_of_citizenship;

    virtual std::ostream& ToStream(std::ostream& os) const {
        os << name << " " << country_of_citizenship;
        return os;
    }

 public:
    // constructor with pre-run initialization
    Person(
        const std::string& name_,
        const std::string& country_of_citizenship_) :
        name(name_), country_of_citizenship(country_of_citizenship_)
        { }

    const std::string& GetName() const {
        return name;
    }

    const std::string& GetCountryOfCitizenship() const {
        return country_of_citizenship;
    }

    virtual void Print() const {
        std::cout << name << " " << country_of_citizenship;
    }

    virtual ~Person() { }
}; // end Person


class Student : public Person {
 protected:
    std::string program;

 public:
    // constructor with pre-run initialization
    Student(
        const std::string& name_,
        const std::string& country_of_citizenship_,
        const std::string& program_) :
        Person(name_, country_of_citizenship_), program(program_) {}
    // call the constructor of the parent class Person

    /*
    Student(
        const Person& person,
        const std::string& program_) :
        Person(person), program(program_) {}
    */

    const std::string& GetProgram() const {
        return program;
    }

    virtual std::string ToString() const {
        std::ostringstream os; // print on string
        os << "Student ";
        ToStream(os);
        os << " " << program;
        return os.str(); // return the string in the stream
    }

    virtual bool ToFile(const std::string& filename) const {
        std::ofstream of(filename);
        if (!of.good()) {
            std::cerr << "Can not open " << filename << std::endl;
            return false;
        }
        of << "Student ";
        ToStream(of);
        of << " " << program << std::endl;
        return true;
    }
    virtual ~Student() { }
}; // end Student


class Researcher : public Person {
 protected:
    std::string research_topics;

 public:
    Researcher(
        const std::string& name_,
        const std::string& country_of_citizenship_,
        const std::string& research_topics_) :
        Person(name_, country_of_citizenship_), research_topics(research_topics_) {}
    
    const std::string& GetResearchTopics() const {
        return research_topics;
    }

    virtual std::string ToString() const {
        std::ostringstream os;
        os << "Researcher ";
        ToStream(os);
        os << " " << research_topics;
        return os.str();
    }

    virtual bool ToFile(const std::string& filename) const {
        std::ofstream of(filename);
        if (!of.good()) {
            std::cerr << "Can not open " << filename << std::endl;
            return false;
        }
        of << "Researcher ";
        ToStream(of);
        of << " " << research_topics << std::endl;
        return true;
    }
    virtual ~Researcher() { }
}; // end Researcher


class Teacher : public Researcher {
 protected:
    /*
    int num_courses = 0;
    std::string* course = nullptr;
    */
    std::string course;

 public:
    Teacher(
        const std::string& name_,
        const std::string& country_of_citizenship_,
        const std::string& research_topics_,
        /* const int num_courses_, const std::string* courses_ */
        const std::string& course_) : 
        Researcher(name_, 
            country_of_citizenship_, research_topics_), 
            /* num_courses(num_courses_), courses(courses_) */
            course(course_) {}

    const std::string& GetCourse() const {
        return course;
    }

    virtual std::string ToString() const {
        std::ostringstream os;
        os << "Teacher ";
        ToStream(os);
        os << " " << course;
        /*
        os << name << " " << country_of_citizenship;
        os << " " << num_courses;
        for (int i = 0 ; i < num_courses: i++) {
            os << " " << courses[i];
        }
        */
        return os.str();
    }

    virtual bool ToFile(const std::string& filename) const {
        std::ofstream of(filename);
        if (!of.good()) {
            std::cerr << "Can not open " << filename << std::endl;
            return false;
        }
        of << "Teacher ";
        ToStream(of);
        of << " " << research_topics << " " << course << std::endl;
        return true;
    }

    virtual ~Teacher() { }
}; // end Teacher


/*
g++ -o university university.cc
./university [RESEARCHER, STUDENT, TEACHER] [filename]
argv[0] = "./university"
argv[1] = [RESEARCHER, STUDENT, TEACHER];
argv[2] = filename;
*/


int main(int argc, char** argv) {

    PersonBase* person = nullptr;

    // have at least the name of the program and the person to build
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [Researcher, Student, Teacher] [filename]\n";
        return 2;
    }

    const std::string person_type(argv[1]);

    /*
    Person does not implement the interface
    so it cannot be instantiated 

    if (person_type == "Person") {
        person = new Person("Mario_Rossi", "SanMarino");
    } else */ if (person_type == "Researcher") {
        person = new Researcher(
            "Mario_Rossi", "SanMarino", "Informatica");
    } else if (person_type == "Student") {
        person = new Student(
            "Mario_Rossi", "SanMarino", "Ingegneria");
    } else if (person_type == "Teacher") {
        person = new Teacher(
            "Mario_Rossi", "SanMarino", "Informatica", "PPS");
    } else {
        std::cerr << "I can not build class " << person_type;
        return 1;
    }

    // usage
    const std::string person_str = person->ToString();
    std::cout << "Person is " << person_str << std::endl;

    /*
    ./university Student university.txt
    */

    if (argc > 2) {
        // argv[2] is filename
        person->ToFile(argv[2]);
    }

    // destructor
    if (person != nullptr) {
        delete person;
    }
    
    return 0;
}