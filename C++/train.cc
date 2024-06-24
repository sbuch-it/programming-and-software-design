#include <set>
#include <string>
#include <vector>
#include <iostream>

class Train {
 private:
    std::string code;
    std::string departure_station;
    std::string arrival_station;
    float langitude;
    float longitude;

 public:
    // default constructor
    Train(
    const std::string& code_,
    const std::string& departure_station_,
    const std::string& arrival_station_,
    float langitude_, float longitude_
    ) :
    code(code_),
    departure_station(departure_station_),
    arrival_station(arrival_station_),
    langitude(langitude_), longitude(longitude_) { }

    // getters
    inline const std::string& GetCode() const {
        return code;
    }
    inline const std::string& GetDepartureStation() const {
        return departure_station;
    }
    inline const std::string& GetArrivalStation() const {
        return arrival_station;
    }
    inline float GetLangitude() const {
        return langitude;
    }
    inline float GetLongitude() const {
        return longitude;
    }
};


class TrainManagement {
 private:
    std::vector<Train> trains;

 public:
    void AddTrain(const Train& train);
    Train GetTrainByCode(const std::string& code);
    std::set<std::string> GetCodes() const;

    // class Iterator
    class ConstIterator {
     private:
        unsigned int index = 0;
        const TrainManagement* tm = nullptr;

     public:
        inline ConstIterator(const TrainManagement& tm_) :
        tm(&tm_) { }
        inline Train GetNext() {
            const Train t = tm->trains[index];
            index++;
            return t;
        }
        inline bool HasNext() const {
            return index < tm->trains.size();
        }
    };
    friend class ConstIterator;
};

void TrainManagement::AddTrain(const Train& train) {
    trains.push_back(train);
}

Train TrainManagement::GetTrainByCode(const std::string& code) {
    Train t("0", "NULL", "NULL", 0.0, 0.0);
    for (const Train train : trains) {
        if (train.GetCode() == code) {
            return train;
        }
    }
    return t;
}

std::set<std::string> TrainManagement::GetCodes() const {
    std::set<std::string> codes;
    for (const Train& train : trains) {
        codes.insert(train.GetCode());
    }
    return codes;
}


int main() {
    
    TrainManagement tm;

    Train t1("A01", "Siena", "Firenze", 43.62, 11.18);
    tm.AddTrain(t1);

    Train t2("B03", "Firenze", "Siena", 43.38, 11.27);
    tm.AddTrain(t2);

    Train t3("B02", "Firenze", "Siena", 43.69, 11.21);
    tm.AddTrain(t3);

    float langitude;
    float longitude;

    std::cout << "Position of trains by increasing code \n";
    const std::set<std::string> codes = tm.GetCodes();
    for (const std::string& code : codes) {
        std::cout << "Train: " << code << " - ";
        langitude = tm.GetTrainByCode(code).GetLangitude();
        longitude = tm.GetTrainByCode(code).GetLongitude();
        std::cout << "Position: " << langitude << ", " << longitude;
        std::cout << std::endl;
    }

    std::cout << "\n Train list" << std::endl;
    TrainManagement::ConstIterator iter(tm);
    while (iter.HasNext()) {
        const Train t = iter.GetNext();
        std::cout << "Train: " << t.GetCode() << " - ";
        std::cout << "From " << t.GetDepartureStation();
        std::cout << " to " << t.GetArrivalStation();
        std::cout << std::endl;
    }

    std::cout << std::endl;
    return 0;
}