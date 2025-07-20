#include <iostream>
#include "../include/Account.h"
#include "../include/Card.h"

int main() {
    // Hardcoded account and card creation
    Account acc(1, 100);
    Card card = {"1111-2222-3333-4444", 1234, 1};

    int inputPin;
    std::cout << "Card inserted into the ATM." << std::endl;
    std::cout << "Please enter your PIN: ";
    std::cin >> inputPin;

    // PIN validation
    if (inputPin != card.pinCode) {
        std::cout << "Incorrect PIN. Exiting transaction." << std::endl;
        return 0;
    }

    std::cout << "Authentication success!" << std::endl;

    while (true) {
        // ATM menu
        std::cout << "\n--- ATM Menu ---\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Exit\n";
        std::cout << "Select menu option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) { // Check balance
            std::cout << "Current balance: $" << acc.getBalance() << "\n";
        }
        else if (choice == 2) { // Deposit
            int amount;
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            if (acc.deposit(amount)) {
                std::cout << "$" << amount << " deposited successfully!\n";
            } else {
                std::cout << "Invalid amount entered.\n";
            }
        }
        else if (choice == 3) { // Withdraw
            int amount;
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            if (acc.withdraw(amount)) {
                std::cout << "$" << amount << " withdrawn successfully!\n";
            } else {
                std::cout << "Invalid amount entered.\n";
            }
        }
        else if (choice == 4) { // Exit
            std::cout << "Bye bye~\n";
            break;
        }
        else {
            std::cout << "Invalid selection. Please try again.\n";
        }
    }

    return 0;
}