#include <iostream>
#include "../include/Account.h"
#include "../include/Card.h"
#include "../include/MockBank.h"
#include "../include/MockCashBin.h"
#include "../include/ATMController.h"

int main() {
    // Initialize mock cash bin, bank, and account
    MockCashBin cashBin;
    MockBank bank;
    Account acc(1, 100);
    bank.addAccount(acc, 1234);

    // Create mock card linked to the above account
    Card card = {"1111-2222-3333-4444", 1234, 1};

    // Set up the ATM controller
    ATMController atm(bank, cashBin);

    // Requirements 1. Insert Card
    if (!atm.insertCard(card)) {
        std::cout << "Failed to insert card." << std::endl;
        return 1;
    }
    std::cout << "Card inserted into the ATM." << std::endl;

    int inputPin;
    std::cout << "Please enter your PIN: ";
    std::cin >> inputPin;

    // Requirements 2. Enter PIN number
    if (!atm.enterPin(inputPin)) {
        std::cout << "Incorrect PIN. Exiting transaction." << std::endl;
        atm.ejectCard();
        return 0;
    }

    // Requirements 3. Select Account
    if (!atm.selectAccount(card.accountId)) {
        std::cout << "Account not found. Exiting transaction." << std::endl;
        atm.ejectCard();
        return 0;
    }

    std::cout << "Authentication success!" << std::endl;

    // Requirements 4. See Balance/Deposit/Withdraw
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
            int balance = atm.checkBalance();
            if (balance >= 0) {
                std::cout << "Current balance: $" << balance << "\n";
            } else {
                std::cout << "Cannot check balance.\n";
            }
        }
        else if (choice == 2) { // Deposit
            int amount;
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            if (atm.deposit(amount)) {
                std::cout << "$" << amount << " deposited successfully!\n";
            } else {
                std::cout << "Deposit failed (invalid amount or ATM error).\n";
            }
        }
        else if (choice == 3) { // Withdraw
            int amount;
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            if (atm.withdraw(amount)) {
                std::cout << "$" << amount << " withdrawn successfully!\n";
            } else {
                std::cout << "Withdraw failed (invalid amount, insufficient balance, or ATM cash shortage).\n";
            }
        }
        else if (choice == 4) { // Exit
            std::cout << "\nBye bye~\n";
            atm.ejectCard();
            break;
        }
        else {
            std::cout << "Invalid selection. Please try again.\n";
        }
    }

    return 0;
}