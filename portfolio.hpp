#ifndef PORTFOLIO
#define PORTFOLIO
#include <string>
#include <vector>
#include <map>
#include "trading.hpp"


struct Transaction {
        char * event_time;
        std::string description;
        double new_balance;
};

class Account {
    public:
        std::shared_ptr<Transaction> record_event(const std::string& descr);

        Account(); // done
        Account(const float& starting_bal); // done

        double get_balance() { return m_balance; }; // done
        void deposit_funds(const float& deposit); // done
        void withdraw_funds(const float& withdrawal); // done
        std::vector<std::shared_ptr<Transaction>> get_history() { return m_history; }; // done
        void view_history(); // done
        // void balance_update(); 

    private:
        float m_balance;
        std::vector<std::shared_ptr<Transaction>> m_history;
};

class StockPortfolio {
    public:
        StockPortfolio(); // done
        StockPortfolio(const int& starting_bal); // done

        int enumerate_ownership(const std::string& stock, const std::string& asset); // how many do i own? // done

        void buy_stock(const std::string& symbol, const int& volume); // done for now
        void sell_stock(const std::string& symbol, const int& volume);

        void buy_option_contract(const std::string& name, const int& volume);
        void sell_option_contract(const std::string& name, const int& volume);

        void add_to_watch_list(const std::string& stock);
        void view_watch_list(); 

        void deposit_more_cash(const double& deposit);
        void withdraw_more_cash(const double& withdrawal);
        void view_transaction_history();

        void update_portfolio_val();
        double get_portfolio_val() { return m_portfolio_val; }
        double get_cash_balance() { return m_cash.get_balance(); }

        std::map<std::string, std::string> get_stock_prices() { return m_trading.get_prices(); }
        void show_stocks() { m_trading.show_stocks(); }
        void price_option() { m_trading.option_eval(); }

        void view_my_stocks();

    private:
        Account m_cash;
        double m_portfolio_val;
        
        TradingToolkit m_trading;

        std::map<std::string, int> m_owned_stocks;
        std::map<std::string, int> m_owned_options;
        std::map<std::string, double> m_watch_list;
};

#endif // PORTFOLIO