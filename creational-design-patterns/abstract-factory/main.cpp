#include <iostream>
#include <memory>

// Abstract Product A: CoffeeMachine
// Defines the interface for all coffee machines
class CoffeeMachine {
public:
    // Brew method to be implemented by all concrete coffee machines
    virtual void brew() = 0;
    // Virtual destructor for safe polymorphic deletion
    virtual ~CoffeeMachine() = default;
};

// Concrete Product A1: SimpleCoffeeMachine
class SimpleCoffeeMachine : public CoffeeMachine {
public:
    // Implements brewing for a simple coffee machine
    void brew() override {
        std::cout << "Brewing coffee in a simple coffee machine." << std::endl;
    }
};

// Concrete Product A2: EspressoMachine
class EspressoMachine : public CoffeeMachine {
public:
    // Implements brewing for an espresso machine
    void brew() override {
        std::cout << "Brewing espresso in an espresso machine." << std::endl;
    }
};

// Abstract Product B: Coffee
// Defines the interface for all coffee types
class Coffee {
public:
    // Prepare method to be implemented by all concrete coffee types
    virtual void prepare() = 0;
    // Virtual destructor for safe polymorphic deletion
    virtual ~Coffee() = default;
};

// Concrete Product B1: SimpleCoffee
class SimpleCoffee : public Coffee {
public:
    // Implements preparation for simple coffee
    void prepare() override {
        std::cout << "Preparing simple coffee." << std::endl;
    }
};

// Concrete Product B2: Espresso
class Espresso : public Coffee {
public:
    // Implements preparation for espresso
    void prepare() override {
        std::cout << "Preparing espresso." << std::endl;
    }
};

// Abstract Factory: CoffeeFactory
// Declares creation methods for each abstract product
class CoffeeFactory {
public:
    virtual std::unique_ptr<CoffeeMachine> createCoffeeMachine() = 0;
    virtual std::unique_ptr<Coffee> createCoffee() = 0;
    virtual ~CoffeeFactory() = default;
};

// Concrete Factory 1: SimpleCoffeeFactory
// Creates simple coffee and simple coffee machine
class SimpleCoffeeFactory : public CoffeeFactory {
public:
    std::unique_ptr<CoffeeMachine> createCoffeeMachine() override {
        return std::make_unique<SimpleCoffeeMachine>();
    }
    std::unique_ptr<Coffee> createCoffee() override {
        return std::make_unique<SimpleCoffee>();
    }
};

// Concrete Factory 2: EspressoFactory
// Creates espresso and espresso machine
class EspressoFactory : public CoffeeFactory {
public:
    std::unique_ptr<CoffeeMachine> createCoffeeMachine() override {
        return std::make_unique<EspressoMachine>();
    }
    std::unique_ptr<Coffee> createCoffee() override {
        return std::make_unique<Espresso>();
    }
};

int main() {
    // Prompt user for coffee type
    int choice;
    std::cout << "Enter coffee type (simple:1 / espresso:2): ";
    if (!(std::cin >> choice)) {
        std::cout << "Invalid input!" << std::endl;
        return 1;
    }

    // Factory pointer to create products
    std::unique_ptr<CoffeeFactory> factory;

    // Select the appropriate factory based on user input
    if (choice == 1) {
        factory = std::make_unique<SimpleCoffeeFactory>();
    } else if (choice == 2) {
        factory = std::make_unique<EspressoFactory>();
    } else {
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }

    // Create products using the selected factory
    auto coffeeMachine = factory->createCoffeeMachine();
    auto coffee = factory->createCoffee();

    // Use the created products
    coffeeMachine->brew();
    coffee->prepare();

    // All memory is managed by unique_ptr, no manual deletion needed
    return 0;
}