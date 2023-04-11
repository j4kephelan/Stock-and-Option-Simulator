#include <iostream>
#include <string>
#include <vector>
// #include <chrono>
// #include <ctime> 
#include "portfolio.hpp"

namespace {
    char ask_again(const std::string& question) {
        std::cout << "Sorry, your answer was invalid.\n" << question << std::endl;

        char answer;
        std::cin >> answer;
        if (answer == 'Q') {
            return 'N';
        }
        else if (answer != 'Y' && answer != 'N') {
            ask_again(question);
        }
        return answer;
    }
}

Account::Account(): m_balance(0) {}

Account::Account(const int& starting_bal) {
    m_balance = starting_bal;
    // std::string update;
    // m_history.push_back(update);
}

void Account::deposit_funds(const int& deposit) {
    char view_balance;
    m_balance += deposit;

    std::string question = "Would you to view your balance after this transaction? Y/N";
    std::cout << "Your deposit has been completed. " << question << std::endl;
    std::cin >> view_balance;

    if (view_balance != 'Y' && view_balance != 'N') {
        view_balance = ask_again(question);
    }

    if (view_balance == 'Y') {
        std::cout << "Your new balance is " << check_balance() << std::endl;
    }
}

void Account::withdraw_funds(const int& withdrawal) {
    char view_balance;
    m_balance -= withdrawal;

    std::string question = "Would you to view your balance after this transaction? Y/N";
    std::cout << "Your deposit has been completed. " << question << std::endl;
    std::cin >> view_balance;

    if (view_balance != 'Y' && view_balance != 'N') {
        view_balance = ask_again(question);
    }

    if (view_balance == 'Y') {
        std:: cout << "Your new balance is " << check_balance() << std::endl;
    }
}

void Account::view_history() {
    std::cout << "ACCOUNT HISTORY: \n";
    // for (const std::string& event : m_history) {
    //     std:: cout << event << "\n";
    // }
    std::cout << std::flush;
}