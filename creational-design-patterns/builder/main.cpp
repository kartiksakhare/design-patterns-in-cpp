#include<iostream>
#include<string>

// Forward declaration of CoffeeBuilder for use in Coffee class
class CoffeeBuilder;

// Coffee class represents the product being built
class Coffee {
private:
    // Name of the person who requested the coffee
    std::string requestorName;
public:
    // Coffee properties
    bool isHot = false, hasMilk = false, hasSugar = false;
    double cost = 0.0;

    // Constructor initializes the requestor's name
    Coffee(std::string requestorName) : requestorName(requestorName){}

    // Grant CoffeeBuilder access to private members
    friend class CoffeeBuilder;

    // Static method to start building a Coffee object
    static CoffeeBuilder create(std::string requestorName);

    // Getter for requestorName
    std::string getRequestorName() const { return requestorName; }

    // Individual getters for properties
    bool getIsHot() const { return isHot; }
    bool getHasMilk() const { return hasMilk; }
    bool getHasSugar() const { return hasSugar; }
    double getCost() const { return cost; }

    // Returns a string describing the coffee
    std::string getDescription() const {
        std::string desc = (isHot ? "Hot" : "Cold");
        desc += " coffee";
        if (hasMilk) desc += " with milk";
        else desc += " without milk";
        if (hasSugar) desc += " and sugar";
        else desc += " and no sugar";
        desc += " for " + requestorName;
        desc += " ($" + std::to_string(cost) + ")";
        return desc;
    }
};

// CoffeeBuilder class helps in building Coffee objects step by step
class CoffeeBuilder {
private:
    // The Coffee object being built
    Coffee coffee;
public:
    // Constructor initializes the Coffee object with the requestor's name
    CoffeeBuilder(std::string requestorName) : coffee(requestorName) {}

    // Conversion operator to allow implicit conversion to Coffee
    operator Coffee() const { return coffee; }

    // Explicit build method to get the Coffee object
    Coffee build() const {
        validate(); // Ensure the coffee is valid before returning
        return coffee;
    }

    // Validate the current coffee configuration
    void validate() const {
        if (coffee.requestorName.empty()) {
            throw std::runtime_error("Requestor name cannot be empty.");
        }
        if (coffee.cost < 0.0) {
            throw std::runtime_error("Cost cannot be negative.");
        }
        // Add more validation rules as needed
    }

    // Reset the builder to build a new coffee (reuse the builder)
    CoffeeBuilder& reset(std::string requestorName) {
        coffee = Coffee(requestorName);
        return *this;
    }

    // Change the requestor's name during building
    CoffeeBuilder& setRequestorName(const std::string& name) {
        coffee.requestorName = name;
        return *this;
    }

    // Methods to set various properties of Coffee
    CoffeeBuilder& makeHot();
    CoffeeBuilder& makeCold();
    CoffeeBuilder& addMilk();
    CoffeeBuilder& removeMilk();
    CoffeeBuilder& addSugar();
    CoffeeBuilder& removeSugar();
    CoffeeBuilder& costs(double cost);    
};

// Implementation of static create method to start the builder
CoffeeBuilder Coffee::create(std::string requestorName) {
    return CoffeeBuilder{requestorName};
}

// Set the coffee to hot
CoffeeBuilder& CoffeeBuilder::makeHot() {
    coffee.isHot = true;
    return *this;
}

// Set the coffee to cold
CoffeeBuilder& CoffeeBuilder::makeCold() {
    coffee.isHot = false;
    return *this;
}

// Add milk to the coffee
CoffeeBuilder& CoffeeBuilder::addMilk() {
    coffee.hasMilk = true;
    return *this;
}

// Remove milk from the coffee
CoffeeBuilder& CoffeeBuilder::removeMilk() {
    coffee.hasMilk = false;
    return *this;
}

// Add sugar to the coffee
CoffeeBuilder& CoffeeBuilder::addSugar() {
    coffee.hasSugar = true;
    return *this;
}

// Remove sugar from the coffee
CoffeeBuilder& CoffeeBuilder::removeSugar() {
    coffee.hasSugar = false;
    return *this;
}

// Set the cost of the coffee
CoffeeBuilder& CoffeeBuilder::costs(double cost) {
    coffee.cost = cost;
    return *this;
}

int main() {
    // Build a hot coffee with milk and a cost of $5.0 for John Doe
    Coffee coffee = Coffee::create("John Doe").makeHot().addMilk().costs(5.0);

    // Print the details of the hot coffee
    std::cout << coffee.getDescription() << "\n";
    std::cout << "Is hot: " << (coffee.getIsHot() ? "Yes" : "No") << "\n";
    std::cout << "Has milk: " << (coffee.getHasMilk() ? "Yes" : "No") << "\n";
    std::cout << "Has sugar: " << (coffee.getHasSugar() ? "Yes" : "No") << "\n";
    std::cout << "Cost: $" << coffee.getCost() << "\n";

    // Example of using the CoffeeBuilder to create a cold coffee without sugar for Jane Doe
    CoffeeBuilder builder = Coffee::create("Kevin Smith");
    Coffee coldCoffee = builder.makeCold().removeSugar().costs(4.0).build();

    // Print the details of the cold coffee
    std::cout << "\n" << coldCoffee.getDescription() << "\n";
    std::cout << "Is hot: " << (coldCoffee.getIsHot() ? "Yes" : "No") << "\n";
    std::cout << "Has milk: " << (coldCoffee.getHasMilk() ? "Yes" : "No") << "\n";
    std::cout << "Has sugar: " << (coldCoffee.getHasSugar() ? "Yes" : "No") << "\n";
    std::cout << "Cost: $" << coldCoffee.getCost() << "\n";

    // Demonstrate reset and setRequestorName
    builder.reset("Alice").makeHot().addMilk().addSugar().costs(6.0).setRequestorName("Alice Smith");
    Coffee aliceCoffee = builder.build();
    std::cout << "\n" << aliceCoffee.getDescription() << "\n";

    return 0;
}