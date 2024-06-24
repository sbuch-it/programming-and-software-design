#include <iostream>
#include <fstream>
#include <string>

class Team {
 private:
    std::string name; // team name
    int num_win = 0; // matches won
    int num_lost = 0; // matches lost
    int num_drawn = 0; // matches drawn

 public:
    // default constructor
    Team() { }

    // costructor with parameters
    Team(const std::string& name_) { 
        name = name_;
    };

    // set name
    inline void SetName(const std::string& name_) {
        name = name_;
    }
    // get name
    inline const std::string& GetName() const {
        return name;
    }

    // setters
    inline void AddWin(){
        num_win++;
    }
    inline void AddLost(){
        num_lost++;
    }
    inline void AddDraw(){
        num_drawn++;
    }

    // getters
    inline int GetWin() const{
        return num_win;
    }
    inline int GetLost() const{
        return num_lost;
    }
    inline int GetDraw() const{
        return num_drawn;
    }
    inline int GetPoints() const{
        return 3 * num_win + num_drawn;
    }
}; // end Team


class Championship {
 private:
    int num_teams = 0;
    Team* teams = nullptr;

 public:
    // costructor with parameters
    Championship(const int num_teams_, const std::string* names_) {
        num_teams = num_teams_;
        if (num_teams > 0) {
            teams = new Team[num_teams];
        }
        for (int i = 0; i < num_teams; ++i) {
            teams[i].SetName(names_[i]);
        }
    }
    
    // destructor
    ~Championship() {
        if (teams != nullptr) {
            delete[] teams;
        }      
    }
    
    // method to add a result
    bool AddResult(
        const std::string& name1, 
        const std::string& name2, 
        const char result) {
        /* 1, x, 2 */
    
        if (name1 == name2) {
            std::cerr << "A team can not play against itself \n";
            return false;
        }
        
        // search the team indexes
        int index_name1 = -1;
        int index_name2 = -1;
        for (int i = 0; i < num_teams; ++i) {
            if (teams[i].GetName() == name1) {
                index_name1 = i;
            }
            if (teams[i].GetName() == name2) {
                index_name2 = i;
            }
            if (index_name1 != -1 && index_name2 != -1) {
                break;
            }    
        }

        if (index_name1 == -1 || index_name2 == -1) {
            std::cerr << "Can not find teams " << name1 << " or " << name2 << std::endl;
            return false;
        }

        // assign the results and therefore the points
        if (result == '1') {
            teams[index_name1].AddWin();
            teams[index_name2].AddLost();
        } else if (result == 'x') {
            teams[index_name1].AddDraw();
            teams[index_name2].AddDraw();
        } else if (result == '2') {
            teams[index_name1].AddLost();
            teams[index_name2].AddWin();
        } else {
            std::cerr << "Wrong result " << result << std::endl;
            return false;
        }
        return true;
    }
    
    void PrintStandings() const {
        for (int i = 0; i < num_teams; ++i) {
            std::cout << teams[i].GetName() << " -> " << teams[i].GetPoints() << std::endl;
        }
    }

    // friendship
    friend std::istream& operator>>(
        std::istream& is, Championship& c);
    friend std::ostream& operator<<(
        std::ostream& os, const Championship& c);

}; // end Championship


std::ostream& operator<<(std::ostream& os, const Championship& c) {
    os << c.num_teams;
    for (int i = 0; i < c.num_teams; ++i) {
        os << " " << c.teams[i].GetName();
    }
    return os;
}

std::istream& operator>>(std::istream& is, Championship& c) {
    int num_teams = 0;
    is >> num_teams;
    std::string* names = new std::string[num_teams];
    for (int i = 0; i < num_teams; ++i) {
        is >> names[i];
    }
    if (c.teams != nullptr)
        delete[] c.teams;
    c.num_teams = num_teams;
    c.teams = new Team[num_teams];
    for (int i = 0; i < num_teams; ++i) {
        c.teams[i].SetName(names[i]);
    }
    delete[] names;
    return is;
}


int main() {
    const int num_teams = 4;
    std::string* names = new std::string[num_teams];
    names[0] = "bologna";
    names[1] = "fiorentina";
    names[2] = "siena";
    names[3] = "juventus";

    Championship c(num_teams, names);
    c.AddResult("siena", "bologna", 'x');
    c.AddResult("bologna", "siena", '2');
    c.AddResult("bologna", "juventus", '1');
    c.AddResult("fiorentina", "juventus", '1');
    c.AddResult("siena", "colligiana", '1');
    c.AddResult("juventus", "fiorentina", '1');

    c.PrintStandings();
    std::ofstream of("championship.txt");
    of << c;

    delete[] names;
    return 0;
}