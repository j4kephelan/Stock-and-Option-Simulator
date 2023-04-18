#include "portfolio.hpp"
#include "trading.hpp"

#include <iostream>

using namespace std;

namespace {
    void main_menu() {
        cout << "What would you like to do? Enter a number 1-5." << '\n'
            << "Buy (1) | Sell (2) | Deposit (3) | "
            << "Withdraw (4) | Price (5) | View Balances (6)" << endl;
    }

    string stock_or_option(const string& choice) {
        cout << "Would you like to " + choice + " a stock or an option?" << endl;
        string asset;
        cin >> asset;
        if (asset != "stock" && asset != "option") {
            cout << "Please select either stock or option." << endl;
            string asset = stock_or_option(choice);
            return asset;
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

   enum Choice {
    Buy = 1,
    Sell = 2,
    Deposit = 3,
    Withdraw = 4,
    Price = 5,
    View = 6
    };

   int c = -1;
   cin >> c;

    switch(c) {
        case Buy:
        {
            string asset = stock_or_option("buy");
            if (asset == "stock") {

                string stock_buy;
                cout << "What stock would you like to buy?" << endl;
                cin >> stock_buy;

                double amount;
                cout << "How many shares?" << endl;
                cin >> amount;

                try {
                    yourPortfolio.buy_stock(stock_buy, amount);
                    yourPortfolio.update_portfolio_val();
                    double val = yourPortfolio.get_portfolio_val();
                    cout << "Stock bought successfully." << '\n'
                        << "New portfolio value: " << to_string(val) << '\n'
                        << "New portfolio cash balance: "
                        << to_string(yourPortfolio.get_cash_balance()) << endl;
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                string option_buy;
                cout << "What option contract would you like to buy?" << endl;
                cin >> option_buy;

                double amount;
                cout << "How many?" << endl;
                cin >> amount;

                try {
                    yourPortfolio.buy_option_contract(option_buy, amount);
                    cout << "Option contract bought successfully. " << endl;
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
                string stock_sell;
                cout << "What stock would you like to buy?" << endl;
                cin >> stock_sell;

                double amount;
                cout << "How many shares?" << endl;
                cin >> amount;

                try {
                    yourPortfolio.sell_stock(stock_sell, amount);
                    yourPortfolio.update_portfolio_val();
                    double val = yourPortfolio.get_portfolio_val();
                    cout << "Stock sold successfully." << '\n'
                        << "New portfolio value: " << to_string(val) << '\n'
                        << "New portfolio cash balance: "
                        << to_string(yourPortfolio.get_cash_balance()) << endl;
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                string option_sell;
                cout << "What option contract would you like to sell?" << endl;
                cin >> option_sell;

                double amount;
                cout << "How many?" << endl;
                cin >> amount;

                try {
                    yourPortfolio.buy_option_contract(option_sell, amount);
                    cout << "Option contract bought successfully. " << endl;
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        case Deposit:
        {
            double deposit;
            cout << "How much would you like to deposit? ";
            cin >> deposit;

            yourPortfolio.deposit_more_cash(deposit);
            cout << "Deposit successful!" << '\n' << "New cash balance: "
                << to_string(yourPortfolio.get_cash_balance()) << endl;
            break;
        }
        case Withdraw:
        {
            double withdrawal;
            cout << "How much would you like to withdraw?" << endl;
            cin >> withdrawal;

            try {
                yourPortfolio.withdraw_more_cash(withdrawal);
                cout << "Withdrawal successful." << '\n' << "New cash balance: "
                    << to_string(yourPortfolio.get_cash_balance()) << endl;
            } catch (exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case Price:
        {
            string asset = stock_or_option("price");
            if (asset == "stock") {
                string stock_name;
                cout << "What stock would you like to get the price of?" << endl;
                cin >> stock_name;

                try {
                    double price = stod(yourPortfolio.get_stock_prices().at(stock_name));
                    cout << stock_name << " currently costs " << to_string(price)
                        << " per share." << endl;
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            } else {
                try {
                    yourPortfolio.price_option(); 
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
            }
            break;
        }
        case View:
        {
            cout << "Your current cash balance is " << to_string(yourPortfolio.get_cash_balance())
                << '\n' << "Your current portfolio value is " << to_string(yourPortfolio.get_portfolio_val())
                << endl;
            break;
        }
        default:
        cout << "testing";
    }

    return 0;
}