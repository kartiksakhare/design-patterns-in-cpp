# Factory Method Pattern in C++

---

## 🟦 What is the Factory Method Pattern?

The **Factory Method Pattern** is a creational design pattern that defines an interface for creating objects, but allows subclasses or a factory class to decide which class to instantiate.  
It lets a class defer instantiation to subclasses or a dedicated factory, promoting loose coupling and flexibility.

---

## 🟦 Why Use the Factory Method Pattern?

- To encapsulate object creation logic and avoid direct use of `new` in client code.
- To support the creation of objects from a family of related classes.
- To make code more flexible and open to extension (Open/Closed Principle).
- To decouple client code from concrete classes.

---

## 🟦 Advantages of Factory Method

- **Encapsulation:** Centralizes object creation logic.
- **Flexibility:** Easily add new product types without modifying client code.
- **Decoupling:** Client code depends only on the product interface, not concrete classes.
- **Single Responsibility:** Creation logic is separated from business logic.

---

## 🟦 Disadvantages of Factory Method

- **More Classes:** May introduce additional classes (factories).
- **Complexity:** Can be overkill for simple object creation needs.

---

## ✅ Key Features of the Factory Method Pattern

- **Product Interface:**  
  An abstract base class (e.g., `CoffeeMachine`) defines the interface for products.

- **Concrete Products:**  
  Derived classes (e.g., `SimpleCoffeeMachine`, `EspressoMachine`, `CappuccinoMachine`) implement the product interface.

- **Factory Class:**  
  A factory class (e.g., `CoffeeMachineFactory`) provides a static method to create products based on input parameters.

- **Polymorphism:**  
  Client code works with the product interface, enabling easy extension and substitution.

---

## 🛠️ Scope for Further Modifications

- **Enum or String-based Selection:**  
  Use enums or strings for type selection instead of raw integers for better readability and safety.

- **Registration Mechanism:**  
  Allow dynamic registration of new product types at runtime.

- **Parameterization:**  
  Allow passing parameters to the factory for more customized object creation.

- **Error Handling:**  
  Return `nullptr` or throw exceptions for unknown types.

---

## ⚠️ What NOT to Do

- Do **not** hardcode object creation throughout your codebase.
- Do **not** let client code depend on concrete product classes.
- Do **not** forget to handle unknown or invalid types gracefully.

---

## 🟦 Interview Questions and Answers

### 1. What is the Factory Method pattern?
**Answer:**  
A creational pattern that provides an interface for creating objects in a superclass, but allows subclasses or a factory to alter the type of objects that will be created.

**Example:**  
```cpp
class CoffeeMachine {
public:
    virtual void brew() = 0;
    virtual ~CoffeeMachine() = default;
};
class SimpleCoffeeMachine : public CoffeeMachine {
public:
    void brew() override {
        std::cout << "Brewing coffee in a simple coffee machine." << std::endl;
    }
};
class CoffeeMachineFactory {
public:
    static std::unique_ptr<CoffeeMachine> createMachine(int type) {
        switch (type) {
            case 1: return std::unique_ptr<CoffeeMachine>(new SimpleCoffeeMachine());
            // ... other cases ...
            default: return nullptr;
        }
    }
};
```

---

### 2. When would you use the Factory Method pattern?
**Answer:**  
When you need to create objects from a family of related classes and want to encapsulate the creation logic.

---

### 3. How do you implement the Factory Method pattern in C++?
**Answer:**  
- Define an abstract product interface.
- Implement concrete product classes.
- Create a factory class with a method that returns a product pointer based on input.

---

### 4. How do you handle unknown types in the factory?
**Answer:**  
Return `nullptr` and optionally log an error or throw an exception.

---

### 5. How do you demonstrate the Factory Method pattern in code?
**Answer:**  
- Use the factory to create product objects.
- Use the product interface to interact with the objects.
- Check for `nullptr` before using the returned object.

**Example:**
```cpp
auto machine = CoffeeMachineFactory::createMachine(1);
if (machine) machine->brew();
else std::cout << "Unknown machine type could not be created." << std::endl;
```

---

## 🟦 Example Usage

```cpp
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
```

---