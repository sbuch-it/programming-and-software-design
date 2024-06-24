/*
Un comune toscano vuole mettere a disposizione di cittadini e turisti delle biciclette. Realizzare una classe per la loro gestione. Ogni bici e’ identificata da un codice ed e’ associata al codice fiscale della persona che al momento la noleggia, oltre che ad una lista di interventi di manutenzione (“cambio ruota”, “sostituzione catena”, ecc.). Realizzare una classe che permetta di:
• noleggiare una bici (associandola ad una persona);
• aggiornare la lista di manutenzioni effettuate;
• stampare l’elenco delle bici disponibili (non assegnate a qualcuno); • stampare le bici in ordine numero di interventi effettuati;
*/

#include <map>
#include <list>
#include <string>
#include <vector>
#include <iostream>

class Bike {
 private:
    std::string code;
    std::string fiscal_code = "NULL";
    std::list<std::string> maintenance;

 public:
    Bike(const std::string& code_) : code(code_) { }

    // getters
    inline const std::string& GetCode() const {
        return code;
    }
    inline const std::string& GetFiscalCode() const {
        return fiscal_code;
    }
    inline const std::list<std::string>& GetMaintenance() const {
        return maintenance;
    }

    // setter
    inline void SetFiscalCode(const std::string& fiscal_code_) {
        fiscal_code = fiscal_code_;
    }
    inline void SetMaintenance(const std::string& maintenance_) {
        maintenance.push_back(maintenance_);
    }
};


class BikeRental {
 private:
    typedef std::vector<Bike> Bicycles;
    Bicycles bicycles;

 public:
    
    void AddBike(const std::string& code);

    void Rental(
    const std::string& code_, const std::string& fiscal_code_);

    void AddMaintenance(
    const std::string& code_, const std::string& m);

    void PrintAvailable();

    void PrintMaintenance();

};

void BikeRental::AddBike(const std::string& code) {
    Bike b(code);
    bicycles.push_back(b);
}

void BikeRental::Rental(
const std::string& code_, const std::string& fiscal_code_) {
    for (Bike& b : bicycles) {
        if (b.GetCode() == code_) {
            b.SetFiscalCode(fiscal_code_);
        }
    }
}

void BikeRental::AddMaintenance(
const std::string& code_, const std::string& m) {
    for (Bike& b : bicycles) {
        if (b.GetCode() == code_) {
            b.SetMaintenance(m);
        }
    }
}

void BikeRental::PrintAvailable() {
    for (Bike& b : bicycles) {
        if (b.GetFiscalCode() == "NULL") {
            std::cout << b.GetCode() << std::endl;
            std::cout << "Maintenance:" << std::endl;

            std::list<std::string>::const_iterator iter = b.GetMaintenance().begin();
            for (; iter != b.GetMaintenance().end(); iter++) {
                std::cout << *iter << std::endl;
            }
            std::cout << std::endl;
        }  
    }
    std::cout << std::endl << std::endl;
}

void BikeRental::PrintMaintenance() {
    std::map<int, std::vector<Bike>> m;

    // FINIRE
    // from text_analysis
}


int main() {
    BikeRental br;
    br.AddBike("A01");
    br.AddBike("A02");

    br.PrintAvailable();

    br.Rental("A01", "BLL35");

    br.PrintAvailable();

    br.AddMaintenance("A02", "wheel change");
    br.AddMaintenance("A02", "chain replacement");

    br.PrintAvailable();

    br.PrintMaintenance();

    std::cout << std::endl;
    return 0;
}
