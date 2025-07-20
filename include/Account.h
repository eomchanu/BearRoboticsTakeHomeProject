#pragma once

class Account {
public:
    Account(int id, int initial_balance = 0);

    int getId() const;
    int getBalance() const;

    bool deposit(int amount);
    bool withdraw(int amount);

private:
    int id;
    int balance;
};