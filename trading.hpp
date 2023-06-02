#ifndef TRADING
#define TRADING
#include <string>
#include <cmath>
#include <vector>
#include <map>

// BS_Eval struct stores the data outputted by the black-scholes model
struct BS_Eval {
    std::string option_name;
    double call_price;
    double put_price;
    double current_price;
};

// TradingToolkit class stores stock and option data in order to perform 
// operations with it
class TradingToolkit {
    public:

        // Stock/option operation helper
        TradingToolkit();

        // getter for prices of options/stocks
        std::map<std::string, std::string> get_prices() { return m_prices; } 

        // Runs black scholes model and outputs relevant information
        void option_eval();

        // Runs black scholes model given an option name
        BS_Eval black_scholes(const std::string& option_name); 

        // Gets the current price of a given option
        double get_contract_price(const std::string& option_name);

        // shows all stocks in dataset
        void show_stocks();

        // shows all options in dataset
        void show_options();

    private:
        // stock/option prices
        std::map<std::string, std::string> m_prices;

        // helper for running black scholes model
        double norm_cdf(double x);

};

#endif // TRADING