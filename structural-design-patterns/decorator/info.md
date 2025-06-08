# Decorator Pattern in C++

---

## 🟦 What is the Decorator Pattern?

The **Decorator Pattern** is a structural design pattern that allows you to dynamically add new behavior or responsibilities to objects without modifying their code.  
It achieves this by wrapping the original object with decorator objects that add the desired features.

---

## 🟦 Why Use the Decorator Pattern?

- To add features to objects at runtime, not compile time.
- To avoid an explosion of subclasses for every feature combination.
- To follow the Open/Closed Principle (open for extension, closed for modification).
- To keep code flexible and extensible.

---

## 🟦 Advantages of Decorator

- **Flexibility:** Add or remove features at runtime.
- **Composability:** Combine multiple decorators in any order.
- **Single Responsibility:** Each decorator adds a single feature or responsibility.
- **No subclass explosion:** Avoids creating a subclass for every feature combination.

---

## 🟦 Disadvantages of Decorator

- **Complexity:** Many small classes can make code harder to understand.
- **Debugging:** Tracing through many layers of decorators can be tricky.

---

## ✅ Key Features of the Decorator Pattern

- **Component:**  
  The interface or abstract class for objects that can have responsibilities added (e.g., `Coffee`).

- **Concrete Component:**  
  The original object to which new features are added (e.g., `SimpleCoffee`).

- **Decorator:**  
  An abstract class that implements the component interface and has a reference to a component.

- **Concrete Decorators:**  
  Add new behavior or state (e.g., `MilkDecorator`, `SugarDecorator`, `WhippedCreamDecorator`).

---

## 🛠️ Scope for Further Modifications

- **Add More Decorators:**  
  Easily extend by adding new decorators for more features (e.g., `CinnamonDecorator`).

- **Decorator Order:**  
  The order in which decorators are applied affects the final result.

- **Parameterization:**  
  Decorators can accept parameters for more customized behavior.

---

## ⚠️ What NOT to Do

- Do **not** modify the original component class to add new features.
- Do **not** tightly couple decorators to specific concrete components.
- Do **not** use the pattern if only a few combinations are needed (can be overkill).

---

## 🟦 Interview Questions and Answers

### 1. What is the Decorator pattern?
**Answer:**  
A structural pattern that lets you dynamically add responsibilities to objects by wrapping them in decorator classes.

**Example:**  
```cpp
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() = default;
};
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override { return "Simple Coffee"; }
    double cost() const override { return 2.0; }
};
class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> coffee;
public:
    explicit CoffeeDecorator(std::shared_ptr<Coffee> c) : coffee(std::move(c)) {}
};
class MilkDecorator : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;
    std::string getDescription() const override { return coffee->getDescription() + ", Milk"; }
    double cost() const override { return coffee->cost() + 0.5; }
};
```

---

### 2. When would you use the Decorator pattern?
**Answer:**  
When you want to add features to objects dynamically and transparently, without affecting other objects of the same class.

---

### 3. How do you implement the Decorator pattern in C++?
**Answer:**  
- Define a component interface.
- Implement concrete components.
- Create an abstract decorator that implements the component interface and holds a reference to a component.
- Implement concrete decorators that add new behavior.

---

### 4. How do you use the Decorator pattern in client code?
**Answer:**  
- Create a base component.
- Wrap it with one or more decorators.
- Use the decorated object as if it were the base component.

**Example:**
```cpp
std::shared_ptr<Coffee> myCoffee = std::make_shared<SimpleCoffee>();
myCoffee = std::make_shared<MilkDecorator>(myCoffee);
myCoffee = std::make_shared<SugarDecorator>(myCoffee);
std::cout << myCoffee->getDescription() << " $" << myCoffee->cost() << std::endl;
```

---

## 🟦 Example Usage

```cpp
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
```

---