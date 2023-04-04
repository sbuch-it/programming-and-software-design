#include <ctime>
#include <string>
#include <cstdlib>
#include <iostream>

static const int num_seeds = 4;
static const int num_numbers = 10;

class Card {
 private:
    int number;
    std::string seed;
    bool drawn = false;

 public:
    Card() { }
    Card(int number_, const std::string& seed_){
        number = number_;
        seed = seed_;
    }

    inline int GetNumber() const {
        return number;
    }
    inline const std::string& GetSeed() const {
        return seed;
    }
    inline bool GetDrawn() const {
        return drawn;
    }

    inline void SetNumber(int number_) {
        number = number_;
    }
    inline void SetSeed(const std::string& seed_) {
        seed = seed_;
    }
    inline void SetDrawn(bool drawn_) {
        drawn = drawn_;
    }
}; // end Card


std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << c.GetNumber() << c.GetSeed();
    return os;
}


class Deck {
 private:
    Card cards[num_seeds * num_numbers];
    std::string seeds[num_seeds] = {"♥", "♦", "♣", "♠"};
    // {"hearts", "diamonds", "clubs", "spades"};

 public:
    Deck() {
        for(int i = 0; i < num_seeds; i++){
            for(int j = 0; j < num_numbers; j++){
                cards[(10 * i) + j].SetNumber(j + 1);
                cards[(10 * i) + j].SetSeed(seeds[i]);
            }
        }
    }

    void Print() {
        for(int i = 0; i < num_seeds; i++){
            for(int j = 0; j < num_numbers; j++){
                if (!cards[(10 * i) + j].GetDrawn())
                std::cout << cards[(10 * i) + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void Shuffle() {
        srand(time(NULL));
        for(int i = 0; i < num_seeds * num_numbers; i++){
            int card_a = rand() % ((num_seeds * num_numbers) - 1);
            int card_b = rand() % ((num_seeds * num_numbers) - 1);
            Card temp = cards[card_a];
            cards[card_a] = cards[card_b];
            cards[card_b] = temp;          
        }
    }

    Card Draw() {
        int index = rand() % ((num_seeds * num_numbers) - 1);
        while (cards[index].GetDrawn()) {
            index = rand() % ((num_seeds * num_numbers) - 1);
        }
        Card card = cards[index];
        cards[index].SetDrawn(true);
        return card;
    }

    bool Check() {
        for(int i = 0; i < num_seeds; i++){
            for(int j = 0; j < num_numbers; j++){
                if (cards[(10 * i) + j].GetDrawn())
                    return false;
            }
        }
        return true;
    }
}; // end Deck


int main() {

    Deck d;

    std::cout << "The cards in the deck are" << std::endl;
    d.Print();

    d.Shuffle();
    std::cout << std::endl;

    std::cout << "The card drawn is " << d.Draw() << std::endl;

    if(d.Check()){
        std::cout << "All cards have been drawn" << std::endl;
    } else {
        std::cout << "Not all cards have been drawn" << std::endl;
    }
    return 0;
}