#include <cstdio> // C Standard Input and Output Library
#include <string> // String Library for C++

class Tank {
 // data must always be private
 private:
    float level; // fuel level in the tank
    std::string name; // tank name

 public:
    // default constructor
    Tank() {
        level = 0.0f; // initializes the initial level of fuel
    }

    // constructor with parameters
    Tank(float init_level) {
        if (init_level < 0.0f) {
            printf("ERROR, can not init negative fuel");
        } else {
            level = init_level;
        }
    }

    // getter to detect the fuel level, const method
    float GetLevel() const {
        return level;
    }

    // setter to set the fuel level
    void SetLevel(float level_) {
        if(level_ <= 0.0f) {
            printf("ERROR, can not init negative fuel");
        } else {
            level = level_;
        }
    }

    // getter to return the name of the tank with copy
    std::string GetNameWithCopy() {
        return name;
    }

    // getter to return the name of the tank without copy
    const std::string& GetNameWithoutCopy() {
        return name;
    }

    // method to add fuel to the tank
    void Refill(float delta) {
        level += delta;
    }

    // method for consuming fuel from the tank
    void Consume(float delta) {
        if (delta > level) {
            printf("ERROR, can not use not available fuel");
        } else {
            // level -= delta;
            Refill(-delta);
        }
    }
}; // end Tank

int main() {

    Tank tank_default;  // call default constructor

    Tank tank(10.0f);
    // Tank is the class
    // tank is the instance that call
    // the constructor with parameters Tank(float init_level)

    std::string name_with_copy = tank_default.GetNameWithCopy();
    // get name with copy, return a value

    const std::string& name_without_copy = tank.GetNameWithoutCopy();
    // it returns a memory address that I cannot modify
    // and therefore I mark it as const

    // call the interface as instance.method()
    // the method is invoked on the instance
    tank_default.Refill(5.0f);
    tank.Refill(1.0f);
    tank_default.Consume(3.0f);

    printf("Tank 1: %f \n", tank_default.GetLevel());
    printf("Tank 2: %f \n", tank.GetLevel());

    return 0;
}