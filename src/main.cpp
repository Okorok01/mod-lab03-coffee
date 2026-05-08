
#include "Automata.h"
#include <iostream>

int main() {
    Automata machine;

    std::cout << "=== Демонстрация работы автомата ===\n";
    machine.on();   

        auto menu = machine.getMenu();
    std::cout << "Меню:\n";
    for (const auto& item : menu)
        std::cout << "  " << item << "\n";

        machine.coin(1.0);
    machine.coin(0.5);         
    machine.choice(1);        
    if (machine.check()) {
        machine.cook();       
        machine.finish();     
    }

    // Второй напиток
    machine.coin(0.7);
    machine.choice(4);        
    if (machine.check()) {
        machine.cook();
        machine.finish();
    }

    machine.off();
    return 0;
}