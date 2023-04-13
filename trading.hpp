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

    std::pair<double, double> black_scholes_primer(const Stock& stock);
    double black_scholes_call_price(const Stock& stock);
     double black_scholes_put_price(const Stock& stock);
     
    double get_real_price(const Stock& stock);
    bool is_price_fair();
    double norm_cdf(double x);
};

#endif // TRADING