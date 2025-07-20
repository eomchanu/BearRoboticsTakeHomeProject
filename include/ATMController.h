#pragma once
#include "BankInterface.h"
#include "CashBinInterface.h"
#include "Card.h"

class ATMController {
public:
    ATMController(BankInterface& bank, CashBinInterface& cashBin);

    bool insertCard(const Card& card);
    bool enterPin(int pin);
    bool selectAccount(int accountId);

    int checkBalance() const;
    bool deposit(int amount);
    bool withdraw(int amount);

    void ejectCard();

private:
    BankInterface& bank;
    CashBinInterface& cashBin;
    const Card* currentCard = nullptr;
    Account* currentAccount = nullptr;
    bool isAuthenticated = false;
};