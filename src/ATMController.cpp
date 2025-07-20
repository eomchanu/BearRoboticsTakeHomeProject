#include "ATMController.h"

ATMController::ATMController(BankInterface& bank, CashBinInterface& cashBin)
    : bank(bank), cashBin(cashBin) {}

bool ATMController::insertCard(const Card& card) {
    if (currentCard != nullptr) return false;
    currentCard = &card;
    isAuthenticated = false;
    currentAccount = nullptr;
    return true;
}

bool ATMController::enterPin(int pin) {
    if (currentCard == nullptr) return false;
    if (bank.verifyPin(*currentCard, pin)) {
        isAuthenticated = true;
        return true;
    }
    return false;
}

bool ATMController::selectAccount(int accountId) {
    if (!isAuthenticated) return false;
    auto accountOpt = bank.findAccount(accountId);
    if (accountOpt.has_value()) {
        currentAccount = accountOpt.value();
        return true;
    }
    return false;
}

int ATMController::checkBalance() const {
    if (currentAccount == nullptr) return -1;
    return currentAccount->getBalance();
}

bool ATMController::deposit(int amount) {
    if (currentAccount == nullptr) return false;
    if (!cashBin.accept(amount)) return false;
    return currentAccount->deposit(amount);
}

bool ATMController::withdraw(int amount) {
    if (currentAccount == nullptr) return false;
    if (currentAccount->getBalance() < amount) return false;
    if (!cashBin.dispense(amount)) return false;
    return currentAccount->withdraw(amount);
}

void ATMController::ejectCard() {
    currentCard = nullptr;
    currentAccount = nullptr;
    isAuthenticated = false;
}