#include <iostream>
#include <string>
#include <vector>
// #include <chrono>
// #include <ctime> 
#include "portfolio.hpp"


Account::Account(): m_balance(0) {}

Account::Account(const int& starting_bal) {
    m_balance = starting_bal;
    // std::string update;
    // m_history.push_back(update);
}

void Account::balance_update() {

    char view_balance;

    std::string question = "Would you to view your balance after this transaction? Y/N";
    std::cout << "Your deposit has been completed. " << question << std::endl;
    std::cin >> view_balance;

    if (view_balance != 'Y' && view_balance != 'N') {
        //view_balance = ask_again(question);
    }

    if (view_balance == 'Y' || view_balance == 'y') {
        std::cout << "Your new balance is " << check_balance() << std::endl;
    }

}

void Account::deposit_funds(const int& deposit) {
    m_balance += deposit;
    //balance_update();
}

void Account::withdraw_funds(const int& withdrawal) {
    m_balance -= withdrawal;
   // balance_update();
}


void Account::view_history() {
    std::cout << "ACCOUNT HISTORY: \n";
    // for (const std::string& event : m_history) {
    //     std:: cout << event << "\n";
    // }
    std::cout << std::flush;
}