#include "Automata.h"
#include <gtest/gtest.h>

TEST(AutomataTest, InitialState) {
    Automata a;
    EXPECT_EQ(a.getState(), States::OFF);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(AutomataTest, OnOff) {
    Automata a;
    a.on();
    EXPECT_EQ(a.getState(), States::WAIT);
    a.off();
    EXPECT_EQ(a.getState(), States::OFF);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(AutomataTest, CoinInWait) {
    Automata a;
    a.on();
    a.coin(10.0);
    EXPECT_EQ(a.getState(), States::ACCEPT);
    EXPECT_DOUBLE_EQ(a.getCash(), 10.0);
}

TEST(AutomataTest, CoinAccumulation) {
    Automata a;
    a.on();
    a.coin(5.0);
    a.coin(3.0);
    EXPECT_DOUBLE_EQ(a.getCash(), 8.0);
    EXPECT_EQ(a.getState(), States::ACCEPT);
}

TEST(AutomataTest, ChoiceAndCheckSuccess) {
    Automata a;
    a.on();
    a.coin(2.0);    
    a.choice(2);
    EXPECT_EQ(a.getState(), States::CHECK);
    EXPECT_TRUE(a.check());
    EXPECT_DOUBLE_EQ(a.getCash(), 2.0);
    EXPECT_EQ(a.getState(), States::CHECK);
}

TEST(AutomataTest, ChoiceAndCheckFailure) {
    Automata a;
    a.on();
    a.coin(0.5);
    a.choice(0);    
    EXPECT_FALSE(a.check());
    EXPECT_EQ(a.getState(), States::ACCEPT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.5);
}

TEST(AutomataTest, CookAndFinish) {
    Automata a;
    a.on();
    a.coin(1.5);
    a.choice(1);     
    ASSERT_TRUE(a.check());
    a.cook();
    EXPECT_EQ(a.getState(), States::COOK);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0); 
    a.finish();
    EXPECT_EQ(a.getState(), States::WAIT);
}

TEST(AutomataTest, CancelInAccept) {
    Automata a;
    a.on();
    a.coin(5.0);
    a.cancel();
    EXPECT_EQ(a.getState(), States::WAIT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(AutomataTest, CancelInCheck) {
    Automata a;
    a.on();
    a.coin(3.0);
    a.choice(2);     
    a.cancel();
    EXPECT_EQ(a.getState(), States::WAIT);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(AutomataTest, OffFromCook) {
    Automata a;
    a.on();
    a.coin(0.7);
    a.choice(4);    
    ASSERT_TRUE(a.check());
    a.cook();        
    a.off();
    EXPECT_EQ(a.getState(), States::OFF);
    EXPECT_DOUBLE_EQ(a.getCash(), 0.0);
}

TEST(AutomataTest, CheckInAccept) {
    Automata a;
    a.on();
    a.coin(2.0);
    EXPECT_FALSE(a.check());   
    EXPECT_EQ(a.getState(), States::ACCEPT);
}

TEST(AutomataTest, CoinInCook) {
    Automata a;
    a.on();
    a.coin(1.0);
    a.choice(0);     
    ASSERT_TRUE(a.check());
    a.cook();       
    double cashBefore = a.getCash();
    a.coin(100.0);  
    EXPECT_EQ(a.getState(), States::COOK);
    EXPECT_DOUBLE_EQ(a.getCash(), cashBefore);
}
