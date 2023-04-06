#include "unit_test_framework.h"
#include "portfolio.hpp"
#include <iostream>
#include <string>
#include <vector>

TEST(test_account_constructors){
    Account empty;
    ASSERT_EQUAL(0, empty.check_balance());

    int balance = 1000000;
    Account rich(balance);
    ASSERT_EQUAL(balance, rich.check_balance());
};

TEST(test_account_deposit) {
    Account myBank(100);
    myBank.deposit_funds(5);
    ASSERT_EQUAL(100+5, myBank.check_balance());
}

TEST(test_account_withdrawal) {
    Account myBank(100);
    myBank.withdraw_funds(5);
    ASSERT_EQUAL(100-5, myBank.check_balance());
}

TEST_MAIN();