#include <iostream>
#include <memory>

// Abstract Product: Defines the interface for all coffee machines
class CoffeeMachine {
public:
    // Brew method to be implemented by all concrete coffee machines
    virtual void brew() = 0;
    // Virtual destructor for safe polymorphic deletion
    virtual ~CoffeeMachine() = default;
};

// Concrete Product: SimpleCoffeeMachine
class SimpleCoffeeMachine : public CoffeeMachine {
public:
    // Implements brewing for a simple coffee machine
    void brew() override {
        std::cout << "Brewing coffee in a simple coffee machine." << std::endl;
    }
};

// Concrete Product: EspressoMachine
class EspressoMachine : public CoffeeMachine {
public:
    // Implements brewing for an espresso machine
    void brew() override {
        std::cout << "Brewing espresso in an espresso machine." << std::endl;
    }
};

// Concrete Product: CappuccinoMachine
class CappuccinoMachine : public CoffeeMachine {
public:
    // Implements brewing for a cappuccino machine
    void brew() override {
        std::cout << "Brewing cappuccino in a cappuccino machine." << std::endl;
    }
};

// Factory class: Responsible for creating coffee machines based on type
class CoffeeMachineFactory {
public:
    // Static factory method to create coffee machines
    // type: 1 = Simple, 2 = Espresso, 3 = Cappuccino
    static std::unique_ptr<CoffeeMachine> createMachine(int type) {
        switch (type)
        {
            case 1:
                return std::make_unique<SimpleCoffeeMachine>();
            case 2:
                return std::make_unique<EspressoMachine>();
            case 3:
                return std::make_unique<CappuccinoMachine>();
            default:
                std::cerr << "Error: Unknown coffee machine type (" << type << "). Returning nullptr." << std::endl;
                return nullptr;
        }
    }
};

int main() {
    // Create different types of coffee machines using the factory
    auto machineOne = CoffeeMachineFactory::createMachine(1); // Simple
    auto machineTwo = CoffeeMachineFactory::createMachine(2); // Espresso
    auto machineThree = CoffeeMachineFactory::createMachine(3); // Cappuccino
    auto unknownMachine = CoffeeMachineFactory::createMachine(99); // Unknown type

    // Brew coffee using each machine, check for nullptr
    if (machineOne) machineOne->brew();
    if (machineTwo) machineTwo->brew();
    if (machineThree) machineThree->brew();
    if (unknownMachine)
        unknownMachine->brew();
    else
        std::cout << "Unknown machine type could not be created." << std::endl;

    // No need to manually delete machines; unique_ptr handles cleanup
    return 0;
}