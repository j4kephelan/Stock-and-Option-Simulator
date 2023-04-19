#include "trading.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace {

    // reads in stock/option data from a csv database
    vector<vector<string>> read_csv(const string& filename) {
        ifstream stock_file(filename);
        vector<vector<string>> contents;
        string line;
        while(getline(stock_file, line)) {
            stringstream iss(line);
            vector<string> row;
            string element;
            while (getline(iss, element, ',')) {
                row.push_back(element);
            }
            if (row.at(0) == "PASS") {
                return contents;
            } else {
                contents.push_back(row);
            }
        }
        return contents;
    }
}

// reads in stock data 
TradingToolkit::TradingToolkit() {
    vector<vector<string>> stock_data = read_csv("STOCK_DATA.csv");
    map<string, string> prices;
    for (const auto& row : stock_data) {
        string symbol = row.at(0);
        string price = row.at(3);
        prices.insert({symbol, price});
    }
    m_prices = prices;
}

double TradingToolkit::norm_cdf(double x) {
    return (1.0 + erf(x / sqrt(2.0))) / 2.0;
}

BS_Eval TradingToolkit::black_scholes(const string& option_name) {


    // reads in option data
    vector<vector<string>> option_data = read_csv("Option_Data.csv");

    string stored_option_name;
    double option_price;
    double strike_price;
    double time_to_expiry;
    double risk_free_rate;
    double implied_volatility;
    double current_price;
    bool option_found = false;


    for (const auto& row : option_data) {
        if (row.at(0) == option_name) {
            option_price = stod(row.at(1));
            strike_price = stod(row.at(2));
            time_to_expiry = stod(row.at(3));
            risk_free_rate = stod(row.at(4));
            implied_volatility = stod(row.at(5));
            current_price = stod(row.at(6));
            option_found = true;
        } 
    }
    if (!option_found) {
        throw invalid_argument("Option not found.");
    }


    double d1 = (log(option_price / strike_price) + (risk_free_rate +
     (implied_volatility * implied_volatility) / 2) * time_to_expiry) /
     (implied_volatility * sqrt(time_to_expiry));

    double d2 = d1 - implied_volatility * sqrt(time_to_expiry);

    BS_Eval results;
    results.option_name = option_name;
    results.current_price = current_price;

    // return fair price of call option
    results.call_price = option_price * norm_cdf(d1) - strike_price * 
        exp(-risk_free_rate * time_to_expiry) * norm_cdf(d2);
    // return fair price of put option
    results.put_price = strike_price * exp(-risk_free_rate * time_to_expiry)
        * norm_cdf(-d2) - option_price * norm_cdf(-d1);

    return results;
    
}



void TradingToolkit::option_eval() {

    string desired_option;

    cout << "We will use the Black-Scholes algorithm to price your option. "
        << "Enter the name of the option you would like to evaluate: ";
    cin >> desired_option;


    double call_price = (black_scholes(desired_option)).call_price;
    double put_price = (black_scholes(desired_option)).put_price;
    double current_price = (black_scholes(desired_option)).current_price;

    cout << "Black-Scholes Call Option Price for " << desired_option << ": " << call_price << endl;
    cout << "Black-Scholes Put Option Price for " << desired_option << ": " << put_price << endl;

    if (current_price > call_price) {
        cout << "The fair price is lower than current market price. This option may be overvalued. Sell." << endl; 
    } else {
        cout << "The fair price is greater than current market price. This option may be undervalued. Buy." << endl; 
    }

    if (call_price > put_price) {
        cout << "This indicates that the market is expecting this asset to increase in price, purchase call options." << endl;
    } else {
        cout << "This indicates that the market is expecting this asset to decrease in price, purchase put options." << endl;
    }

}

// gets option contract price, accounting that a contract includes 100 shares
double TradingToolkit::get_contract_price(const string& option_name) {
    return 100*(black_scholes(option_name).current_price);
}

void TradingToolkit::show_stocks() {
    vector<vector<string>> stock_data = read_csv("STOCK_DATA.csv");
    for (const auto& row : stock_data) {
        if (row.at(0) == "ZTS") {
            cout << row.at(0);
        } else if (row.at(0) != "Symbol") {
            cout << row.at(0) << ',' << ' ';
        }
    }
    cout << endl;
}

void TradingToolkit::show_options() {
    vector<vector<string>> option_data = read_csv("Option_Data.csv");
    option_data.erase(option_data.begin());
    for (const auto& row : option_data) {
        if (row.at(0) == "AAPL_option_19_C") {
            cout << row.at(0);
        } else {
            cout << row.at(0) << ',' << ' ';
        }
    }
    cout << endl;
}