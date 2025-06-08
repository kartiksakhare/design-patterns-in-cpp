# Proxy Pattern in C++

---

## 🟦 What is the Proxy Pattern?

The **Proxy Pattern** is a structural design pattern that provides a surrogate or placeholder for another object to control access to it.  
It is used to add additional functionality (such as access control, logging, or lazy initialization) without changing the original object's code.

---

## 🟦 Why Use the Proxy Pattern?

- To control access to sensitive or resource-intensive objects.
- To add security, logging, or caching transparently.
- To defer the creation and initialization of expensive objects.

---

## 🟦 Advantages of Proxy

- **Access Control:** Restricts or manages access to the real object.
- **Separation of Concerns:** Adds extra functionality without modifying the real subject.
- **Lazy Initialization:** Can delay object creation until needed.

---

## 🟦 Disadvantages of Proxy

- **Complexity:** Adds extra classes and indirection.
- **Performance:** May introduce slight overhead due to additional method calls.

---

## ✅ Key Features of the Proxy Pattern

- **Subject:**  
  The common interface for RealSubject and Proxy (e.g., `BankAccount`).

- **RealSubject:**  
  The actual object that does the real work (e.g., `RealBankAccount`).

- **Proxy:**  
  Controls access to the RealSubject and may add extra logic (e.g., `BankAccountProxy`).

- **Client:**  
  Uses the Proxy as if it were the RealSubject.

---

## 🛠️ Scope for Further Modifications

- **Add More Proxies:**  
  Implement different proxies for logging, caching, or remote access.

- **Thread Safety:**  
  Add synchronization if used in a multithreaded environment.

- **Return Types:**  
  Use `std::optional` or exceptions for better error handling.

---

## ⚠️ What NOT to Do

- Do **not** tightly couple client code to the RealSubject.
- Do **not** bypass the proxy if you want to enforce access control.

---

## 🟦 Interview Questions and Answers

### 1. What is the Proxy pattern?
**Answer:**  
A structural pattern that provides a surrogate or placeholder for another object to control access to it.

**Example:**  
```cpp
class BankAccount {
public:
    virtual void deposit(double, const std::string&) = 0;
    virtual void withdraw(double, const std::string&) = 0;
    virtual double getBalance(const std::string&) const = 0;
    virtual ~BankAccount() = default;
};
class RealBankAccount : public BankAccount { /* ... */ };
class BankAccountProxy : public BankAccount { /* ... */ };
```

---

### 2. When would you use the Proxy pattern?
**Answer:**  
When you need to control access, add security, logging, or lazy initialization to an object.

---

### 3. How do you implement the Proxy pattern in C++?
**Answer:**  
- Define a subject interface.
- Implement the real subject.
- Implement the proxy, which holds a reference to the real subject and adds extra logic.

---

### 4. How do you use the Proxy pattern in client code?
**Answer:**  
- Create a proxy object.
- Use it as if it were the real subject; the proxy manages access and delegates as needed.

**Example:**
```cpp
BankAccountProxy accountProxy(100.0, "1234");
accountProxy.deposit(50.0, "1234");
std::cout << accountProxy.getBalance("1234") << std::endl;
```

---

## 🟦 Example Usage

```cpp
std::string pin = "1234";
BankAccountProxy accountProxy(100.0, pin);

// Successful deposit
accountProxy.deposit(50.0, pin);
std::cout << "Current Balance: " << accountProxy.getBalance(pin) << std::endl;

// Successful withdrawal
accountProxy.withdraw(30.0, pin);
std::cout << "Current Balance: " << accountProxy.getBalance(pin) << std::endl;

// Failed withdrawal (insufficient balance)
accountProxy.withdraw(150.0, pin);

// Attempting to access balance with wrong pin
std::cout << "Attempting to get balance with wrong pin:" << std::endl;
std::string wrongPin = "wrong_pin";
accountProxy.deposit(20.0, wrongPin); // Should fail due to authentication
std::cout << "Balance with wrong pin: " << accountProxy.getBalance(wrongPin) << std::endl;
```

---