#include "portfolio.hpp"
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

    string event_time = "now"; // fix this
    string descr = "Account created with initial balance of 0.";
    m_history.push_back(record_event(descr));
}

Account::Account(const double& starting_bal) {
    m_balance = starting_bal;

    string event_time = "now"; // fix this
    string descr = "Account created with initial balance of " + to_string(starting_bal) + ".";
    m_history.push_back(record_event(descr));
}

void Account::deposit_funds(const double& deposit) {
    m_balance += deposit;

    string event_time = "now";
    string descr =to_string(deposit) + " added to account.";
    cout << descr << "**** **** HERE HERE *** " << endl;
    m_history.push_back(record_event(descr));
}

void Account::withdraw_funds(const double& withdrawal) {
    m_balance -= withdrawal;

    string event_time = "now";
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

StockPortfolio::StockPortfolio(const int& starting_bal) {

}

int StockPortfolio::enumerate_ownership(const std::string& stock) { // how many do i own?

}

void StockPortfolio::add_to_watch_list(const std::string& stock) {

}

void StockPortfolio::view_watch_list() {

}

void StockPortfolio::clear_search_history() {
    
}

// void Account::balance_update() { // idk

//     char view_balance;

//     std::string question = "Would you to view your balance after this transaction? Y/N";
//     std::cout << "Your deposit has been completed. " << question << std::endl;
//     std::cin >> view_balance;

//     if (view_balance != 'Y' && view_balance != 'N') {
//         //view_balance = ask_again(question);
//     }

//     if (view_balance == 'Y' || view_balance == 'y') {
//         std::cout << "Your new balance is " << check_balance() << std::endl;
//     }

// }