# Stock-and-Option-Simulator
This project allows you to buy, sell, and price, stocks and options in a mock self-service investment app.


Compiling instructions:
Note: This project was developed and tested using M1 MacOS.

To run this program from the terminal, first change directories into the path where you
have Stock-and-Option-Simulator downloaded. Then, compile by running the following
command.

g++ -std=c++11 -o simulation portfolio.cpp trading.cpp main.cpp

Run the program using:

./simulation

You will then enter a main menu where you will enter your desired starting balance:

Hello! Welcome to our Stock and Option simulator. 
What would you like your starting balance to be? Example: 100 or 100.00 -->

After entering a starting balance, you will then be given the following options:

What would you like to do? Enter a number 1-8.
Buy (1) | Sell (2) | Deposit (3) | Withdraw (4) | Price (5) | View Info (6) |
View History (7) | Quit Simulation (8)

Chose which operation you would like to complete by entering the corresponding number
with the action. Directions for each action will appear after every command, continue
performing commands until you are done, then quit the simulation by entering 8. 
