#include<deque>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>

class Person {
 protected:
    float salary = 0.0f;
    int num_paychecks = 0;
 public:
    Person(const float salary_, const int num_paychecks_) :
      salary(salary_), num_paychecks(num_paychecks_) { }
    inline float GetSalary() const {
        return salary;
    }
    virtual std::string ToString() const = 0;
    virtual ~Person() { }
};

class Engineer : public Person {
 protected:
    std::string project;

 public:
    Engineer(const float salary_, const int num_paychecks_, const std::string& project_) :
      Person(salary_, num_paychecks_), project(project_) { }
    virtual std::string ToString() const {
        std::ostringstream os;
        os << "ENGINEER " << salary << " " << num_paychecks;
        os << " " << project << " " << std::endl;
        return os.str();
    }
    virtual ~Engineer() { }
};

class Admin : public Person {
 protected:
    int code;
 public:
    Admin(const float salary_, const int num_paychecks_, const int code_) :
        Person(salary_, num_paychecks_), code(code_) { }
    virtual std::string ToString() const {
        std::ostringstream os;
        os << "ADMIN " << salary << " " << num_paychecks << " " << code << " " << std::endl;
        return os.str();
    }
    virtual ~Admin() { }
};

class EmployeeFactory {
 public:
    // type=ENGINEER def="2000 14 software"
    static Person* Build(const std::string& employee_type, const std::string& def) {
        std::istringstream is(def);
        float salary = 0.0f;
        int num_paychecks = 0;
        if (!(is >> salary >> num_paychecks)) {
            std::cerr << " ...";
            return nullptr;
        }
        if (employee_type == "ADMIN") {
            int code;
            if (!(is >> code)) {
                std::cerr << "..."; return nullptr;
            }
            return new Admin(salary, num_paychecks, code);
        } else if (employee_type == "ENGINEER") {
            std::string project;
            if (!(is >> project)) {
                std::cerr << "..."; return nullptr;
            }
            return new Engineer(salary, num_paychecks, project);
        }
        std::cerr << "...";
        return nullptr;
    }
};

class EmployeeManagement {
 private:
    std::deque<Person*> employees;

 public:
    bool ToFile(const std::string& filename) const {  // or operator<<
        std::ofstream of(filename);
        if (!of.good()) {
            std::cerr << "...";
            return false;
        }
        for (const Person* p : employees) {
            of << p->ToString();
        }
        return true;
    }
    void AddEmployee(Person* employee) {
        employees.push_back(employee);
    }
    float MonthlyCost() const {
        float sum = 0.0f;
        for (const Person* p : employees) {
            sum += p->GetSalary();
        }
        return sum;
    }
    ~EmployeeManagement() {
        for (Person* p : employees) {
            delete p;
        }
    }
};

// NON METTETELO NEL COMPITO NON MI INTERESSA
int main() {
    EmployeeManagement em;
    em.AddEmployee(EmployeeFactory::Build("ADMIN", "1500 13 100"));
    em.AddEmployee(EmployeeFactory::Build("ADMIN", "1600 13 100"));
    em.AddEmployee(EmployeeFactory::Build("ENGINEER", "2200 13 software"));
    em.AddEmployee(EmployeeFactory::Build("ENGINEER", "2300 14 design"));
    std::cout << em.MonthlyCost() << std::endl;
    em.ToFile("employees.txt");
    return 0;
}