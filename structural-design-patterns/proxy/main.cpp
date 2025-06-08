/*
 * Proxy Pattern Example: Secure access to a bank account.
 *
 * - Subject: BankAccount (interface for bank account operations)
 * - RealSubject: RealBankAccount (actual bank account implementation)
 * - Proxy: BankAccountProxy (controls access and adds authentication)
 *
 * This demonstrates how the Proxy pattern can add security, logging, or other logic
 * to an object without changing its interface or implementation.
 */

#include <iostream>
#include <memory>

// Subject interface
class BankAccount {
public:
    virtual void deposit(double amount, const std::string& pin) = 0;
    virtual void withdraw(double amount, const std::string& pin) = 0;
    virtual double getBalance(const std::string& pin) const = 0;
    virtual ~BankAccount() {}
};

// RealSubject
class RealBankAccount : public BankAccount {
private:
    double balance;
public:
    RealBankAccount(double initialBalance = 0.0) : balance(initialBalance) {}
    void deposit(double amount, const std::string&) override {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: " << amount << ", New Balance: " << balance << std::endl;
        } else {
            std::cout << "Deposit amount must be positive." << std::endl;
        }
    }
    void withdraw(double amount, const std::string&) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew: " << amount << ", New Balance: " << balance << std::endl;
        } else {
            std::cout << "Withdrawal amount must be positive and less than or equal to the balance." << std::endl;
        }
    }
    double getBalance(const std::string&) const override {
        return balance;
    }
};

// Proxy
class BankAccountProxy : public BankAccount {
private:
    std::shared_ptr<RealBankAccount> realAccount;
    std::string correctPin;
public:
    BankAccountProxy(double initialBalance, const std::string& pin)
        : realAccount(std::make_shared<RealBankAccount>(initialBalance)), correctPin(pin) {}

    bool authenticate(const std::string& pin) const {
        return pin == correctPin;
    }

    void deposit(double amount, const std::string& pin) override {
        if (authenticate(pin)) {
            realAccount->deposit(amount, pin);
        } else {
            std::cout << "Authentication failed. Cannot deposit." << std::endl;
        }
    }
    void withdraw(double amount, const std::string& pin) override {
        if (authenticate(pin)) {
            realAccount->withdraw(amount, pin);
        } else {
            std::cout << "Authentication failed. Cannot withdraw." << std::endl;
        }
    }
    double getBalance(const std::string& pin) const override {
        if (authenticate(pin)) {
            return realAccount->getBalance(pin);
        } else {
            std::cout << "Authentication failed. Cannot retrieve balance." << std::endl;
            return 0.0;
        }
    }
};

int main() {
    std::string pin = "1234";
    BankAccountProxy accountProxy(100.0, pin);

    // Successful deposit
    accountProxy.deposit(50.0, pin);
    std::cout << "Current Balance: " << accountProxy.getBalance(pin) << std::endl;

    // Successful withdrawal
    accountProxy.withdraw(30.0, pin);
    std::cout << "Current Balance: " << accountProxy.getBalance(pin) << std::endl;

    // Failed withdrawal (insufficient balance)
    accountProxy.withdraw(150.0, pin);

    // Attempting to access balance with wrong pin
    std::cout << "Attempting to get balance with wrong pin:" << std::endl;
    std::string wrongPin = "wrong_pin";
    accountProxy.deposit(20.0, wrongPin); // Should fail due to authentication
    std::cout << "Balance with wrong pin: " << accountProxy.getBalance(wrongPin) << std::endl;

    return 0;
}