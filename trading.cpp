#include "trading.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

double TradingToolkit::norm_cdf(double x) {
    return (1.0 + std::erf(x / std::sqrt(2.0))) / 2.0;
}

double TradingToolkit::get_current_price(/*const std::string& stock*/) {
    string stock_file = "STOCK_DATA.csv";
    ifstream allStocks;

    allStocks.open(stock_file);
    while (allStocks.peek() != EOF) {
        string example;
        getline(allStocks, example, ',');

        cout << example << endl;
    }
    allStocks.close();

    double hi = 0.00;
    return hi;
}

void TradingToolkit::buy_stock(const std::string& stock, const int& volume) {

}

void TradingToolkit::sell_stock(const std::string& stock, const int& volume) {

}

vector<string> TradingToolkit::budget(const double& price) { // what can i afford for less than X per share

}

Option TradingToolkit::get_option_info(const std::string& option) { // get stock struct from data to feed to black_scholes method

}

BS_Eval TradingToolkit::black_scholes(const Option& option) {
    // pull variables for equation out of stock struct
    double option_price = option.underlying_price;
    double strike_price = option.strike_price;
    double time_to_expiry = option.expiration_time;
    double risk_free_rate = option.interest_rate;
    double implied_volatility = option.volatility;

    // calculate d1 and d2 values
    double d1 = (std::log(option_price / strike_price) + (risk_free_rate +
     (implied_volatility * implied_volatility) / 2) * time_to_expiry) /
     (implied_volatility * std::sqrt(time_to_expiry));

    double d2 = d1 - implied_volatility * std::sqrt(time_to_expiry);

    BS_Eval results;
    results.option_name = option.name;

    // return fair price of call option
    results.call_price = option_price * norm_cdf(d1) - strike_price * 
        std::exp(-risk_free_rate * time_to_expiry) * norm_cdf(d2);
    // return fair price of put option
    results.put_price = strike_price * std::exp(-risk_free_rate * time_to_expiry)
        * norm_cdf(-d2) - option_price * norm_cdf(-d1);

    return results;
}

bool TradingToolkit::is_price_fair() { // with data, idk if this is needed

}

std::string TradingToolkit::call_or_put(const Option& option) { // should i buy a call or put on this, idk if this is needed

}

    