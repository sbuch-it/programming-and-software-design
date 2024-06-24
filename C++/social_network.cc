#include <set>
#include <string>
#include <vector>
#include <iostream>

class Account {
 protected:
    std::string name;
    int followers;
    int post;

 public:
    Account(const std::string& name_, int followers_, int post_) :
    name(name_), followers(followers_), post(post_) { }

    inline const std::string& GetName() const {
        return name;
    }
    inline int GetFollowers() const {
        return followers;
    }
    inline int GetPost() const {
        return post;
    }
};

class AccountPerson : public Account {
 protected:
    std::string phone;

 public:
    AccountPerson(const std::string& name_, int followers_,
    int post_, const std::string& phone_) : 
    Account(name_, followers_, post_), phone(phone_) { }

    inline const std::string& GetPhone() const {
        return phone;
    }
};

class AccountCompany : public Account {
 protected:
    std::string IVA;

 public:
    AccountCompany(const std::string& name_, int followers_,
    int post_, const std::string& IVA_) : 
    Account(name_, followers_, post_), IVA(IVA_) { }
};


class SocialNetwork {
 private:
    std::vector<Account> accounts;

 public:
    SocialNetwork() { }

    void Add(Account account) {
        accounts.push_back(account);
    }

    void Order() {
        std::set<int, std::greater<int>> posts;
        for (int i = 0; i < accounts.size(); i++) {
            posts.insert(accounts[i].GetPost());
        }
        for (auto iter = posts.begin(); iter != posts.end(); iter++) {
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].GetPost() == *iter) {
                    std::cout << accounts[i].GetName() << std::endl;
                }
            }
        } 
    }

    void Print() {
        for (int i = 0; i < accounts.size(); i++) {
            std::cout << "\n Name: " << accounts[i].GetName();
            std::cout << std::endl;
            std::cout << "Followers: " << accounts[i].GetFollowers();
            std::cout << " - Post: " << accounts[i].GetPost();
            std::cout << std::endl;
        }
    }
    
};

int main() {

    SocialNetwork sn;

    AccountPerson ap1("Mario", 5, 10, "+39 12345");
    AccountPerson ap2("Luca", 6, 500, "+39 54321");
    sn.Add(ap1);
    sn.Add(ap2);

    AccountCompany ac1("A", 2000, 500, "25FEG");
    AccountCompany ac2("B", 300, 4000, "94JVS");
    sn.Add(ac1);
    sn.Add(ac2);

    std::cout << "Account name ordered by posts number" << std::endl;
    sn.Order();
    std::cout << std::endl;

    sn.Print();

    std::cout << std::endl;

    return 0;
}