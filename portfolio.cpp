#include "portfolio.hpp"
#include "trading.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime> 

using namespace std;

shared_ptr<Transaction> Account::record_event(const string& descr) {
    using namespace chrono;
    shared_ptr<Transaction> event = make_shared<Transaction>();

    time_t current_time = system_clock::to_time_t(system_clock::now());
    char * time_char = ctime(&current_time);
    event->event_time = time_char;

    event->description = descr;
    event->new_balance = m_balance;

    return event;
}

Account::Account(): m_balance(0) {
    m_balance = 0;

    string descr = "Account created with initial balance of 0.";
    m_history.push_back(record_event(descr));
}

Account::Account(const float& starting_bal) {
    m_balance = starting_bal;

    string descr = "Account created with initial balance of " + to_string(starting_bal) + ".";
    m_history.push_back(record_event(descr));
}

void Account::deposit_funds(const float& deposit) {
    m_balance += deposit;

    string descr = to_string(deposit) + " added to account.";
    m_history.push_back(record_event(descr));
}

void Account::withdraw_funds(const float& withdrawal) {
    m_balance -= withdrawal;

    string descr = to_string(std::ceil(withdrawal*100)/100) + " withdrawn from account.";
    m_history.push_back(record_event(descr));
}

void Account::view_history() {
    for (const auto& each : m_history) {
        cout << each->event_time << each->description << '\n'
            << "Updated balance: " << each->new_balance << "\n\n";
    }
    cout << flush;
}

StockPortfolio::StockPortfolio() {
    Account empty_account;
    m_cash = empty_account;
    m_portfolio_val = 0;
}

StockPortfolio::StockPortfolio(const int& starting_bal) {
    Account cash_account(starting_bal);
    m_cash = cash_account;
    m_portfolio_val = 0;
}

int StockPortfolio::enumerate_ownership(const string& symbol, const string& asset) {
    if (asset == "stock") {
        auto ownership_it = m_owned_stocks.find(symbol);
        if (ownership_it == m_owned_stocks.end()) {
            return 0;
        } else {
            return (*ownership_it).second;
        }
    } else if (asset == "option") {
        auto ownership_it = m_owned_options.find(symbol);
        if (ownership_it == m_owned_options.end()) {
            return 0;
        } else {
            return (*ownership_it).second;
        }
    } else {
        throw invalid_argument("Enter stock or option.");
    }
}

void StockPortfolio::buy_stock(const std::string& symbol, const int& volume) {

    map<string, string> prices = m_trading.get_prices();
    auto stock_it = prices.find(symbol);
    if (stock_it != prices.end()) {
        float price = stof((*stock_it).second);
        float cost = price*volume;
        if (cost < m_cash.get_balance()) { 
            string description = to_string(volume) + " shares of " + symbol + " bought.";
            m_cash.record_event(description);
            m_cash.withdraw_funds(cost); 
            if (enumerate_ownership(symbol, "stock") == 0) {
                m_owned_stocks.insert({symbol, volume}); 
            } else {
                m_owned_stocks.at(symbol) = m_owned_stocks.at(symbol) + volume;
            }
        } else {
            throw invalid_argument("Insufficient funds.");
        }
    } else {
        throw invalid_argument("Stock does not exist in our database.");
    }
}

void StockPortfolio::sell_stock(const std::string& symbol, const int& volume) {
    int amount_owned = enumerate_ownership(symbol, "stock");
    if (amount_owned >= volume) {
        map<string, string> prices = m_trading.get_prices();
        auto stock_it = prices.find(symbol);
        double price = stod((*stock_it).second);
        double profit = volume*price;

        string description = to_string(volume) + " shares of " + symbol + " sold.";
        m_cash.record_event(description);

        m_cash.deposit_funds(profit);
        m_owned_stocks.at(symbol) = amount_owned - volume;
    } else if (amount_owned < volume) {
        throw invalid_argument("Insufficient amount of " + symbol + " stock owned.");
    }
}


void StockPortfolio::buy_option_contract(const std::string& name, const int& volume) {
    if (m_trading.get_contract_price(name)) {
        double price =  m_trading.get_contract_price(name) * volume;
        if (m_cash.get_balance() >= price) {
            int owned = enumerate_ownership(name, "option");
            if (owned == 0) {
                m_owned_options.insert({name, volume});
            } else {
                m_owned_options.at(name) = m_owned_options.at(name) + volume;
            }
            string description = to_string(volume) + " contracts of " + name + " bought.";
            m_cash.record_event(description);
            m_cash.withdraw_funds(price);
        } else {
            throw invalid_argument("Insufficient funds.");
        }
    } else {
        throw invalid_argument("Option does not exist in our database.");
    }
}

void StockPortfolio::sell_option_contract(const std::string& name, const int& volume) {
    if (m_trading.get_contract_price(name)) {
        int owned = enumerate_ownership(name, "option");
        if (owned >= volume) {
            double profit = m_trading.get_contract_price(name) * volume;
            m_owned_options.at(name) = m_owned_options.at(name) - volume;
            string description = to_string(volume) + " contracts of " + name + " sold.";
            m_cash.record_event(description);
            m_cash.deposit_funds(profit);
        } else {
            throw invalid_argument("Insufficient amount of options owned.!!!");
        }
    } else {
        throw invalid_argument("Option does not exist in our database.");
    }
}

void StockPortfolio::deposit_more_cash(const double& deposit) {
    m_cash.deposit_funds(deposit);
}

void StockPortfolio::withdraw_more_cash(const double& withdrawal) {
    m_cash.withdraw_funds(withdrawal);
}

void StockPortfolio::view_transaction_history() {
    m_cash.view_history();
}

void StockPortfolio::update_portfolio_val() {
    double val = 0;
    if (m_owned_stocks.size() > 0) {
        for (const auto& stock : m_owned_stocks) {
            double price = stod(get_stock_price(stock.first));
            int volume = stock.second;
            val = val + price*volume;
        }
    }
    if (m_owned_options.size() > 0) {
        for (const auto& option : m_owned_options) {
            double price = m_trading.get_contract_price((option.first));
            int volume = option.second;
            val = val + price*volume;
        }
    }
    m_portfolio_val = val;
}

double StockPortfolio::get_portfolio_val() {
    update_portfolio_val();
    return m_portfolio_val;
}

vector<string> StockPortfolio::get_my_stocks() {
    vector<string> results;
    for (const auto& stock : m_owned_stocks) {
        results.push_back(stock.first);
    }
    return results;
}

vector<string> StockPortfolio::get_my_options() {
    vector<string> results;
    for (const auto& option : m_owned_options) {
        results.push_back(option.first);
    }
    return results;
}

void StockPortfolio::view_my_stocks() {
    if (m_owned_stocks.size() == 0) {
        cout << "You own no stocks." << endl;
    } else {
        for (const auto& stock : m_owned_stocks) {
            cout << stock.first << ":" << " " << stock.second << '\n';
        }
        cout << flush;
    }
}

void StockPortfolio::view_my_options() {
    if (m_owned_options.size() == 0) {
        cout << "You own no options." << endl;
    } else {
        for (const auto& option : m_owned_options) {
            cout << option.first << ':' << ' ' << option.second << '\n';
        }
        cout << flush;
    }
}

string StockPortfolio::get_stock_price(const std::string& stock) {
    map<string, string> prices = get_stock_prices();
    auto stock_it = prices.find(stock);
    if (stock_it != prices.end()) {
        return (*stock_it).second;
    } else {
        throw invalid_argument("Stock not found.");
    }
}