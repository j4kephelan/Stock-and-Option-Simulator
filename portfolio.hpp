#ifndef PORTFOLIO
#define PORTFOLIO
#include <string>
#include <vector>

class StockPortfolio;
class Account;
class Pricer;

struct Transaction {
        std::string event_time; // figure out how to get current time
        std::string description;
        float new_balance;
};

class Account {
    public:
        std::shared_ptr<Transaction> record_event(const std::string& event_time, const std::string& descr);

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

        void purchase(const std::string& stock, const int& volume);
        void sell(const std::string& stock, const int& volume);
        float checkFairPrice(const std::string& method, const std::string& stock);
        float checkRealPrice(const std::string stock);
        void marketCloses(); // time until market closes
    
    private:
        Account m_cash;
};

#endif // PORTFOLIO