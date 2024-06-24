#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Wine {
 private:
    int year;
    std::string name;
    std::string company;

 public:
    // default constructor
    Wine() { }
    Wine(int year_,
    const std::string& name_,
    const std::string& company_) :
    year(year_), name(name_), company(company_) { }

    // getters
    inline int GetYear() const {
        return year;
    }
    inline const std::string& GetName() const {
        return name;
    }
    inline const std::string& GetCompany() const {
        return company;
    }

    // friendship operator>>
    friend std::istream& operator>>(std::istream& is, Wine& w);
    friend std::ostream& operator<<(std::ostream& os, Wine& w);
};

std::istream& operator>>(std::istream& is, Wine& w) {
    is >> w.name >> w.company >> w.year;
    return is;
}

std::ostream& operator<<(std::ostream& os, Wine& w) {
    os << w.name << " (" << w.year << ") : " << w.company;
    return os;
}


class WineManagement {
 private:
    // producer -> wines
    typedef std::map<std::string, std::vector<Wine>> Wines;
    Wines wines;

 public:

    void AddWine(const Wine& w);
    void RemoveWine(Wine& w);
    Wine SearchWine(const std::string& name);

    class Iterator {
     private:
        const WineManagement* wm;
        Wines::const_iterator iter;
        int index = 0;

     public:
        Iterator(const WineManagement& wm_) : wm(&wm_), index(0) {
            iter = wm->wines.begin();
        }
        bool HasNext() const {
            return (iter != wm->wines.end());
        }
        const Wine& GetNext() {
            const std::vector<Wine>& wines = iter->second;
            const Wine& wine = wines[index];
            if (index < wines.size() - 1) {
                index++;
            } else {
                iter++;
                index = 0;
            }
            return wine;
        }
    };


    friend std::istream& operator>>(
    std::istream& is, WineManagement& wm);
};

std::istream& operator>>(std::istream& is, WineManagement& wm) {
    
    int num_wines = 0;
    is >> num_wines;

    if (num_wines <= 0) {
        std::cerr << "Can not read the wines \n";
        return is;
    }

    for (int i = 0; i < num_wines; i++) {
        Wine wine;
        is >> wine;
        wm.wines[wine.GetCompany()].push_back(wine);
    }
    return is;
}

void WineManagement::AddWine(const Wine& w) {
    wines[w.GetCompany()].push_back(w);
}

void WineManagement::RemoveWine(Wine& w) {

    for (int i = 0; i < wines[w.GetCompany()].size(); i++) {
      
        int year = wines[w.GetCompany()].at(i).GetYear();
        std::string name = wines[w.GetCompany()].at(i).GetName();
        std::string company = 
        wines[w.GetCompany()].at(i).GetCompany();

        if (year == w.GetYear() &&
        name == w.GetName() &&
        company == w.GetCompany())
        {
            wines[w.GetCompany()].erase(wines[w.GetCompany()].begin() + i);
        }
    }
}

Wine WineManagement::SearchWine(const std::string& name) {
    for (auto& iter : wines) {
        for (int i = 0; i < iter.second.size(); i++) {
            if (iter.second.at(i).GetName() == name) {
                return iter.second.at(i);
            }
        }
    }
    Wine wn(0, "NULL", "NULL");
    return wn;
}


int main() {
    WineManagement wm;

    std::ifstream is("wine.txt");
    if (!is.good()) {
        std::cerr << "Can not load data \n";
        return 1;
    }
    is >> wm;

    Wine wa(2017, "Viola", "C");
    wm.AddWine(wa);

    Wine wr(2012, "Bianco", "C");
    wm.RemoveWine(wr);

    std::cout << "Wines list" << std::endl;
    WineManagement::Iterator iter(wm);
    while (iter.HasNext()) {
        const Wine w = iter.GetNext();
        std::cout << "• " << w.GetName();
        std::cout << " (" << w.GetYear() << ") ";
        std::cout << "- Company: " << w.GetCompany();
        std::cout << std::endl;
    }

    Wine ws = wm.SearchWine("Verde");
    std::cout << std::endl << "Search: " << ws << std::endl;

    std::cout << std::endl;

    return 0;
}