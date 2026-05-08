
#include "Automata.h"
#include <iostream>

Automata::Automata() : cash(0.0), state(States::OFF), selected(-1) {
        menu   = {"Espresso", "Americano", "Latte", "Cappuccino", "Tea"};
    prices = {1.0, 1.5, 2.0, 2.5, 0.7};
}

void Automata::on() {
    if (state == States::OFF) {
        state = States::WAIT;
        std::cout << "Automata is ON. Waiting for action...\n";
    }
}

void Automata::off() {
    if (state != States::OFF) {
        std::cout << "Automata is turning OFF.\n";
        cash = 0.0;
        selected = -1;
        state = States::OFF;
        std::cout << "Automata is OFF.\n";
    }
}

void Automata::coin(double amount) {
    if (state == States::WAIT || state == States::ACCEPT) {
        if (amount <= 0) {
            std::cout << "Invalid coin amount.\n";
            return;
        }
        cash += amount;
        std::cout << "Added " << amount << " cash. Total: " << cash << "\n";
        if (state == States::WAIT) {
            state = States::ACCEPT;
            std::cout << "Now accepting money.\n";
        }
    } else {
        std::cout << "Cannot accept coins in current state.\n";
    }
}

std::vector<std::string> Automata::getMenu() const {
    std::vector<std::string> result;
    for (size_t i = 0; i < menu.size(); ++i) {
        result.push_back(menu[i] + " - $" + std::to_string(prices[i]));
    }
    return result;
}

States Automata::getState() const {
    return state;
}

void Automata::choice(int index) {
    if (state != States::ACCEPT) {
        std::cout << "Cannot choose drink now.\n";
        return;
    }
    if (index < 0 || index >= static_cast<int>(menu.size())) {
        std::cout << "Invalid choice.\n";
        return;
    }
    selected = index;
    std::cout << "Chosen: " << menu[selected]
              << " (price: " << prices[selected] << ")\n";
    state = States::CHECK;
}

bool Automata::check() {
    if (state != States::CHECK) {
        std::cout << "Not in checking state.\n";
        return false;
    }
    if (selected < 0 || selected >= static_cast<int>(menu.size())) {
        std::cout << "No drink selected.\n";
        return false;
    }
    if (cash >= prices[selected]) {
        std::cout << "Enough cash. Proceed to cooking.\n";
        return true;
    } else {
        std::cout << "Not enough money. Returning to accept state.\n";
        state = States::ACCEPT;
        return false;
    }
}

void Automata::cancel() {
    if (state == States::ACCEPT || state == States::CHECK) {
        std::cout << "Cancelling operation. Returning " << cash << " cash.\n";
        cash = 0.0;
        selected = -1;
        state = States::WAIT;
        std::cout << "Returned to wait state.\n";
    } else {
        std::cout << "Cannot cancel in current state.\n";
    }
}

void Automata::cook() {
    if (state == States::CHECK &&
        selected >= 0 && selected < static_cast<int>(menu.size()) &&
        cash >= prices[selected]) {
        cash -= prices[selected];
        std::cout << "Cooking " << menu[selected] << "...\n";
        state = States::COOK;
    } else {
        std::cout << "Cannot cook: check not passed or no drink selected.\n";
    }
}

void Automata::finish() {
    if (state == States::COOK) {
        std::cout << "Your " << menu[selected] << " is ready. Enjoy!\n";
        selected = -1;
        state = States::WAIT;
    } else {
        std::cout << "Nothing to finish.\n";
    }
}
