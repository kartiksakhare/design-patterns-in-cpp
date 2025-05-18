# Prototype Pattern in C++

---

## 🟦 What is the Prototype Pattern?

The **Prototype Pattern** is a creational design pattern that enables object creation by copying (cloning) an existing object, known as the prototype.  
It allows you to create new objects by duplicating a prototype instance, rather than instantiating new objects directly.

---

## 🟦 Why Use the Prototype Pattern?

- To avoid the cost of creating objects from scratch, especially when object creation is expensive.
- To create objects with complex state or configuration.
- To decouple code from specific classes by using a common interface for cloning.
- To allow dynamic addition of new object types at runtime.

---

## 🟦 Advantages of Prototype

- **Cloning:** Easily create new objects by copying existing ones.
- **Decoupling:** Client code does not need to know the concrete class of the object being created.
- **Runtime Flexibility:** New prototypes can be registered and cloned at runtime.
- **Stateful Objects:** Cloned objects can have their own state, independent of the prototype.

---

## 🟦 Disadvantages of Prototype

- **Copy Complexity:** Deep copying can be tricky if objects have complex or pointer-based members.
- **Initialization:** Prototypes must be initialized before cloning.
- **Memory Management:** Manual memory management is required if using raw pointers (consider smart pointers for modern C++).

---

## ✅ Key Features of the Prototype Pattern

- **Prototype Interface:**  
  An abstract base class (e.g., `CoffeeMachine`) declares a `clone()` method, as well as `brew()`, `display()`, and `validate()`.

- **Concrete Prototypes:**  
  Derived classes (e.g., `SimpleCoffeeMachine`, `EspressoMachine`, `AdvancedCoffeeMachine`) implement the `clone()` and `brew()` methods and inherit state management and validation.

- **Prototype Manager:**  
  A manager class (e.g., `CoffeeMachineManager`) holds prototype instances and provides a factory method to clone them.  
  It also provides a cleanup method to delete prototypes and prevent memory leaks.

- **Stateful Cloning and Validation:**  
  Cloned objects can be customized after cloning (e.g., cup size, milk, sugar) using setters.  
  The `validate()` method ensures the machine's configuration is valid before brewing.

- **Memory Management:**  
  Proper cleanup of dynamically allocated prototypes and clones is essential.  
  The base class has a virtual destructor.

---

## 🛠️ Scope for Further Modifications

- **Dynamic Prototype Registration:**  
  Allow registering new prototypes at runtime, not just at compile time.

- **Smart Pointers:**  
  Use `std::unique_ptr` or `std::shared_ptr` for safer memory management.

- **Deep Copying:**  
  Ensure deep copy in `clone()` if your objects contain pointers or dynamic resources.

- **Prototype Metadata:**  
  Store and display additional information about each prototype.

- **Exception Safety:**  
  Add error handling for failed clones or invalid types.

---

## ⚠️ What NOT to Do

- Do **not** forget to implement a virtual destructor in the prototype base class.
- Do **not** return shallow copies if your objects manage dynamic memory.
- Do **not** leak memory—always clean up prototypes and clones.
- Do **not** expose internal state that should remain encapsulated.
- Do **not** skip validation before using a customized clone.

---

## 🟦 Interview Questions and Answers

### 1. What is the Prototype pattern?
**Answer:**  
A creational pattern where new objects are created by copying (cloning) an existing prototype instance.

**Example:**  
```cpp
class CoffeeMachine {
public:
    virtual CoffeeMachine* clone() const = 0;
    virtual ~CoffeeMachine() {}
};
class SimpleCoffeeMachine : public CoffeeMachine {
public:
    CoffeeMachine* clone() const override {
        return new SimpleCoffeeMachine(*this);
    }
};
```

---

### 2. When would you use the Prototype pattern?
**Answer:**  
When object creation is costly or complex, or when you want to create objects at runtime without knowing their exact types.

---

### 3. How do you implement the Prototype pattern in C++?
**Answer:**  
- Define an abstract base class with a pure virtual `clone()` method.
- Implement `clone()` in each concrete subclass, returning a copy of itself.
- Use a manager or registry to store and clone prototypes as needed.

---

### 4. How do you handle state in cloned objects?
**Answer:**  
After cloning, you can customize the state of the new object using setter methods or by modifying its properties.  
The `validate()` method ensures the state is valid before use.

---

### 5. How do you manage memory in a Prototype implementation?
**Answer:**  
- Ensure the base class has a virtual destructor.
- Delete all dynamically allocated prototypes and clones.
- Prefer smart pointers for automatic memory management.

---

### 6. What is the difference between Prototype and Factory patterns?
**Answer:**  
- **Prototype:** Creates objects by cloning existing instances.
- **Factory:** Creates objects by instantiating classes, often using a factory method.

---

### 7. How do you ensure deep copying in the Prototype pattern?
**Answer:**  
Implement the copy constructor and `clone()` method to perform deep copies of all dynamic members.

---

### 8. Can you register new prototypes at runtime?
**Answer:**  
Yes, by adding a registration method to the manager, you can add new prototype instances dynamically.

---

### 9. How do you clean up prototypes and clones?
**Answer:**  
Provide a cleanup method in the manager to delete all prototypes, and ensure client code deletes any clones it creates.

---

### 10. How do you demonstrate the Prototype pattern in code?
**Answer:**  
- Create and register prototype objects.
- Clone prototypes to create new objects.
- Customize the state of clones as needed.
- Validate before using the clone.
- Clean up all dynamically allocated objects.

**Example:**
```cpp
CoffeeMachine* simple = CoffeeMachineManager::createMachine(0);
simple->setCupSize(2);
simple->setMilk(true);
simple->setSugar(1);

if (simple->validate()) {
    simple->brew();
}

CoffeeMachine* clone = simple->clone();
clone->setCupSize(1);
clone->setMilk(false);
clone->setSugar(0);

if (clone->validate()) {
    clone->brew();
}

delete simple;
delete clone;
CoffeeMachineManager::cleanupPrototypes();
```

**Validation Example:**  
You can also validate and compare the state of the original and the clone:
```cpp
CoffeeMachine* original = CoffeeMachineManager::createMachine(0);
original->setCupSize(2);
CoffeeMachine* clone = original->clone();
clone->setCupSize(3);

if (original->validate()) original->brew();
if (clone->validate()) clone->brew();

delete original;
delete clone;
CoffeeMachineManager::cleanupPrototypes();
```
---