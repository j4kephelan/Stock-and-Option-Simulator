#ifndef TRADING
#define TRADING
#include <string>
#include <cmath>
#include <vector>
#include <map>

struct BS_Eval {
    std::string option_name;
    double call_price;
    double put_price;
    double current_price;
};

class TradingToolkit {
    public:

        TradingToolkit();
        std::map<std::string, std::string> get_prices() { return m_prices; } // done

        void option_eval();
        BS_Eval black_scholes(const std::string& option_name); // done
        double get_contract_price(const std::string& option_name);
        void show_stocks();

    private:
        // std::vector<std::string> m_pricing_history;
        std::map<std::string, std::string> m_prices;
        double norm_cdf(double x);

};

#endif // TRADING