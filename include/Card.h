#pragma once
#include <string>

// Each card is connected to specific account
struct Card {
    std::string cardNumber;
    int pinCode;
    int accountId;
};