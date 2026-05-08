#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <vector>
#include <string>

enum class States {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
private:
    double cash;
    std::vector<std::string> menu;
    std::vector<double> prices;
    States state;
    int selected;   

public:
    Automata();

    void on();
    void off();
    void coin(double amount);
    std::vector<std::string> getMenu() const;
    States getState() const;
    void choice(int index);
    bool check();
    void cancel();
    void cook();
    void finish();

    double getCash() const { return cash; }
    int getSelected() const { return selected; }
};

#endif