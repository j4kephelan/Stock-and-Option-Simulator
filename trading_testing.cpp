#include "unit_test_framework.h"
#include "trading.hpp"

TEST(trade_read_csv) {
    TradingToolkit trades;
    trades.get_current_price();
    ASSERT_TRUE(0);
}

TEST_MAIN()