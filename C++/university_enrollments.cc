#include <string>
#include <fstream>
#include <iostream>

class Student {
 private:
    std::string name;
    std::string surname;
    std::string course;

 public:
    Student() { }
    Student(const std::string name_, 
        const std::string surname_, std::string course_)
    {
        name = name_;
        surname = surname_;
        course = course_;
    }

    inline const std::string& GetName() const{
        return name;
    }
    inline const std::string& GetSurname() const {
        return surname;
    }
    inline const std::string& GetCourse() const {
        return course;
    }
}; // end Student


std::ostream& operator<<(std::ostream& os, const Student& s){
    os << s.GetName() << " " << s.GetSurname() << " ";
    os << s.GetCourse() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    std::string name;
    std::string surname;
    std::string course;
    
    is >> name >> surname >> course;
    return is;
}


class University {
 private:
    int num_students = 0;
    Student* students = nullptr;

 public:
    University(const int num_students_) {
        num_students = num_students_;
        if (num_students > 0) {
            students = new Student[num_students];
        } else {
            std::cerr << "Error" << std::endl;
        }
    }

    ~University() {
        if (students != nullptr) {
            delete[] students;
        }
    }

    void SetStudent(const Student& s, const int i) {
        students[i] = s;
    }

    bool Enrolled(const std::string& name, 
        const std::string& surname)
    {
        for (int i = 0; i < num_students; i++) {
            if (students[i].GetName() == name &&
                students[i].GetSurname() == surname)
            {
                return true;
            }
        }
        return false;
    }

    int Course(const std::string& course) {
        int num = 0;
        for (int i = 0; i < num_students; i++) {
            if (students[i].GetCourse() == course) {
                num++;
            }
        }
        return num;
    }

    friend std::ostream& operator<<(
        std::ostream& os, const University& u);
    friend std::istream& operator>>(
        std::istream& is, University& u);
}; // end University


std::ostream& operator<<(std::ostream& os, const University& u){
    os << u.num_students << std::endl;
    for (int i = 0; i < u.num_students; i++) {
        os << u.students[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, University& u) {
    int num_students = 0;
    is >> num_students;
    Student* students = new Student[num_students];
    for (int i = 0; i < u.num_students; i++) {
        is >> u.students[i];
    }
    return is;
}


int main() {

    Student s0("Mario", "Rossi", "Ingegneria_Informatica");
    Student s1("Luca", "Bianchi", "Ingegneria_Aerospaziale");
    Student s2("Andrea", "Neri", "Ingegneria_Gestionale");
    Student s3("Antonio", "Giallo", "Ingegneria_Informatica");
    Student s4("Francesco", "Verde", "Ingegneria_Aerospaziale");
    Student s5("Federico", "Blu", "Ingegneria_Informatica");
    Student s6("Roberto", "Marrone", "Ingegneria_Gestionale");

    std::cout << "Students are" << std::endl;
    std::cout << s0 << s1 << s2 << s3 << s4 << s5 << s6 << std::endl;

    University uni(7);

    uni.SetStudent(s0, 0);
    uni.SetStudent(s1, 1);
    uni.SetStudent(s2, 2);
    uni.SetStudent(s3, 3);
    uni.SetStudent(s4, 4);
    uni.SetStudent(s5, 5);
    uni.SetStudent(s6, 6);

    std::ofstream of("university_enrollments.txt");
    if(of.good()) {
        of << uni;
    }

    std::ifstream ifs("university_enrollments.txt");
    if(ifs.good()) {
        ifs >> uni;
    }

    if (uni.Enrolled("Mario", "Rossi")) {
        std::cout << "Mario Rossi is enrolled" << std::endl;
    } else {
        std::cout << "Mario Rossi is not enrolled" << std::endl;
    }

    std::cout << "Student of Ingegneria Informatica: ";
    std::cout << uni.Course("Ingegneria_Informatica") << std::endl;

    return 0;
}