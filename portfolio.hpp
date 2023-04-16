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

        int enumerate_ownership(const std::string& stock); // how many do i own? // done

        void buy_stock(const std::string& symbol, const int& volume); // done for now
        void sell_stock(const std::string& symbol, const int& volume);

        void add_to_watch_list(const std::string& stock);
        void view_watch_list();
        std::vector<Transaction> view_search_history();
        void clear_search_history();

    private:
        Account m_cash;
        float m_portfolio_val;
        
        TradingToolkit m_trading;

        std::map<std::string, int> m_owned_stocks;
        std::vector<std::string> m_watch_list;
        std::vector<Transaction> m_search_history;
};

#endif // PORTFOLIO