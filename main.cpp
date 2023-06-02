#include "portfolio.hpp"
#include "trading.hpp"

#include <iostream>

using namespace std;

namespace {

    // Intial pop-up main menu with directions for user input
    void main_menu() {
        cout << "What would you like to do? Enter a number 1-8." << '\n'
            << "Buy (1) | Sell (2) | Deposit (3) | "
            << "Withdraw (4) | Price (5) | View Info (6) | "
            << "View History (7) | Quit Simulation (8)" << endl;
    }

    // helper to choose either a stock or an option given whether user is buying or 
    // selling
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

// main execultable to run the simulator given user input
int main() {
    double starting_bal;

    // input starting balance 
    cout << "Hello! Welcome to our Stock and Option simulator. "
        << "\nWhat would you like your starting balance to be? "
        << "Example: 100 or 100.00 --> " << flush;
    cin >> starting_bal;

    // make a portfolio given a starting balance
    StockPortfolio yourPortfolio(starting_bal);

    // different choice options to interact with program
    enum Choice {
        Buy = 1,
        Sell = 2,
        Deposit = 3,
        Withdraw = 4,
        Price = 5,
        View = 6,
        History = 7,
        Quit = 8
        };

    int selection = -1;

    // reads in selection and runs necessary methods
    while (selection) {
        cout << "*******************************************************" << endl;
        main_menu();
        cin >> selection;

        switch(selection) {
            case Buy:
            {
                string asset = stock_or_option("buy");
                if (asset == "stock") {

                    string stock_buy;
                    cout << "What stock would you like to buy?"
                        << " Press 1 to see available stocks." << endl;
                    cin >> stock_buy;
                    if (stock_buy == "1") {
                        yourPortfolio.show_stocks();
                        cout << "What stock would you like to buy? " << endl;
                        cin >> stock_buy;
                    }
                    try {
                        double amount;
                        string price = yourPortfolio.get_stock_price(stock_buy);
                        cout << stock_buy << " currently costs " << price
                        << " per share.\nHow many shares would you like to buy?" << endl;
                        cin >> amount;
                        yourPortfolio.buy_stock(stock_buy, amount);
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
                    cout << "What option contract would you like to buy?"
                        << " Press 1 to see available option contracts." << endl;
                    cin >> option_buy;
                    if (option_buy == "1") {
                        yourPortfolio.show_options();
                        cout << "What option contract would you like to buy?" << endl;
                        cin >> option_buy;
                    }

                    try {
                        double amount;
                        double price = yourPortfolio.get_option_price(option_buy);
                        cout << option_buy << " currently costs "
                        << to_string(price) << " per contract. "
                        << "How many contracts would you like to buy?" << endl;
                        cin >> amount;
                        yourPortfolio.buy_option_contract(option_buy, amount);
                        double val = yourPortfolio.get_portfolio_val();
                        cout << "Option bought successfully." << '\n'
                            << "New portfolio value: " << to_string(val) << '\n'
                            << "New portfolio cash balance: "
                            << to_string(yourPortfolio.get_cash_balance()) << endl;
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
                    if (yourPortfolio.get_my_stocks().size() == 0) {
                        cout << "You own no stocks to sell." << endl;
                        break;
                    } else {
                        string stock_sell;
                        cout << "What stock would you like to sell?" << endl;
                        cin >> stock_sell;

                        double amount;
                        cout << "How many shares?" << endl;
                        cin >> amount;

                        try {
                            yourPortfolio.sell_stock(stock_sell, amount);
                            double val = yourPortfolio.get_portfolio_val();
                            cout << "Stock sold successfully." << '\n'
                                << "New portfolio value: " << to_string(val) << '\n'
                                << "New portfolio cash balance: "
                                << to_string(yourPortfolio.get_cash_balance()) << endl;
                        } catch (exception& e) {
                            cout << e.what() << endl;
                        }
                    }
                } else {
                    if (yourPortfolio.get_my_options().size() == 0) {
                        cout << "You own no options to sell." << endl;
                        break;
                    } else {
                        string option_sell;
                        cout << "What option contract would you like to sell?" << endl;
                        cin >> option_sell;

                        double amount;
                        cout << "How many?" << endl;
                        cin >> amount;

                        try {
                            yourPortfolio.sell_option_contract(option_sell, amount);
                            double val = yourPortfolio.get_portfolio_val();
                            cout << "Option contract sold successfully." << '\n'
                                << "New portfolio value: " << to_string(val) << '\n'
                                << "New portfolio cash balance: "
                                << to_string(yourPortfolio.get_cash_balance()) << endl;
                        } catch (exception& e) {
                            cout << e.what() << endl;
                        }
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
                        yourPortfolio.eval_option(); 
                    } catch (exception& e) {
                        cout << e.what() << endl;
                    }
                }
                break;
            }
            case View:
                cout << "Your current cash balance is " << to_string(yourPortfolio.get_cash_balance())
                    << '\n' << "Your current portfolio value is " << to_string(yourPortfolio.get_portfolio_val())
                    << endl;
                yourPortfolio.view_my_stocks();
                yourPortfolio.view_my_options();
                break;
            case History:
                yourPortfolio.view_transaction_history();
                break;
            case Quit:
                cout << "Thank you for using our Stock and Option simulator. "
                    << "Have a nice day!" << endl;
                exit(0);
            default:
            cout << "Invalid input.";
            break;
        }
    }
        return 0;
}