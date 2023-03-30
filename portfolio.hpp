#ifndef STOCK_PORTFOLIO_
#define STOCK_PORTFOLIO_

#include <vector>
#include <string>

class Bank {
public:
    Bank();
    Bank(const int& starting_bal);

    int check_balance() { return m_balance; };
    void deposit_funds(const int& deposit);
    void withdraw_funds(const int& withdrawal);
    void view_history();


private:
    int m_balance;
    std::vector<std::string> m_history;
};

#endif // BANK