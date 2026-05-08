#include "Automata.h"
#include <gtest/gtest.h>

// Тест 1: Начальное состояние
TEST(AutomataTest, InitialState) {
    Automata a;
    EXPECT_EQ(a.getState(), States::OFF);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

// Тест 2: Включение и выключение
TEST(AutomataTest, OnOff) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), States::WAIT);
    a.off();
    EXPECT_EQ(a.getState(), States::OFF);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

// Тест 3: Внос монет в состоянии WAIT
TEST(AutomataTest, CoinInWait) {
    Automata a;
    a.on();
    a.coin(10.0);
    EXPECT_EQ(a.getState(), States::ACCEPT);
    EXPECT_DOUBLE_EQ(a.getCash(), 10.0);
}

// Тест 4: Накопление монет
TEST(AutomataTest, CoinAccumulation) {
    Automata a;
    a.on();
    a.coin(5.0);
    a.coin(3.0);
    EXPECT_DOUBLE_EQ(a.getCash(), 8.0);
    EXPECT_EQ(a.getState(), States::ACCEPT);
}

// Тест 5: Успешный выбор и проверка
TEST(AutomataTest, ChoiceAndCheckSuccess) {
    Automata a;
    a.on();
    a.coin(2.0);     // достаточно для Latte (индекс 2, цена 2.0)
    a.choice(2);
    EXPECT_EQ(a.getState(), States::CHECK);
    EXPECT_TRUE(a.check());
    // Деньги на этом этапе ещё не списаны
    EXPECT_DOUBLE_EQ(a.getCash(), 2.0);
    EXPECT_EQ(a.getState(), States::CHECK);
}

// Тест 6: Неуспешная проверка (недостаточно средств)
TEST(AutomataTest, ChoiceAndCheckFailure) {
    Automata a;
    a.on();
    a.coin(0.5);
    a.choice(0);     // Espresso – 1.0
    EXPECT_FALSE(a.check());
    EXPECT_EQ(a.getState(), States::ACCEPT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.5);
}

// Тест 7: Приготовление и завершение
TEST(AutomataTest, CookAndFinish) {
    Automata a;
    a.on();
    a.coin(1.5);
    a.choice(1);     // Americano – 1.5
    ASSERT_TRUE(a.check());
    a.cook();
    EXPECT_EQ(a.getState(), States::COOK);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0); // деньги списаны
    a.finish();
    EXPECT_EQ(a.getState(), States::WAIT);
}

// Тест 8: Отмена в состоянии ACCEPT
TEST(AutomataTest, CancelInAccept) {
    Automata a;
    a.on();
    a.coin(5.0);
    a.cancel();
    EXPECT_EQ(a.getState(), States::WAIT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

// Тест 9: Отмена в состоянии CHECK
TEST(AutomataTest, CancelInCheck) {
    Automata a;
    a.on();
    a.coin(3.0);
    a.choice(2);     // Переход в CHECK
    a.cancel();
    EXPECT_EQ(a.getState(), States::WAIT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

// Тест 10: Выключение из состояния COOK
TEST(AutomataTest, OffFromCook) {
    Automata a;
    a.on();
    a.coin(0.7);
    a.choice(4);     // Tea – 0.7
    ASSERT_TRUE(a.check());
    a.cook();        // Переход в COOK
    a.off();
    EXPECT_EQ(a.getState(), States::OFF);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

// Тест 11: Вызов check() в состоянии ACCEPT (не должен ничего менять)
TEST(AutomataTest, CheckInAccept) {
    Automata a;
    a.on();
    a.coin(2.0);
    EXPECT_FALSE(a.check());   // не в CHECK – возвращает false
    EXPECT_EQ(a.getState(), States::ACCEPT);
}

// Тест 12: Монеты не принимаются во время приготовления
TEST(AutomataTest, CoinInCook) {
    Automata a;
    a.on();
    a.coin(1.0);
    a.choice(0);     // Espresso – 1.0
    ASSERT_TRUE(a.check());
    a.cook();        // Переход в COOK
    double cashBefore = a.getCash();
    a.coin(100.0);   // не должно быть принято
    EXPECT_EQ(a.getState(), States::COOK);
    EXPECT_DOUBLE_EQ(a.getCash(), cashBefore);
}

// Точка входа для Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}