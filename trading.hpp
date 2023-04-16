#ifndef TRADING
#define TRADING
#include <string>
#include <cmath>
#include <vector>
#include <map>


struct Option {
    std::string name;
    double volatility;
    double underlying_price;
    double strike_price;
    double expiration_time;
    double interest_rate;
};

struct BS_Eval {
    std::string option_name;
    double call_price;
    double put_price;
};

class TradingToolkit {
    public:

        TradingToolkit();
        double get_current_price(/*const std::string& stock*/);

        // void buy_stock(const std::string& stock, const int& volume);
        // void sell_stock(const std::string& stock, const int& volume);

        // std::vector<std::string> budget(const double& price); // what can i afford for less than X per share

        // Option get_option_info(const std::string& name); // get stock struct from data to feed to black_scholes method
        // BS_Eval black_scholes(const Option& option); // done
        // bool is_price_fair(); // with data, idk if this is needed
        // std::string call_or_put(const Option& stock); // should i buy a call or put on this, idk if this is needed

    private:
        // std::vector<std::string> m_pricing_history;
        std::map<std::string, float> m_prices;

        double norm_cdf(double x);

};

#endif // TRADING