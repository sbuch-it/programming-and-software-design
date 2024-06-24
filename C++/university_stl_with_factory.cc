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

    // Definition of the factory Method, DESIGN PATTERN.
    static PersonBase* Build(const std::string& def);
};

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
        name(name_), country_of_citizenship(country_of_citizenship_) {}
    
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
};

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
};

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
};

class Teacher : public Researcher {
 protected:
    std::string course;

 public:
    Teacher(
        const std::string& name_,
        const std::string& country_of_citizenship_,
        const std::string& research_topics_,
        const std::string& course_) :
        Researcher(name_, country_of_citizenship_, 
            research_topics_), course(course_) {}
    
    const std::string& GetCourse() const {
        return course;
    }

    virtual std::string ToString() const {
        std::ostringstream os;
        os << "Teacher ";
        ToStream(os);
        os << " " << research_topics << " " << course;
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
};


/* Definire una classe che definisce un Dipartimento come un
insieme di Persone (usa std::vector) */
class Department {
 private:
    // Vector of pointers to base class, can store different types: Student, Researcher, etc.
    std::vector<PersonBase*> people;
 public:
    Department() { }
    // Trasferimento ownership: prendi possesso del puntatore.
    void Add(PersonBase* person) {
        people.push_back(person);
    }
    ~Department() {
        // ownership interna alla classe, deve deallocare la classe.
        for (int i = 0; i < people.size(); ++i) {
            if (people[i] != nullptr) {
                delete people[i];  // -> Distruttore di Student, se e' ricercatore ~Researcher...
            }
        }
        // Distruzione vector automatica, viene chiamato ~vector()
    }
    friend std::ostream& operator<<(std::ostream& os, const Department& dip);

    class ConstIterator {
     private:
        unsigned int index = 0;
        const Department* dep = nullptr;

     public:
        inline ConstIterator(const Department& dep_) : dep(&dep_) { }
        inline const PersonBase* GetNext() {
            const PersonBase* p = dep->people[index];
            index++;
            return p;
        }
        inline bool HasNext() const {
            return index < dep->people.size();
        }
    };
    friend class ConstIterator;
};

// Student Nome Italia Informatica
// Researcher Nome Francia AI
// Teacher Nome Italia AI PPS
std::ostream& operator<<(std::ostream& os, const Department& dip) {
    for (int i = 0; i < dip.people.size(); ++i) {
        os << dip.people[i]->ToString() << std::endl;
    }
    return os;
}

PersonBase* PersonBase::Build(const std::string& def) {
    std::istringstream is(def);
    std::string type;
    is >> type;
    std::string name;
    std::string citizenship;
    is >> name >> citizenship;

    if (type == "Student") {
        std::string program;
        is >> program;
        return new Student(name, citizenship, program);
    }

    if (type == "Researcher") {
        std::string reasearch_field;
        is >> reasearch_field;
        return new Researcher(name, citizenship, reasearch_field);
    }

    if (type == "Teacher") {
        std::string reasearch_field;
        std::string course;
        is >> reasearch_field >> course;
        return new Teacher(name, citizenship, reasearch_field, course);
    }

    std::cerr << "Not well defined Person from line" << def << std::endl;
    return nullptr;
};

std::istream& operator>>(std::istream& is, Department& dip) {
    std::string line;
    while (getline(is, line)) {
        PersonBase* person = PersonBase::Build(line);
        dip.Add(person);
    }
    return is;
}

// g++ -o university_stl university_stl.cc
int main(int argc, char** argv) {
    Department dip;

    // Inserimento con cast esplicito a PersonBase.
    PersonBase* person1 = new Researcher("Mario_Rossi", "SanMarino", "Informatica");
    dip.Add(person1);
    // Inserimento con cast implicito a PersonBase.
    dip.Add(new Student("Carlo_Rossi", "Italia", "Fisica"));
    dip.Add(new Student("Maria_Bianchi", "Svizzera", "Matematica"));
    dip.Add(new Teacher("Stefano_Melacci", "Italia", "Ingegneria", "PPS"));

    std::cout << dip;

    std::ofstream of("department.txt");
    of << dip;
    of.close();  // forza la scrittura del file, altrimenti potrebbe essere buffered.

    Department dip1;
    std::ifstream is("department.txt");
    is >> dip1;
    std::cout << "\nRead Department from file\n" << dip1;

    Department::ConstIterator iter(dip1);
    float num_stud = 0.0f;
    float num_teac = 0.0f;
    while (iter.HasNext()) {
        const PersonBase* p = iter.GetNext();
        if (p->ToString().substr(0, 3) == "Stu") {
            num_stud++;
        } else if (p->ToString().substr(0, 3) == "Tea") {
            num_teac++;
        }
        // std::cout << p->ToString() << std::endl;
    }
    std::cout << "Ratio student to teacher " << num_stud / num_teac << std::endl;

    return 0;
}