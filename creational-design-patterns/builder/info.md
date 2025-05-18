# Builder Pattern in C++

---

## 🟦 What is the Builder Pattern?

The **Builder Pattern** is a creational design pattern that lets you construct complex objects step by step.  
It separates the construction of an object from its representation, allowing the same construction process to create different representations.

---

## 🟦 Why Use a Builder?

- To construct objects with many optional parameters or configurations.
- To avoid telescoping constructors (constructors with many parameters).
- To make the construction process readable and flexible.
- To encapsulate the construction logic outside the main class.

---

## 🟦 Advantages of Builder

- **Readable Code:** Construction steps are clear and chainable.
- **Separation of Concerns:** Construction logic is separated from the object itself.
- **Immutability:** The final product can be made immutable.
- **Flexible Construction:** Easily create different representations or configurations.
- **Validation:** Ensures only valid objects are created by checking configuration before building.
- **Reusability:** Builder can be reset and reused for multiple products.

---

## 🟦 Disadvantages of Builder

- **More Classes:** Requires additional builder classes.
- **Verbosity:** Can be overkill for simple objects.
- **Complexity:** Slightly increases code complexity for small objects.

---

## ✅ Key Features of the Builder Pattern

- **Product Class:**  
  The complex object being built (e.g., `Coffee`).

- **Builder Class:**  
  Provides methods to configure and assemble the product step by step (e.g., `CoffeeBuilder`).

- **Fluent Interface:**  
  Builder methods return `*this` to allow chaining.

- **Director (Optional):**  
  Encapsulates standard construction sequences (not always needed).

- **Separation:**  
  The builder is separate from the product, so the product class does not need to know about the construction process.

- **Final Build Step:**  
  The builder provides a method or conversion to obtain the finished product.

- **Validation:**  
  The builder includes a `validate()` method, called in `build()`, to ensure the product is in a valid state before creation (e.g., non-empty name, non-negative cost).

- **Reset/Reuse:**  
  The builder can be reset to build multiple products without creating a new builder object.

---

## 🛠️ Scope for Further Modifications

- **Director Class:**  
  Add a director to encapsulate common construction sequences.

- **More Validation:**  
  Add additional validation logic in the builder before returning the product (e.g., required ingredients, size limits).

- **Immutability:**  
  Make the product immutable after construction.

- **Multiple Products:**  
  Use the same builder interface for different products.

- **Thread Safety:**  
  Make the builder thread-safe if used in concurrent contexts.

- **Additional Customizations:**  
  Add more properties (e.g., size, flavor, strength) and corresponding builder methods.

---

## ⚠️ What NOT to Do

- Do **not** expose incomplete product objects before the build is finished.
- Do **not** mix product logic with builder logic.
- Do **not** make the builder responsible for too many unrelated products.
- Do **not** skip validation in the builder if the product requires it.

---

## 🟦 Interview Questions and Answers

### 1. What is the Builder pattern?
**Answer:**  
A builder separates the construction of a complex object from its representation, allowing the same construction process to create different representations.

**Example:**  
```cpp
class CoffeeBuilder {
public:
    CoffeeBuilder& addMilk();
    CoffeeBuilder& addSugar();
    Coffee build();
};
```

---

### 2. When would you use the Builder pattern?
**Answer:**  
When an object requires many configuration steps or has many optional parameters, or when you want to avoid long constructors.

---

### 3. How do you implement a builder in C++?
**Answer:**  
- Create a builder class with methods for each configuration step.
- Each method returns a reference to the builder (`*this`) for chaining.
- Provide a method or conversion to get the final product.
- Add a `validate()` method to check the configuration before building.

**Example:**  
```cpp
class CoffeeBuilder {
    Coffee coffee;
public:
    CoffeeBuilder& addMilk() { coffee.hasMilk = true; return *this; }
    Coffee build() {
        validate();
        return coffee;
    }
    void validate() const {
        if (coffee.cost < 0.0) throw std::runtime_error("Cost cannot be negative.");
    }
};
```

---

### 4. What are the pros and cons of using a builder?
**Answer:**  
**Pros:** Readable, flexible, avoids telescoping constructors, separates construction logic, allows validation.  
**Cons:** More classes, more code for simple objects.

---

### 5. How would you test code that uses a builder?
**Answer:**  
- Test each builder method individually.
- Test the final product after a sequence of builder calls.
- Test edge cases (e.g., missing required steps, invalid configurations).

---

### 6. Can you make the builder reusable?
**Answer:**  
Yes, by adding a `reset()` method to clear the builder’s state, allowing it to build multiple products.

---

### 7. What is the difference between Builder and Factory patterns?
**Answer:**  
- **Builder:** Step-by-step construction, often for complex objects with many options.
- **Factory:** Instantiates objects, usually in one step, often for families of related objects.

---

### 8. How do you handle required and optional parameters in a builder?
**Answer:**  
- Required parameters can be passed to the builder’s constructor.
- Optional parameters are set via builder methods.

---

### 9. How do you ensure the product is valid before returning it?
**Answer:**  
Add validation logic in the builder’s `build()` method or before returning the product, using a `validate()` function.

---

### 10. Can you use the builder pattern with immutable objects?
**Answer:**  
Yes. The builder can set all properties, and the product can be made immutable (e.g., by making all fields `const` and only settable by the builder).

**Example:**  
```cpp
class Coffee {
    const bool hasMilk;
    friend class CoffeeBuilder;
    Coffee(bool milk) : hasMilk(milk) {}
};
class CoffeeBuilder {
    bool milk = false;
public:
    CoffeeBuilder& addMilk() { milk = true; return *this; }
    Coffee build() { return Coffee(milk); }
};
```
---