#include <deque>
#include <iostream>
#include <string>

class MeteoStation;  // Forward declaration dell'osservato.

// Prototipo dell'osservante.
class MeteoObserver {
 protected:
    std::string name;
 public:
    MeteoObserver(const std::string& name_) : name(name_) { }
    virtual void Update(const MeteoStation* station) = 0;
};

// classe osservata
class MeteoStation {
 public:
    MeteoStation() { }
    void AddObserver(MeteoObserver* observer) {
        observers.push_back(observer);
    }

    inline float GetTemp() const {
        return temp;
    }
    inline float GetPressure() const {
        return pressure;
    }
    void SetData(float temp_, float pressure_) {
        pressure = pressure_;
        if (std::abs(temp - temp_) > 3.0f) {
            temp = temp_;
            Notify();
        } else {
            temp = temp_;
        }
    }

 private:
    float temp = 0.0f;
    float pressure = 0.0;
    void Notify() {
        for (MeteoObserver* observer : observers) {
            observer->Update(this);
        }
    }
    // lista di osservanti
    std::deque<MeteoObserver*> observers;
};

// classe con implementazione dell'osservante
class MeteoFanatic : public MeteoObserver {
 public:
    MeteoFanatic(const std::string& name_) : MeteoObserver(name_) { }
    virtual void Update(const MeteoStation* station) {
        std::cout << name << " " << station->GetTemp();
        std::cout << " " << station->GetPressure() << std::endl;
    }
};

int main() {
    MeteoStation s;
    MeteoFanatic mf("Carlo Rossi");
    s.AddObserver(&mf);
    MeteoFanatic mf1("Carla Bianchi");
    s.AddObserver(&mf1);

    s.SetData(5.3, 1023.2);
    s.SetData(5.4, 1023.2);
    s.SetData(10.3, 1023.2);
    return 0;
}