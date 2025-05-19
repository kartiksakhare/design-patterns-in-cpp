# Adapter Pattern in C++

---

## 🟦 What is the Adapter Pattern?

The **Adapter Pattern** is a structural design pattern that allows objects with incompatible interfaces to work together.  
It acts as a bridge between two incompatible interfaces by wrapping one of the objects and exposing the expected interface.

---

## 🟦 Why Use the Adapter Pattern?

- To integrate classes with incompatible interfaces.
- To reuse existing code without modifying it.
- To enable classes to work together that otherwise couldn’t due to interface differences.
- To follow the Open/Closed Principle (open for extension, closed for modification).

---

## 🟦 Advantages of Adapter

- **Reusability:** Allows use of existing classes even if their interfaces don’t match.
- **Flexibility:** Can adapt multiple incompatible interfaces to a common interface.
- **Decoupling:** Client code is decoupled from the adaptee’s implementation.

---

## 🟦 Disadvantages of Adapter

- **Extra Layer:** Adds complexity and an extra layer of indirection.
- **Overuse:** Overusing adapters can make code harder to understand and maintain.

---

## ✅ Key Features of the Adapter Pattern

- **Target Interface:**  
  The interface expected by the client (e.g., `AmericanSocket`).

- **Adaptee:**  
  The existing class with an incompatible interface (e.g., `EuropeanPlug`).

- **Adapter:**  
  Implements the target interface and wraps the adaptee, translating calls as needed (e.g., `PlugAdapter`).

- **Client:**  
  Uses the target interface and is unaware of the adaptee’s details.

---

## 🛠️ Scope for Further Modifications

- **Support Multiple Adaptees:**  
  Create adapters for other plug/socket types.

- **Two-way Adapter:**  
  Allow adaptation in both directions if needed.

- **Composition vs. Inheritance:**  
  Use composition (preferred) or inheritance based on requirements.

- **Error Handling:**  
  Add checks for null adaptees or invalid states.

---

## ⚠️ What NOT to Do

- Do **not** modify the adaptee’s code directly.
- Do **not** tightly couple the adapter to specific client code.
- Do **not** use the adapter if direct compatibility can be achieved by refactoring.

---

## 🟦 Interview Questions and Answers

### 1. What is the Adapter pattern?
**Answer:**  
A structural pattern that allows objects with incompatible interfaces to work together by providing a wrapper (adapter) with the expected interface.

**Example:**  
```cpp
class AmericanSocket {
public:
    virtual void providePower() const = 0;
    virtual ~AmericanSocket() = default;
};
class EuropeanPlug {
public:
    void connect() const {
        std::cout << "European plug connected to European socket." << std::endl;
    }
};
class PlugAdapter : public AmericanSocket {
    std::shared_ptr<EuropeanPlug> plug;
public:
    explicit PlugAdapter(std::shared_ptr<EuropeanPlug> p) : plug(std::move(p)) {}
    void providePower() const override {
        if (!plug) {
            std::cout << "No plug connected to adapter!" << std::endl;
            return;
        }
        std::cout << "Adapter converting plug..." << std::endl;
        plug->connect();
        std::cout << "Power provided through adapter." << std::endl;
    }
};
```

---

### 2. When would you use the Adapter pattern?
**Answer:**  
When you want to use an existing class, but its interface does not match what your code expects.

---

### 3. How do you implement the Adapter pattern in C++?
**Answer:**  
- Define the target interface.
- Implement the adapter class that inherits from the target interface and wraps the adaptee.
- In the adapter, translate calls from the target interface to the adaptee’s interface.

---

### 4. How do you demonstrate that direct usage won’t work?
**Answer:**  
By attempting to use the adaptee where the target interface is expected, which results in a compile-time error.

**Example:**
```cpp
// This will not compile:
// std::shared_ptr<AmericanSocket> direct = std::make_shared<EuropeanPlug>();
// direct->providePower(); // ERROR: EuropeanPlug does not implement AmericanSocket
```

---

### 5. How do you use the adapter in client code?
**Answer:**  
- Create an instance of the adaptee.
- Wrap it in an adapter.
- Use the adapter as if it were an instance of the target interface.

**Example:**
```cpp
auto europeanPlug = std::make_shared<EuropeanPlug>();
std::shared_ptr<AmericanSocket> adapter = std::make_shared<PlugAdapter>(europeanPlug);
adapter->providePower();
```

---

### 6. How do you handle error cases in the adapter?
**Answer:**  
Check for null adaptee pointers and handle them gracefully in the adapter’s methods.

---

## 🟦 Example Usage

```cpp
// Direct usage (not possible): EuropeanPlug can't be used as AmericanSocket
// std::shared_ptr<AmericanSocket> direct = std::make_shared<EuropeanPlug>();
// direct->providePower(); // ERROR: EuropeanPlug does not implement AmericanSocket

// Using Adapter
auto europeanPlug = std::make_shared<EuropeanPlug>();
std::shared_ptr<AmericanSocket> adapter = std::make_shared<PlugAdapter>(europeanPlug);

std::cout << "Using European plug in an American socket." << std::endl;
adapter->providePower();

// Demonstrate error handling: Adapter with no plug
std::shared_ptr<AmericanSocket> emptyAdapter = std::make_shared<PlugAdapter>(nullptr);
std::cout << "\nTrying to use adapter with no plug:" << std::endl;
emptyAdapter->providePower();
```

---