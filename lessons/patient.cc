#include <set>
#include <string>
#include <iostream>

class Patient {
 private:
    std::string age;
    std::string name;

 public:
    // default constructor
    Patient(const std::string& age_, const std::string& name_) :
    age(age_), name(name_) { }

    // getters
    inline const std::string& GetAge() const {
        return age;
    }
    inline const std::string& GetName() const {
        return name;
    }
};

// comparator to compare two patients
struct Cmp {
    bool operator()(const Patient& a, const Patient& b) const {
        if (a.GetAge() == b.GetAge()) {
            if (a.GetName() < b.GetName()) {
                return true;
            } else {
                return false;
            }
        } else if (a.GetAge() > b.GetAge()) {
            return true;
        } else {
            return false;
        }
    }
};

// operator to print a patient
inline std::ostream& operator<<(std::ostream& os, const Patient& p) {
    os << p.GetName() << ": " << p.GetAge() << " years old";
    return os;
}

class Clinic {
 private:
    std::set<Patient, Cmp> patients;

 public:
    Clinic() { }

    inline std::set<Patient, Cmp> GetPatients() {
        return patients;
    }

    void AddPatient(const Patient& p) {
        patients.insert(p);
    }
};


int main() {

    Clinic c;
    int choice;
    std::string age;
    std::string name;

    while (true) {
        std::cout << std::endl;
        std::cout << "1. Enter a patient \n";
        std::cout << "2. View the waiting list \n";
        std::cout << "Enter choice (press 0 to exit): ";
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            std::cout << "Enter name and age of patient: ";
            std::cin >> name >> age;
            Patient p(age, name);
            c.AddPatient(p);
        } else if (choice == 2) {
            std::cout << "Patients in the clinic" << std::endl;
            for (const Patient& patient : c.GetPatients()) {
                std::cout << patient << std::endl;
            }
        } else {
            std::cout << "Choice is invalid" << std::endl;
        }
    }
    return 0;
}