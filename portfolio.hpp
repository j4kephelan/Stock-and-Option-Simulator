#ifndef PORTFOLIO
#define PORTFOLIO


struct Transaction {
    std::string time; // figure out how to get current time
    std::string description;
    float new_balance;
};

class Account {
    public:
        Account();
        Account(const int& starting_bal);

        float check_balance() { return m_balance; };
        void deposit_funds(const int& deposit);
        void withdraw_funds(const int& withdrawal);
        void view_history();

    private:
        float m_balance;
        std::vector<Transaction> m_history;
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