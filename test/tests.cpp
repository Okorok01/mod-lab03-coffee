// Copyright 2025 <Student>
#include "Automata.h"
#include <iostream>
#include <cassert>

void test_on_off() {
    Automata a;
    assert(a.getState() == States::OFF);
    a.on();
    assert(a.getState() == States::WAIT);
    a.off();
    assert(a.getState() == States::OFF);
    std::cout << "test_on_off passed\n";
}

void test_coin() {
    Automata a;
    a.on();
    a.coin(50);
    assert(a.getState() == States::ACCEPT);
    a.coin(30);
    a.choice(0);
    assert(a.getState() == States::CHECK);
    a.check();
    assert(a.getState() == States::COOK);
    a.cook();
    assert(a.getState() == States::WAIT);
    std::cout << "test_coin passed\n";
}

void test_cancel() {
    Automata a;
    a.on();
    a.coin(100);
    a.cancel();
    assert(a.getState() == States::WAIT);
    bool res = a.choice(0);
    assert(!res);
    assert(a.getState() == States::WAIT);
    std::cout << "test_cancel passed\n";
}

void test_choice_invalid() {
    Automata a;
    a.on();
    a.coin(50);
    bool res = a.choice(10);
    assert(!res);
    assert(a.getState() == States::ACCEPT);
    res = a.choice(-1);
    assert(!res);
    assert(a.getState() == States::ACCEPT);
    std::cout << "test_choice_invalid passed\n";
}

void test_insufficient_funds() {
    Automata a;
    a.on();
    a.coin(20);
    a.choice(0);
    assert(a.getState() == States::CHECK);
    bool ok = a.check();
    assert(!ok);
    assert(a.getState() == States::ACCEPT);
    a.coin(10);
    a.check();
    assert(a.getState() == States::COOK);
    std::cout << "test_insufficient_funds passed\n";
}

void test_cook_without_check() {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(0);
    a.cook();
    assert(a.getState() == States::CHECK);
    std::cout << "test_cook_without_check passed\n";
}

void test_finish_direct() {
    Automata a;
    a.on();
    a.coin(50);
    a.choice(0);
    a.check();
    a.cook();
    assert(a.getState() == States::WAIT);
    a.finish();
    assert(a.getState() == States::WAIT);
    std::cout << "test_finish_direct passed\n";
}

void test_multiple_coins() {
    Automata a;
    a.on();
    a.coin(10);
    a.coin(20);
    a.coin(5);
    a.choice(1);
    a.check();
    assert(a.getState() == States::ACCEPT);
    a.coin(15);
    a.check();
    assert(a.getState() == States::COOK);
    a.cook();
    assert(a.getState() == States::WAIT);
    std::cout << "test_multiple_coins passed\n";
}

void test_off_during_accept() {
    Automata a;
    a.on();
    a.coin(100);
    a.off();
    assert(a.getState() == States::OFF);
    bool res = a.choice(0);
    assert(!res);
    std::cout << "test_off_during_accept passed\n";
}

void test_getMenu() {
    Automata a;
    a.getMenu();
    std::cout << "test_getMenu passed\n";
}

void test_state_transitions() {
    Automata a;
    assert(a.getState() == States::OFF);
    a.on();
    assert(a.getState() == States::WAIT);
    a.coin(10);
    assert(a.getState() == States::ACCEPT);
    a.choice(0);
    assert(a.getState() == States::CHECK);
    a.check();
    assert(a.getState() == States::COOK);
    a.cook();
    assert(a.getState() == States::WAIT);
    std::cout << "test_state_transitions passed\n";
}
