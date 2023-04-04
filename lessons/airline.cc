#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

class Airline {
 private:
    // people: Set di persone
    typedef std::set<std::string> People;
    // volo -> people
    typedef std::map<std::string, People> Fligth2People;
    Fligth2People fligth2people;

    // oppure
    // std::map<std::string, std:set<std::string> fligth2people;

 public:
    // Costruttore
    Airline(const std::string& filename);
    inline bool Good() const {
        return fligth2people.size() > 0;
    }
    bool Search(const std::string& flight, const std::string& name) const;
};


Airline::Airline(const std::string& filename) {
    std::ifstream is(filename);
    if (!is.good()) {
        std::cerr << "Can not load the airline data \n";
        return;
    }

    std::string flight;
    std::string name;
    while (is >> flight && std::getline(is, name)) {
        if (name.length() > 0) {
            name = name.substr(1);
        }
        fligth2people[flight].insert(name);
    }
}


bool Airline::Search(const std::string& flight, const std::string& name) const {
    Fligth2People::const_iterator iter_flight = fligth2people.find(flight);
    // auto iter_flight = fligth2people.find(flight);

    if (iter_flight == fligth2people.end()) {
        return false;
    }

    const People& people = iter_flight -> second;
    // const auto& people iter_flight -> second;

    if (people.find(name) == people.end()) {
        return false;
    }
    return true;
}

int main() {
    const Airline airline("airline.txt");
    if (!airline.Good()) {
        std::cerr << "Can not load airline data \n";
        return 1;
    }

    const bool found1 = airline.Search("AZ1000", "Carla Bianchi");
    std::cout << "Carla Bianchi AZ1000 " << (found1 ? "YES" : "NO") << std::endl;
    const bool found2 = airline.Search("AZ1001", "Topolino Bianchi");
    std::cout << "Topolino Bianchi AZ1001 " << (found2 ? "YES" : "NO") << std::endl;

    return 0;
}