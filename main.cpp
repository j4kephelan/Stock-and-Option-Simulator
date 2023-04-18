#include "portfolio.hpp"
#include "trading.hpp"

#include <iostream>

using namespace std;

namespace {
    void main_menu() {
        cout << "What would you like to do? Enter a number 1-5." << '\n'
        << "Buy (1) | Sell (2) | Deposit (3) | Withdraw (4) | Price (5)" << endl;
    }

    string stock_or_option(const string& choice) {
        cout << "Would you like to " + choice + " a stock or an option?" << endl;
        string asset;
        cin >> asset;
        if (asset != "stock" && asset != "option") {
            cout << "Please select either stock or option." << endl;
            stock_or_option(choice);
        } else {
            return asset;
        }
    }
}

int main() {


    double starting_bal;
    cout << "Hello! Welcome to our Stock and Option simulator. What would you like your starting balance to be? ";
    cin >> starting_bal;

    StockPortfolio yourPortfolio(starting_bal);

   main_menu();

   enum Choice {Buy = 1, Sell = 2, Deposit = 3, Withdraw = 4, Price = 5};

   int c = -1;
   cin >> c;

    switch(c) {
        case Buy:
        {
            string asset = stock_or_option("buy");
            if (asset == "stock") {

                string s;
                cout << "What stock would you like to buy?" << endl;
                cin >> s;

                double amount;
                cout << "How many shares?" << endl;
                cin >> amount;

                try {
                    yourPortfolio.buy_stock(s, amount);
                    yourPortfolio.update_portfolio_val();
                    double val = yourPortfolio.get_portfolio_val();
                    cout << "Stock bought successfully. New portfolio value: "
                        << to_string(val) << endl;
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                string o;
                cout << "What option contract would you like to buy?" << endl;
                cin >> o;

                double amount;
                cout << "How many?" << endl;
                cin >> amount;

                try {
                    yourPortfolio.buy_option_contract(o, amount);
                    cout << "Option contract bought successfully. " << endl;
                    main_menu();
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        case Sell:
        {
            string asset = stock_or_option("sell");
            if (asset == "stock") {
                cout << "What stock would you like to sell?" << endl;
            } else {
                cout << "What option would you like to sell?" << endl;
            }
            break;
        }
        case Deposit:
        {
            double money;
            cout << "How much would you like to deposit? ";
            cin >> money;
            yourPortfolio.deposit_more_cash(money);
            cout << "Deposit Successful!" << endl;
            break;
        }
        default:
        cout << "testing";
    }

    return 0;
}