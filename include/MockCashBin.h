#pragma once
#include "CashBinInterface.h"

class MockCashBin : public CashBinInterface {
public:
    bool dispense(int amount) override;
    bool accept(int amount) override;

    int getCashInside() const;
private:
    int cashInside = 10000; // Assume this ATM has $10,000
};