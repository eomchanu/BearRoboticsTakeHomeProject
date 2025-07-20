#include "../include/MockBank.h"

void MockBank::addAccount(const Account& account, int pinCode) {
    accounts.push_back({account, pinCode});
}

bool MockBank::verifyPin(const Card& card, int inputPin) const {
    for (const auto& info : accounts) {
        if (info.account.getId() == card.accountId && info.pinCode == inputPin) {
            return true;
        }
    }
    return false;
}

std::optional<Account*> MockBank::findAccount(int accountId) {
    for (auto& info : accounts) {
        if (info.account.getId() == accountId) {
            return &(info.account);
        }
    }
    return std::nullopt;
}