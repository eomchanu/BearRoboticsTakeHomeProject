#pragma once
#include "Account.h"
#include "Card.h"
#include <optional>

class BankInterface {
public:
    virtual ~BankInterface() = default;
    virtual bool verifyPin(const Card& card, int inputPin) const = 0;
    virtual std::optional<Account*> findAccount(int accountId) = 0;
};