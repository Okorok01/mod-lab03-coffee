
#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;

    std::cout << "=== Демонстрация работы автомата ===\n";
    machine.on();   // OFF -> WAIT

    // Покажем меню
    auto menu = machine.getMenu();
    std::cout << "Меню:\n";
    for (const auto& item : menu)
        std::cout << "  " << item << "\n";

    // Первый напиток
    machine.coin(1.0);
    machine.coin(0.5);         // всего 1.5
    machine.choice(1);         // Americano (1.5)
    if (machine.check()) {
        machine.cook();       // CHECK -> COOK (деньги списываются)
        machine.finish();     // COOK -> WAIT
    }

    // Второй напиток
    machine.coin(0.7);
    machine.choice(4);         // Tea (0.7)
    if (machine.check()) {
        machine.cook();
        machine.finish();
    }

    machine.off();
    return 0;
}