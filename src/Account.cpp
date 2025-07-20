#include "Account.h"

Account::Account(int id, int initial_balance)
    : id(id), balance(initial_balance) {}

int Account::getId() const {
    return id;
}

int Account::getBalance() const {
    return balance;
}

bool Account::deposit(int amount) {
    if (amount <= 0) return false;
    balance += amount;
    
    return true;
}

bool Account::withdraw(int amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;

    return true;
}