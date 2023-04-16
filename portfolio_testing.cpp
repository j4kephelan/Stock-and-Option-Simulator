#include "unit_test_framework.h"
#include "portfolio.hpp"
#include <iostream>
#include <string>
#include <vector>

TEST(test_account_constructors){
    Account empty;
    ASSERT_EQUAL(0.00, empty.get_balance());
    ASSERT_EQUAL(empty.get_history().at(0)->new_balance, 0.00);

    double balance = 1000000.00;
    Account rich(balance);
    ASSERT_EQUAL(balance, rich.get_balance());
    ASSERT_EQUAL(rich.get_history().at(0)->new_balance, balance);
};

TEST(test_account_deposit) {
    Account myBank(100.00);
    myBank.deposit_funds(5.00);
    ASSERT_EQUAL(100.00+5.00, myBank.get_balance());
    ASSERT_EQUAL(myBank.get_history().back()->new_balance, 100.00+5.00);
}

TEST(test_account_withdrawal) {
    Account myBank(100.00);
    myBank.withdraw_funds(5.00);
    ASSERT_EQUAL(100.00-5.00, myBank.get_balance());
    ASSERT_EQUAL(myBank.get_history().back()->new_balance, 100.00-5.00);
}

TEST(test_view_history) {
    Account historyChecker(1.00);
    historyChecker.deposit_funds(1.00);
    historyChecker.deposit_funds(100.00);
    historyChecker.withdraw_funds(5.00);

    historyChecker.view_history();
}

TEST_MAIN()