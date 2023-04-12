#ifndef TRADING
#define TRADING
#include <string>

struct Stock {
    std::string name;
    double volatility;
    double underlying_asset;
    double strike_price;
    double expiration_time;
    double interest_rate;
};

#endif // TRADING