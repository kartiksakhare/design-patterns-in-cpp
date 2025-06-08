/*
 * Decorator Pattern Example: Dynamically adding features (milk, sugar, whipped cream) to coffee.
 *
 * - Component: Coffee (interface for all coffee types)
 * - Concrete Component: SimpleCoffee (basic coffee)
 * - Decorator: CoffeeDecorator (base class for all decorators)
 * - Concrete Decorators: MilkDecorator, SugarDecorator, WhippedCreamDecorator (add features)
 *
 * This demonstrates how the Decorator pattern allows you to add responsibilities to objects
 * dynamically and transparently, without affecting other objects of the same class.
 * Each decorator wraps a Coffee object and adds its own behavior (description and cost).
 */

#include <iostream>
#include <string>
#include <memory>

// Component interface: Coffee
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};

// Concrete Component: SimpleCoffee
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }
    double cost() const override {
        return 2.0; // Base price of simple coffee
    }
};

// Decorator base class: CoffeeDecorator
class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> coffee;
public:
    explicit CoffeeDecorator(std::shared_ptr<Coffee> c) : coffee(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription();
    }
    double cost() const override {
        return coffee->cost();
    }
};

// Concrete Decorator: MilkDecorator
class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }
    double cost() const override {
        return coffee->cost() + 0.5; // Adding cost of milk
    }
};

// Concrete Decorator: SugarDecorator
class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }
    double cost() const override {
        return coffee->cost() + 0.2; // Adding cost of sugar
    }
};

// Concrete Decorator: WhippedCreamDecorator
class WhippedCreamDecorator : public CoffeeDecorator {
public:
    explicit WhippedCreamDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription() + ", Whipped Cream";
    }
    double cost() const override {
        return coffee->cost() + 1.0; // Adding cost of whipped cream
    }
};

int main() {
    // Create a simple coffee (base component)
    std::shared_ptr<Coffee> myCoffee = std::make_shared<SimpleCoffee>();

    // Dynamically decorate with milk
    myCoffee = std::make_shared<MilkDecorator>(myCoffee);
    
    // Dynamically decorate with sugar
    myCoffee = std::make_shared<SugarDecorator>(myCoffee);
    
    // Dynamically decorate with whipped cream
    myCoffee = std::make_shared<WhippedCreamDecorator>(myCoffee);

    // Output the final description and cost
    std::cout << "Description: " << myCoffee->getDescription() << std::endl;
    std::cout << "Total Cost: $" << myCoffee->cost() << std::endl;

    return 0;
}