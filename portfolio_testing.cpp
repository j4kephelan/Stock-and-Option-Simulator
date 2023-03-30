#include "unit_test_framework.h"
#include "portfolio.hpp"

TEST(test_bank_constructors){
    Bank empty;
    ASSERT_EQUAL(0, empty.check_balance());

    int bal = 1000000;
    Bank rich(bal);
    ASSERT_EQUAL(bal, rich.check_balance());
};

TEST(test_bank_deposit) {
    Bank myBank(100);
    myBank.deposit_funds(5);
    ASSERT_EQUAL(100+5, myBank.check_balance());
}

TEST(test_bank_withdrawal) {
    Bank myBank(100);
    myBank.withdraw_funds(5);
    ASSERT_EQUAL(100-5, myBank.check_balance());
}

TEST_MAIN();