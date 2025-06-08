# Flyweight Pattern in C++

---

## 🟦 What is the Flyweight Pattern?

The **Flyweight Pattern** is a structural design pattern that allows you to efficiently support a large number of fine-grained objects by sharing common (intrinsic) state and storing only unique (extrinsic) state externally.  
It is especially useful when many objects share similar data, reducing memory usage.

---

## 🟦 Why Use the Flyweight Pattern?

- To minimize memory usage when you have many similar objects.
- To share as much data as possible between objects.
- To separate shared (intrinsic) state from unique (extrinsic) state.

---

## 🟦 Advantages of Flyweight

- **Memory Efficiency:** Greatly reduces memory footprint for large numbers of similar objects.
- **Performance:** Can improve performance by reducing object creation overhead.

---

## 🟦 Disadvantages of Flyweight

- **Complexity:** Adds complexity to code due to separation of intrinsic and extrinsic state.
- **Thread Safety:** Shared objects may require synchronization in multithreaded environments.

---

## ✅ Key Features of the Flyweight Pattern

- **Flyweight:**  
  The shared object that contains intrinsic (shared) state (e.g., `CarFlyweight`).

- **Flyweight Factory:**  
  Creates and manages flyweight objects, ensuring sharing (e.g., `CarFlyweightFactory`).

- **Client:**  
  Uses flyweights and supplies extrinsic (unique) state when needed.

---

## 🛠️ Scope for Further Modifications

- **Add More Intrinsic State:**  
  Store more shared data in the flyweight if needed.

- **Thread Safety:**  
  Make the factory thread-safe if used in concurrent environments.

- **Pooling:**  
  Implement object pooling for even more efficient reuse.

---

## ⚠️ What NOT to Do

- Do **not** store extrinsic (unique) state inside the flyweight.
- Do **not** create new flyweights for every request—reuse existing ones when possible.

---

## 🟦 Interview Questions and Answers

### 1. What is the Flyweight pattern?
**Answer:**  
A structural pattern that minimizes memory usage by sharing as much data as possible with similar objects.

**Example:**  
```cpp
class CarFlyweight {
    // Intrinsic state: model, brand, engineType
};
class CarFlyweightFactory {
    std::unordered_map<std::string, std::shared_ptr<CarFlyweight>> carMap;
    // ...
};
```

---

### 2. When would you use the Flyweight pattern?
**Answer:**  
When you need to efficiently manage a large number of similar objects that share common data.

---

### 3. How do you implement the Flyweight pattern in C++?
**Answer:**  
- Define a flyweight class for shared state.
- Implement a factory to manage and share flyweight instances.
- Store unique (extrinsic) state outside the flyweight.

---

### 4. How do you use the Flyweight pattern in client code?
**Answer:**  
- Request a flyweight from the factory.
- Supply extrinsic state when using the flyweight.

**Example:**
```cpp
auto car = factory.getCarFlyweight("Model S", "Tesla", "Electric");
car->displayCarDetails("TS1234", "Alice");
```

---

## 🟦 Example Usage

```cpp
CarFlyweightFactory factory;

// Request a flyweight for a Tesla Model S (creates new)
auto car1 = factory.getCarFlyweight("Model S", "Tesla", "Electric");
car1->displayCarDetails("TS1234", "Alice");

// Request the same flyweight again (reuses existing)
auto car2 = factory.getCarFlyweight("Model S", "Tesla", "Electric");
car2->displayCarDetails("TS5678", "Bob");

// Request a flyweight for a Ford Mustang (creates new)
auto car3 = factory.getCarFlyweight("Mustang", "Ford", "Gasoline");
car3->displayCarDetails("FD1234", "Charlie");
```

---