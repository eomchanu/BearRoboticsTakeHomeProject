#include "../include/MockCashBin.h"

bool MockCashBin::dispense(int amount) {
    if (amount <= 0 || amount > cashInside) return false;
    cashInside -= amount;
    return true;
}

bool MockCashBin::accept(int amount) {
    if (amount <= 0) return false;
    cashInside += amount;
    return true;
}

int MockCashBin::getCashInside() const {
    return cashInside;
}