#include <string>
#include <iostream>
#include <set>
#include <vector>

class Date {
 private:
    int day = 0;
    int month = 0;
    int year = 0;
    bool valid = true;

 public:
    // Costruttore
    Date() : valid(false) { }

    Date(const int day_, const int month_, const int year_) :
    day(day_), month(month_), year(year_) {
        if (month < 1 || month > 13 || year < 1900 || day < 1 || day > 31) {
            valid = false;
            return;
        }
        if (month == 2 && year % 4 == 0 && day > 29) {
            valid = false;
            return;
        } 
        if (month == 2 && year % 4 != 0 && day > 28) {
            valid = false;
            return;
        }
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            valid = false;
            return;
        }
    }
    
    // Getters
    inline int GetDay() const {
        return day;
    }
    inline int GetMonth() const {
        return month;
    }
    inline int GetYear() const {
        return year;
    }
    inline bool GetValid() const {
        return valid;
    }
};  // End Date

// Operatori per confrontare due date
inline bool operator<(const Date& a, const Date& b) {
    if (a.GetYear() != b.GetYear()) {
        return a.GetYear() < b.GetYear();
    }
    if (a.GetMonth() != b.GetMonth()) {
        return a.GetMonth() < b.GetMonth();
    }
    return a.GetDay() < b.GetDay();
}
inline bool operator==(const Date& a, const Date& b) {
    return (a.GetYear() == b.GetYear() && 
        a.GetMonth() == b.GetMonth() && 
        a.GetDay() == b.GetDay());
}

// Operatore per stampare le date in modo compatto
inline std::ostream& operator<<(std::ostream& os, const Date& a) {
    os << a.GetDay() << "/" << a.GetMonth() << "/" << a.GetYear() << std::endl;
    return os;
}

class Student {
 private:
    std::string name;
    Date date;

 public:
    // Default costructor
    Student() { }
    // Costructor with parameters
    Student(const std::string& name_, const Date& date_) : name(name_), date(date_) { }

    // Getters
    inline const std::string& GetName() const {
        return name;
    }
    inline const Date& GetDate() const {
        return date;
    }
};

// Comparatore per ordinare gli studenti per data
struct Cmp {
    bool operator()(const Student& a, const Student& b) const {
        if (a.GetDate() == b.GetDate()) {
            return a.GetName() < b.GetName();
        }
        return a.GetDate() < b.GetDate();
    }
};

class University {
 private:
    std::set<Student, Cmp> students;  // Definire il comparatore

 public:
    University() { }
    void Add(const Student& student) {
        students.insert(student);
    }

    // Usando deque e includendo #include <deque>
    /*
    std::deque<Date> GetDates() const {
        std::deque<Date> dates;
        for (const Student& student : students) {
            dates.push_back(student.GetDate());
        }
        return dates;
    }
    */

    // Usando vector, preferibile perché conosco
    // il numero di studenti ed è più veloce la ricerca
    std::vector<Date> GetDates() const {
        std::vector<Date> dates;
        dates.reserve(students.size());
        for (const Student& student : students) {
            dates.push_back(student.GetDate());
        }
        return dates;
    }
};

int main() {
    University students;

    Student s1("Mario Rossi", Date(1, 1, 2000));
    Student s2("Maria Bianchi", Date(1, 3, 1997));
    Student s3("Mario Carli", Date(1, 3, 2001));
    Student s4("Jose Ibanez", Date(23, 3, 1999));

    students.Add(s1);
    students.Add(s2);
    students.Add(s3);
    students.Add(s4);

    const std::vector<Date> dates = students.GetDates();
    for (const Date& date : dates) {
        std::cout << date << std::endl;
    }
    return 0;
}