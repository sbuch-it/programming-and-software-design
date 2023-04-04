#include <string>
#include <iostream>

class Date {
 private:
    int day = 0;
    int month = 0;
    int year = 0;
    bool valid = false;

 public:
    // default costructor
    Date() { }
    // constructor with parameters
    Date(const int day_, const int month_, const int year_) {
        day = day_;
        month = month_;
        year = year_;

        if (month < 1 || month > 13 || year < 1900 ||
            day < 1 || day > 31) {
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
        if ((month == 4 || month == 6 || month == 9 ||
            month == 11) && day > 30) {
            valid = false;
            return;
        }
        valid = true;
    }
    
    // getters
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
}; // end Date


inline bool operator<(const Date& d1, const Date& d2) {
    if (!d1.GetValid() || !d2.GetValid()) {
        return false;
    }
    if (d1.GetYear() != d2.GetYear()) {
        return d1.GetYear() < d2.GetYear();
    }
    if (d1.GetMonth() != d2.GetMonth()) {
        return d1.GetMonth() < d2.GetMonth();
    }
    return d1.GetDay() < d2.GetDay();
}

inline bool operator>(const Date& d1, const Date& d2) {
    if (!d1.GetValid() || !d2.GetValid()) {
        return false;
    }
    return d2 < d1;
}

inline bool operator==(const Date& d1, const Date& d2) {
    return (d1.GetYear() == d2.GetYear() &&
            d1.GetMonth() == d2.GetMonth() &&
            d1.GetDay() == d2.GetDay());
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.GetDay() << " " << d.GetMonth() << " " << d.GetYear();
    os << std::endl;
    return os;
}


class Person {
 private:
    std::string name;
    std::string surname;
    std::string address;
    Date born_date;

 public:
    // default costructor
    Person() { }
    // costructor with parameters
    Person(const std::string& name_, const std::string& surname_,
        const std::string& address_, const Date& born_date_) { 
            name = name_;
            surname = surname_;
            address = address_;
            born_date = born_date_;
    }
  
    // getters
    inline const std::string& GetName() const {
        return name;
    }
    inline const std::string& GetSurname() const {
        return surname;
    }
    inline const std::string& GetAddress() const {
        return address;
    }
    inline const Date& GetBornDate() const {
        return born_date;
    }
}; // end Person


inline std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.GetName() << " " << p.GetSurname() << " ";
    os << p.GetAddress() << " " << p.GetBornDate();
    return os;
}

inline std::istream& operator>>(std::istream& in, Person& p) {
    std::string name;
    std::string surname;
    std::string address;
    int day;
    int month;
    int year;

    in >> name >> surname >> address >> day >> month >> year;

    Date d(day, month, year);

    while (!d.GetValid()) {
        in >> name >> surname >> address >> day >> month >> year;
    }

    return in;
}

inline bool operator==(const Person& p1, const Person& p2) {
    return (p1.GetName() == p2.GetName() &&
        p1.GetSurname() == p2.GetSurname() &&
        p1.GetAddress() == p2.GetAddress() &&
        p1.GetBornDate() == p2.GetBornDate());
}


class People {
 private:
    int num_people = 0;
    Person* people = nullptr;
 
 public:
    // constructor with parameters
    People(const int num_people_) {
        num_people = num_people_;
        if (num_people > 0) {
            people = new Person[num_people_];
        } else {
            std::cerr << "Wrong num_people \n";
        }
    }

    inline const Person& GetPerson(const int i) const { 
        return people[i];
    }

    bool SetPerson(const Person& p, const int i) {
        if (i < 0 || i >= num_people) {
            return false;
        }
        people[i] = p;
        return true;
    }

    Person Oldest() const {
        if (num_people < 1) {
            return Person();
        }
        Person oldest = people[0];
        for (int i = 1; i < num_people; ++i) {
            if (people[i].GetBornDate() < oldest.GetBornDate()) {
                oldest = people[i];
            }
        }
        return oldest;
    }

    ~People() {
        if (people != nullptr)
            delete[] people;
    }
}; // end People


int main() {
    Person p1("Mario", "Rossi", "Via Roma 56", Date(26, 3, 1923));
    Person p2("Mario", "Bianchi", "Via Roma 56", Date(26, 8, 1923));
    Person p3("Franca", "Rossi", "Via Roma 54", Date(26, 8, 1933));

    People people(3);

    people.SetPerson(p1, 0);
    people.SetPerson(p2, 1);
    people.SetPerson(p3, 2);

    std::cout << "Person 0 is " << people.GetPerson(0);
    std::cout << "Oldest is " << people.Oldest();
    
    return 0;
}