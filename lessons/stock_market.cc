#include <iostream>
#include <string>
#include <list>
using namespace std;

// classe osservata
class Stock {
 public:
    Stock(const string& symbol, double price) : 
        symbol_(symbol), price_(price) { }

    // + osservatore
    void Attach(InvestorBase* investor) {
        investors_.push_back(investor);
    }

    // - osservatore
    void Detach(InvestorBase* investor) {
        investors_.remove(investor);
    }

    double GetPrice() const {
        return price_;
    }
    void SetPrice(double price) {
        price_ = price;
        Notify(); // cambio stato, chiamo Notify()
    }

    const string& GetSymbol() const {
        return symbol_;
    }

 private:
    // notifica gli osservatori passandogli l'oggetto osservato
    void Notify() {
        list<InvestorBase*>::iterator it = investors_.begin();
        while (it != investors_.end()) {
            (*it)->Update(this);
            it++;
        }
    }
    string symbol_;
    double price_;
    list<InvestorBase*> investors_; // lista di osservanti
};

// classe osservante
class Investor : public InvestorBase {
 public:
    Investor(const string& name) : name_(name) { }
    void Update(const Stock* stock) {
        // riceve la notifica
        cout << "Notifica a" << name_ << "=>" << stock->GetSymbol();
        cout << stock->GetPrice() << endl;
    }

 private:
    string name_;
};

// il main
int main() {
    Stock c1("Ebay", 123.0);
    Investor* i1 = new Investor("Billy");
    c1.Attach(i1);
    cout << "Created investor Billy following Ebay" << endl;
    c1.SetPrice(125.0);
    Investor* i2 = new Investor("Timmy");
    c1.Attach();
    cout << "Created investor Timmy following Ebay" << endl;
    c1.SetPrice(145.0);
    c1.Detach(i1);
    cout << "Investor Billy not interested in Ebay anymore" << endl;
    c1.SetPrice(165.0);
    delete i1;
    delete i2;
    return 0
}