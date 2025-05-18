#include<iostream>
#include<vector>
#include<string>

// Abstract Prototype: CoffeeMachine
class CoffeeMachine {
public:
    // Constructor with default state
    CoffeeMachine(std::string name = "Generic", int cupSize = 1, bool milk = false, int sugar = 0)
        : name(name), cupSize(cupSize), milk(milk), sugar(sugar) {}

    // Pure virtual clone method for Prototype pattern
    virtual CoffeeMachine* clone() const = 0;

    // Pure virtual brew method to be implemented by concrete prototypes
    virtual void brew() = 0;

    // Display current state/configuration of the machine
    virtual void display() const {
        std::cout << "Name: " << name
                  << ", Cup Size: " << cupSize
                  << ", Milk: " << (milk ? "Yes" : "No")
                  << ", Sugar: " << sugar << std::endl;
    }

    // Setters for state customization
    void setCupSize(int size) { cupSize = size; }
    void setMilk(bool m) { milk = m; }
    void setSugar(int s) { sugar = s; }

    // Virtual destructor for safe cleanup of derived objects
    virtual ~CoffeeMachine() {}
protected:
    std::string name;
    int cupSize; // 1=small, 2=medium, 3=large
    bool milk;
    int sugar;
};

// Concrete Prototype: SimpleCoffeeMachine
class SimpleCoffeeMachine : public CoffeeMachine {
public:
    SimpleCoffeeMachine() : CoffeeMachine("Simple", 1, false, 0) {}
    // Copy constructor for cloning
    SimpleCoffeeMachine(const SimpleCoffeeMachine& other) : CoffeeMachine(other) {}
    // Returns a copy of this object
    CoffeeMachine* clone() const override {
        return new SimpleCoffeeMachine(*this);
    }
    // Implementation of brewing for simple machine
    void brew() override {
        std::cout << "Brewing coffee in a simple coffee machine." << std::endl;
        display();
    }
};

// Concrete Prototype: EspressoMachine
class EspressoMachine : public CoffeeMachine {
public:
    EspressoMachine() : CoffeeMachine("Espresso", 1, false, 0) {}
    EspressoMachine(const EspressoMachine& other) : CoffeeMachine(other) {}
    CoffeeMachine* clone() const override {
        return new EspressoMachine(*this);
    }
    void brew() override {
        std::cout << "Brewing espresso in an espresso machine." << std::endl;
        display();
    }
};

// Concrete Prototype: AdvancedCoffeeMachine
class AdvancedCoffeeMachine : public CoffeeMachine {
public:
    AdvancedCoffeeMachine() : CoffeeMachine("Advanced", 2, true, 2) {}
    AdvancedCoffeeMachine(const AdvancedCoffeeMachine& other) : CoffeeMachine(other) {}
    CoffeeMachine* clone() const override {
        return new AdvancedCoffeeMachine(*this);
    }
    void brew() override {
        std::cout << "Brewing coffee in an advanced coffee machine." << std::endl;
        display();
    }
};

// Manager class to handle prototypes and cloning
class CoffeeMachineManager {
public:
    // Factory method to create a new machine by cloning the prototype
    static CoffeeMachine* createMachine(int machineType);

    // Cleanup function to delete prototypes and prevent memory leaks
    static void cleanupPrototypes();

    ~CoffeeMachineManager(){}
private:
    // Array of prototype objects (static, shared by all instances)
    static CoffeeMachine* machines[3];
};

// Initialize the prototype objects
CoffeeMachine* CoffeeMachineManager::machines[3] = {
    new SimpleCoffeeMachine(),
    new EspressoMachine(),
    new AdvancedCoffeeMachine()
};

// Clone the appropriate prototype based on machineType
CoffeeMachine* CoffeeMachineManager::createMachine(int machineType) {
    if (machineType < 0 || machineType >= 3) {
        std::cerr << "Invalid machine type." << std::endl;
        return nullptr;
    }
    return machines[machineType]->clone();
}

// Delete all prototype objects and set pointers to nullptr
void CoffeeMachineManager::cleanupPrototypes() {
    for (int i = 0; i < 3; ++i) {
        delete machines[i];
        machines[i] = nullptr;
    }
}

int main() {
    // Vector to store created coffee machines
    std::vector<CoffeeMachine*> myMachines(3);

    // Create machines by cloning prototypes
    CoffeeMachine* simpleMachine = CoffeeMachineManager::createMachine(0);
    CoffeeMachine* espressoMachine = CoffeeMachineManager::createMachine(1);
    CoffeeMachine* advancedMachine = CoffeeMachineManager::createMachine(2);

    // Check if machines were created successfully
    if (!simpleMachine || !espressoMachine || !advancedMachine) {
        std::cerr << "Failed to create coffee machines." << std::endl;
        CoffeeMachineManager::cleanupPrototypes();
        return 1;
    }

    // Customize state of each machine
    simpleMachine->setCupSize(2); // medium
    simpleMachine->setMilk(true);
    simpleMachine->setSugar(1);

    espressoMachine->setCupSize(1); // small
    espressoMachine->setMilk(false);
    espressoMachine->setSugar(0);

    advancedMachine->setCupSize(3); // large
    advancedMachine->setMilk(true);
    advancedMachine->setSugar(3);

    // Store created machines in the vector
    myMachines[0] = simpleMachine;
    myMachines[1] = espressoMachine;
    myMachines[2] = advancedMachine;

    // Brew coffee using each machine (shows state)
    for(size_t i = 0; i < myMachines.size(); i++) {
        myMachines[i]->brew();
    }

    // Demonstrate cloning: clone the simple machine, customize, and brew
    CoffeeMachine* clonedMachine = simpleMachine->clone();
    clonedMachine->setCupSize(1); // small
    clonedMachine->setMilk(false);
    clonedMachine->setSugar(0);
    std::cout << "Cloned and customized SimpleCoffeeMachine:" << std::endl;
    clonedMachine->brew();
    delete clonedMachine; // Prevent memory leak

    // Clean up created machines
    for(size_t i = 0; i < myMachines.size(); i++) {
        delete myMachines[i];
    }

    // Clean up prototype objects
    CoffeeMachineManager::cleanupPrototypes();

    return 0;
}