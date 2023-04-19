#ifndef PORTFOLIO
#define PORTFOLIO
#include <string>
#include <vector>
#include <map>
#include "trading.hpp"

// This struct is used to keep track of events that occur to Account class objects.
struct Transaction {
        char * event_time;
        std::string description;
        double new_balance;
};

// This class simulates a bank account
class Account {
    public:
        // This method is used to add a new Transaction struct instance to the
        // Account member variable m_history
        std::shared_ptr<Transaction> record_event(const std::string& descr);

        // Default constructor for Accounts with a 0 starting balance
        Account();

        // Constructor for Accounts with a nonzero starting balance
        Account(const float& starting_bal);

        // Method for accessing Account balance
        double get_balance() { return m_balance; };

        // Methods for depositing and withdrawing funds from the Account balance
        void deposit_funds(const float& deposit);
        void withdraw_funds(const float& withdrawal);

        // Methods for accessing and viewing history of Account transacations
        std::vector<std::shared_ptr<Transaction>> get_history() { return m_history; };
        void view_history();

    private:
        float m_balance;
        std::vector<std::shared_ptr<Transaction>> m_history;
};

class StockPortfolio {
    public:
        // Default constructor for the StockPortfolio class with an Account of 0 balance
        StockPortfolio();

        // Constructor for the StockPortfolio class with an Account of nonzero balance
        StockPortfolio(const int& starting_bal);

        // Method for counting the number of certain stocks or options in a portfolio
        int enumerate_ownership(const std::string& stock, const std::string& asset);

        // Methods for buying and selling stocks and reflecting the new Account balance
        void buy_stock(const std::string& symbol, const int& volume);
        void sell_stock(const std::string& symbol, const int& volume);

        // Methods for buying and selling options and reflecting the new Account balance
        void buy_option_contract(const std::string& name, const int& volume);
        void sell_option_contract(const std::string& name, const int& volume);

        // Methods for depositing, withdrawing, and retrieving cash from m_cash Account
        void deposit_more_cash(const double& deposit);
        void withdraw_more_cash(const double& withdrawal);
        double get_cash_balance() { return m_cash.get_balance(); }

        // Method for viewing m_history of m_cash Account
        void view_transaction_history();

        // Methods for calculating and retrieving portfolio value
        void update_portfolio_val();
        double get_portfolio_val();

        // Method for getting map of stock prices
        std::map<std::string, std::string> get_stock_prices() { return m_trading.get_prices(); }

        // Methods for showing all available stocks and options in our datasets
        void show_stocks() { m_trading.show_stocks(); }
        void show_options() { m_trading.show_options(); }

        // Method for finding real prices of stocks and options
        std::string get_stock_price(const std::string& stock);
        double get_option_price(const std::string& option)
            { return m_trading.get_contract_price(option); }

        // Method for evaluating option using Black-Scholes algorithm
        void eval_option() { m_trading.option_eval(); }
        
        // Methods for retrieving and viewing owned stocks and options
        std::vector<std::string> get_my_stocks();
        std::vector<std::string> get_my_options();
        void view_my_stocks();
        void view_my_options();

    private:
        Account m_cash;
        double m_portfolio_val;
        TradingToolkit m_trading;
        std::map<std::string, int> m_owned_stocks;
        std::map<std::string, int> m_owned_options;
};

#endif // PORTFOLIO