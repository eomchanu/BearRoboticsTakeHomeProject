#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../include/Account.h"
#include "../include/Card.h"
#include "../include/MockBank.h"
#include "../include/MockCashBin.h"
#include "../include/ATMController.h"

TEST_CASE("ATMController basic flow", "[atm]") {
    MockBank bank;
    MockCashBin cashBin;
    Account acc(1, 100);
    Card card = {"1111-2222-3333-4444", 1234, 1};
    bank.addAccount(acc, 1234);

    ATMController atm(bank, cashBin);

    SECTION("Card insert and correct PIN") {
        REQUIRE(atm.insertCard(card) == true);
        REQUIRE(atm.enterPin(1234) == true);
        REQUIRE(atm.selectAccount(1) == true);
        REQUIRE(atm.checkBalance() == 100);
    }

    SECTION("Wrong PIN fails") {
        REQUIRE(atm.insertCard(card) == true);
        REQUIRE(atm.enterPin(9999) == false);
    }

    SECTION("Deposit increases balance") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        REQUIRE(atm.deposit(200) == true);
        REQUIRE(atm.checkBalance() == 300);
    }

    SECTION("Withdraw decreases balance") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        REQUIRE(atm.withdraw(50) == true);
        REQUIRE(atm.checkBalance() == 50);
    }

    SECTION("Withdraw fails if insufficient funds") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        REQUIRE(atm.withdraw(1000) == false);
        REQUIRE(atm.checkBalance() == 100);
    }
}

TEST_CASE("ATMController extended cases", "[atm][edge]") {
    MockBank bank;
    MockCashBin cashBin;
    Account acc(1, 100);
    Card card = {"1111-2222-3333-4444", 1234, 1};
    bank.addAccount(acc, 1234);
    ATMController atm(bank, cashBin);

    SECTION("Insert card twice should fail") {
        REQUIRE(atm.insertCard(card) == true);
        REQUIRE(atm.insertCard(card) == false);
    }

    SECTION("Deposit negative amount fails") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        REQUIRE(atm.deposit(-50) == false);
        REQUIRE(atm.checkBalance() == 100);
    }

    SECTION("Withdraw zero or negative amount fails") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        REQUIRE(atm.withdraw(0) == false);
        REQUIRE(atm.withdraw(-100) == false);
        REQUIRE(atm.checkBalance() == 100);
    }

    SECTION("Deposit and withdraw to zero balance") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        REQUIRE(atm.withdraw(100) == true);
        REQUIRE(atm.checkBalance() == 0);
        REQUIRE(atm.withdraw(1) == false);
        REQUIRE(atm.deposit(1) == true);
        REQUIRE(atm.checkBalance() == 1);
    }

    SECTION("Try to operate without selecting an account") {
        atm.insertCard(card);
        REQUIRE(atm.deposit(10) == false);
        REQUIRE(atm.withdraw(10) == false);
    }

    SECTION("Eject card resets state") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        atm.ejectCard();
        REQUIRE(atm.checkBalance() == -1);
        REQUIRE(atm.deposit(100) == false);
    }

    SECTION("ATM cash shortage blocks withdrawal") {
        atm.insertCard(card);
        atm.enterPin(1234);
        atm.selectAccount(1);
        for (int i = 0; i < 10000; ++i) cashBin.dispense(1);
        REQUIRE(atm.withdraw(50) == false);
    }
}