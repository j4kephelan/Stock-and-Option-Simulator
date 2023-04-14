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

        Stock get_stock_info(const string& name); // with data!
        double norm_cdf(double x); // done
        double Pricer::black_scholes(const Stock& stock, const string& option); // done?
        double get_real_price(const Stock& stock); // with data!
        bool is_price_fair(); // with data!

    private:

};

#endif // TRADING