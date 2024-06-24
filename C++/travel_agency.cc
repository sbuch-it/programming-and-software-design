#include <map>
#include <string>
#include <vector>
#include <iostream>

class Travel {
 private:
    std::string start_loc;
    std::string dest_loc;
    std::string start_date;
    std::string end_date;
    std::vector<std::string> travellers;

 public:
    // Travel(const std::string& filename) { ... }

    // getters
    inline const std::string& GetStartLoc() const {
        return start_loc;
    }
    inline const std::string& GetDestLoc() const {
        return dest_loc;
    }
    inline const std::string& GetStartDate() const {
        return start_date;
    }
    inline const std::string& GetEndDate() const {
        return end_date;
    }
    inline const std::vector<std::string>& GetTravellers() const {
        return travellers;
    }

    // check if travel is good
    inline bool Good() const {
        return (!start_loc.empty() && 
        !dest_loc.empty() && 
        !start_date.empty() && 
        !end_date.empty());
    }

    friend std::istream& operator>>(std::istream& is, Travel& v);
};

std::istream& operator>>(std::istream& is, Travel& v) {
    is >> v.start_loc >> v.dest_loc >> v.start_date >> v.end_date;

    int num_travellers = 0;
    is >> num_travellers;
    v.travellers.reserve(num_travellers);

    for (int i = 0; i < num_travellers; ++i) {
        std::string traveller;
        is >> traveller;
        v.travellers.push_back(traveller);
    }
    return is;
}


class TravelAgency {
 private:
    // destionation -> travels
    typedef std::map<std::string, std::vector<Travel> > TravelCont;
    TravelCont travels;

 public:
    // TravelAgency(const std::string& filename);

    std::vector<Travel> GetTravelsByDest(const std::string& dest) const {
        const auto iter = travels.find(dest);
        return (iter != travels.end() ? iter->second : std::vector<Travel>());
    }

    class Iterator {
     private:
        const TravelAgency* agency;
        TravelCont::const_iterator iter;
        int index = 0;

     public:
        Iterator(const TravelAgency& agency_) : agency(&agency_), index(0) {
            iter = agency->travels.begin();
        }
        bool HasNext() const {
            return (iter != agency->travels.end());
        }
        const Travel& GetNext() {
            const std::vector<Travel>& travels = iter->second;
            const Travel& travel = travels[index];
            if (index < travels.size() - 1) {
                index++;
            } else {
                iter++;
                index = 0;
            }
            return travel;
        }
    };

    friend std::istream& operator>>(
    std::istream& is, TravelAgency& agency);
};

std::istream& operator>>(std::istream& is, TravelAgency& agency) {
    int num_travels = 0;
    is >> num_travels;
    if (num_travels <= 0) {
        std::cerr << "Can not read the travels\n";
        return is;
    }
    for (int i = 0; i < num_travels; ++i) {
        Travel travel;
        is >> travel;
        if (!travel.Good()) {
            std::cerr << "Can not read travel\n";
            continue;
        }
        agency.travels[travel.GetDestLoc()].push_back(travel);
    }
    return is;
}