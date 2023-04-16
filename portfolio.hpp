#ifndef PORTFOLIO
#define PORTFOLIO
#include <string>
#include <vector>
#include <map>
#include "trading.hpp"

struct Transaction {
        char * event_time; // figure out how to get current time
        std::string description;
        double new_balance;
};

class Account {
    public:
        std::shared_ptr<Transaction> record_event(const std::string& descr);

        Account(); // done
        Account(const double& starting_bal); // done

        double check_balance() { return m_balance; }; // done
        void deposit_funds(const double& deposit); // done
        void withdraw_funds(const double& withdrawal); // done
        std::vector<std::shared_ptr<Transaction>> get_history() { return m_history; }; // done
        void view_history(); // done
        void balance_update(); // idk

    private:
        double m_balance;
        std::vector<std::shared_ptr<Transaction>> m_history;
};

class StockPortfolio {
    public:
        StockPortfolio();
        StockPortfolio(const int& starting_bal);

        int enumerate_ownership(const std::string& stock); // how many do i own?

        void add_to_watch_list(const std::string& stock);
        void view_watch_list();
        void clear_search_history();

    private:
        Account m_cash;
        std::map<std::string, int> m_owned_stocks;
        std::vector<std::string> m_watch_list;
        double m_portfolio_val;
        TradingToolkit m_trading;
};

#endif // PORTFOLIO