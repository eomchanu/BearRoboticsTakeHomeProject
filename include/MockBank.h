#pragma once
#include "BankInterface.h"
#include <vector>

class MockBank : public BankInterface {
public:
    void addAccount(const Account& account, int pinCode);

    bool verifyPin(const Card& card, int inputPin) const override;
    std::optional<Account*> findAccount(int accountId) override;

private:
    // Groups an account with its PIN for easy management. Kind of simplify
    // (Card info is managed elsewhere maybe)
    struct AccountInfo {
        Account account;
        int pinCode;
    };
    std::vector<AccountInfo> accounts;
};