#pragma once

class CashBinInterface {
public:
    virtual ~CashBinInterface() = default;
    virtual bool dispense(int amount) = 0;
    virtual bool accept(int amount) = 0;
};