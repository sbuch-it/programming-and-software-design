#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
    Person(
        const std::string& name_,
        const std::string& country_of_citizenship_) :
        name(name_), 
        country_of_citizenship(country_of_citizenship_) {}

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
    Student(
        const std::string& name_,
        const std::string& country_of_citizenship_,
        const std::string& program_) :
        Person(name_, country_of_citizenship_), program(program_) {}
    
    const std::string& GetProgram() const {
        return program;
    }

    virtual std::string ToString() const {
        std::ostringstream os;
        os << "Student ";
        ToStream(os);
        os << " " << program;
        return os.str();
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
        Person(name_, country_of_citizenship_), 
        research_topics(research_topics_) {}
    
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
    // int num_courses = 0;
    // std::string* course = nullptr;
    std::string course;

 public:
    Teacher(
        const std::string& name_,
        const std::string& country_of_citizenship_,
        const std::string& research_topics_,
        const std::string& course_) : 
        /* const int num_courses_, const std::string* courses_ */
        Researcher(name_, country_of_citizenship_, research_topics_), course(course_) {}
        /* num_courses(num_courses_), courses(courses_) */
    
    const std::string& GetCourse() const {
        return course;
    }

    virtual std::string ToString() const {
        std::ostringstream os;
        os << "Teacher ";
        ToStream(os);
        os << " " << course;
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


class Department {
 private:
    /*
    vector of pointers to base class, can store different types:
    Student, Researcher, etc.
    */
    std::vector<PersonBase*> people;

 public:
    // default constructor
    Department() { }

    // ownership transfer: take possession of the pointer
    void Add(PersonBase* person) {
        people.push_back(person); // copy of the pointer
    }

    // destructor
    ~Department() {
        // ownership within the class, must deallocate the class
        for (int i = 0; i < people.size(); ++i) {
            delete people[i]; // if Student -> ~Student, 
            // if Researcher -> ~Researcher ...
        }
        // automatic vector deallocation, is called ~vector()
    }
    
    friend std::ostream& operator<<(
        std::ostream& os, const Department& dip);
}; // end Department

std::ostream& operator<<(std::ostream& os, const Department& dip) {
    for (int i = 0; i < dip.people.size(); ++i) {
        os << dip.people[i]->ToString() << std::endl;
    }
    // C++11 pointer iteration
    /*
    for (const PersonBase* person : dip.people) {
        os << person->ToString() << std::endl;
    }
    */
    return os;
}


int main(int argc, char** argv) {

    Department dip;

    // Explicit cast insert to PersonBase
    PersonBase* person1 = new Researcher("Mario_Rossi", "SanMarino", "Informatica");
    dip.Add(person1);

    // Implicit cast insert to PersonBase
    dip.Add(new Student("Carlo_Rossi", "Italia", "Fisica"));
    dip.Add(new Student("Maria_Bianchi", "Svizzera", "Matematica"));
    dip.Add(new Teacher("Stefano_Melacci", "Italia", "Ingegneria", "PPS"));

    std::cout << dip;
    return 0;
}