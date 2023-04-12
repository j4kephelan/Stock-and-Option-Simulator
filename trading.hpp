#ifndef TRADING
#define TRADING
#include <string>
#include <cmath>

struct Stock {
    std::string name;
    double volatility;
    double underlying_price;
    double strike_price;
    double expiration_time;
    double interest_rate;
};

class Pricer {
    public:
    double black_scholes(const Stock& stock);
    double get_real_price(const Stock& stock);
    bool fair_price;
    double norm_cdf(double x);

};

#endif // TRADING