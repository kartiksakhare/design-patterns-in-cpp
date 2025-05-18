# Abstract Factory Pattern in C++

---

## 🟦 What is the Abstract Factory Pattern?

The **Abstract Factory Pattern** is a creational design pattern that provides an interface for creating families of related or dependent objects without specifying their concrete classes.  
It allows you to produce different types of products (e.g., machines and drinks) that are designed to work together.

---

## 🟦 Why Use the Abstract Factory Pattern?

- To create families of related objects without binding your code to specific classes.
- To ensure that products from the same family are used together.
- To encapsulate object creation logic for multiple product types.
- To make code more flexible and open to extension (Open/Closed Principle).

---

## 🟦 Advantages of Abstract Factory

- **Consistency:** Ensures that products from the same family are compatible.
- **Encapsulation:** Centralizes creation logic for related products.
- **Extensibility:** Easy to add new product families without changing client code.
- **Decoupling:** Client code depends only on abstract interfaces, not concrete classes.

---

## 🟦 Disadvantages of Abstract Factory

- **Complexity:** More classes and interfaces to manage.
- **Rigid Structure:** Adding new product types (not families) can require changes to all factories.

---

## ✅ Key Features of the Abstract Factory Pattern

- **Abstract Factory Interface:**  
  Declares creation methods for each abstract product (e.g., `createCoffeeMachine()`, `createCoffee()`).

- **Concrete Factories:**  
  Implement the abstract factory interface to create specific product families (e.g., `SimpleCoffeeFactory`, `EspressoFactory`).

- **Abstract Products:**  
  Define interfaces for each kind of product (e.g., `CoffeeMachine`, `Coffee`).

- **Concrete Products:**  
  Implement the abstract product interfaces (e.g., `SimpleCoffeeMachine`, `EspressoMachine`, `SimpleCoffee`, `Espresso`).

- **Client Code:**  
  Uses the abstract factory and product interfaces, remaining independent of concrete implementations.

---

## 🛠️ Scope for Further Modifications

- **Add More Product Families:**  
  Add new factories and product implementations for more coffee types.

- **Add More Product Types:**  
  Extend the abstract factory and all concrete factories to support new product types (e.g., `createDessert()`).

- **Parameterization:**  
  Allow factories to accept parameters for more customized product creation.

- **Registration Mechanism:**  
  Dynamically register new factories for runtime flexibility.

---

## ⚠️ What NOT to Do

- Do **not** let client code depend on concrete product classes.
- Do **not** hardcode object creation throughout your codebase.
- Do **not** break the family consistency by mixing products from different factories.

---

## 🟦 Interview Questions and Answers

### 1. What is the Abstract Factory pattern?
**Answer:**  
A creational pattern that provides an interface for creating families of related objects without specifying their concrete classes.

**Example:**  
```cpp
class CoffeeFactory {
public:
    virtual std::unique_ptr<CoffeeMachine> createCoffeeMachine() = 0;
    virtual std::unique_ptr<Coffee> createCoffee() = 0;
    virtual ~CoffeeFactory() = default;
};
```

---

### 2. When would you use the Abstract Factory pattern?
**Answer:**  
When you need to create families of related objects that must be used together, and you want to avoid specifying their concrete classes in client code.

---

### 3. How do you implement the Abstract Factory pattern in C++?
**Answer:**  
- Define abstract product interfaces.
- Implement concrete product classes.
- Define an abstract factory interface with creation methods for each product.
- Implement concrete factories for each product family.

---

### 4. How do you ensure products from the same family are used together?
**Answer:**  
By using a single factory instance to create all products, you guarantee compatibility.

---

### 5. How do you demonstrate the Abstract Factory pattern in code?
**Answer:**  
- Prompt the user for a product family (e.g., simple or espresso).
- Instantiate the corresponding factory.
- Use the factory to create related products.
- Use the products via their abstract interfaces.

**Example:**
```cpp
int choice;
std::cout << "Enter coffee type (simple:1 / espresso:2): ";
if (!(std::cin >> choice)) {
    std::cout << "Invalid input!" << std::endl;
    return 1;
}

std::unique_ptr<CoffeeFactory> factory;
if (choice == 1) {
    factory = std::make_unique<SimpleCoffeeFactory>();
} else if (choice == 2) {
    factory = std::make_unique<EspressoFactory>();
} else {
    std::cout << "Invalid choice!" << std::endl;
    return 1;
}

auto coffeeMachine = factory->createCoffeeMachine();
auto coffee = factory->createCoffee();

coffeeMachine->brew();
coffee->prepare();
```

---

## 🟦 Example Usage

```cpp
// Prompt user for coffee type
int choice;
std::cout << "Enter coffee type (simple:1 / espresso:2): ";
if (!(std::cin >> choice)) {
    std::cout << "Invalid input!" << std::endl;
    return 1;
}

std::unique_ptr<CoffeeFactory> factory;
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
```

---