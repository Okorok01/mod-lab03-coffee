// Copyright 2025 <Student>
#ifndef INCLUDE_AUTOMATA_H__
#define INCLUDE_AUTOMATA_H__

#include <string>
#include <vector>

enum class States {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
 private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    States state;
    int selected_item;

 public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    void getMenu() const;
    States getState() const;
    bool choice(int index);
    bool check();
    void cancel();
    void cook();
    void finish();
};

#endif  // INCLUDE_AUTOMATA_H__
