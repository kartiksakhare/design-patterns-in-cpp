# Bridge Pattern in C++

---

## 🟦 What is the Bridge Pattern?

The **Bridge Pattern** is a structural design pattern that decouples an abstraction from its implementation so that the two can vary independently.  
It allows you to develop abstractions and implementations in separate class hierarchies and combine them flexibly.

---

## 🟦 Why Use the Bridge Pattern?

- To avoid a combinatorial explosion of classes when you have multiple dimensions of variation (e.g., different remotes and different devices).
- To allow abstractions and implementations to evolve independently.
- To increase flexibility and scalability in your codebase.

---

## 🟦 Advantages of Bridge

- **Decoupling:** Abstraction and implementation can be developed and extended independently.
- **Flexibility:** Easily mix and match abstractions and implementations.
- **Scalability:** Adding new abstractions or implementations does not require changes to existing code.

---

## 🟦 Disadvantages of Bridge

- **Complexity:** Introduces more classes and indirection.
- **Initial Setup:** Requires careful design to identify abstraction and implementation hierarchies.

---

## ✅ Key Features of the Bridge Pattern

- **Abstraction:**  
  Defines the interface for the "control" part of the two-class system (e.g., `RemoteControl`).

- **Refined Abstraction:**  
  Extends the abstraction interface (e.g., `BasicRemote`, `AdvancedRemote`).

- **Implementor:**  
  Defines the interface for the "implementation" part (e.g., `Device`).

- **Concrete Implementor:**  
  Implements the implementor interface (e.g., `TV`, `Radio`).

- **Bridge:**  
  The abstraction contains a reference (usually a pointer or smart pointer) to the implementor.

---

## 🛠️ Scope for Further Modifications

- **Add More Devices or Remotes:**  
  Easily extend by adding new device or remote types.

- **Add More Operations:**  
  Add more methods to the abstraction or implementor interfaces.

- **Parameterization:**  
  Pass parameters to remotes or devices for more customized behavior.

---

## ⚠️ What NOT to Do

- Do **not** tightly couple abstraction and implementation.
- Do **not** duplicate code for each combination of abstraction and implementation.
- Do **not** break the separation between abstraction and implementation.

---

## 🟦 Interview Questions and Answers

### 1. What is the Bridge pattern?
**Answer:**  
A structural pattern that decouples an abstraction from its implementation, allowing both to vary independently.

**Example:**  
```cpp
class Device {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~Device() = default;
};
class RemoteControl {
protected:
    std::shared_ptr<Device> device;
public:
    explicit RemoteControl(std::shared_ptr<Device> dev) : device(std::move(dev)) {}
    virtual void pressPowerButton() = 0;
    virtual ~RemoteControl() = default;
};
```

---

### 2. When would you use the Bridge pattern?
**Answer:**  
When you have multiple dimensions of variation (e.g., different remotes and devices) and want to avoid a class explosion.

---

### 3. How do you implement the Bridge pattern in C++?
**Answer:**  
- Define the abstraction and implementor interfaces.
- Implement concrete classes for both hierarchies.
- The abstraction holds a reference to the implementor.
- Use composition to combine them at runtime.

---

### 4. How do you demonstrate the Bridge pattern in code?
**Answer:**  
- Create devices (e.g., TV, Radio).
- Create remotes (e.g., BasicRemote, AdvancedRemote) that control devices via the implementor interface.
- Show that any remote can control any device.

**Example:**
```cpp
auto tv = std::make_shared<TV>();
auto radio = std::make_shared<Radio>();

std::shared_ptr<RemoteControl> basicRemote = std::make_shared<BasicRemote>(tv);
std::shared_ptr<RemoteControl> advancedRemote = std::make_shared<AdvancedRemote>(radio);

basicRemote->pressPowerButton();
advancedRemote->pressPowerButton();

if (auto adv = dynamic_cast<AdvancedRemote*>(advancedRemote.get())) {
    adv->pressPowerOffButton();
}
```

---

## 🟦 Example Usage

```cpp
// Create a TV and a Radio
std::shared_ptr<Device> tv = std::make_shared<TV>();
std::shared_ptr<Device> radio = std::make_shared<Radio>();

// Bridge: Remotes can control any Device
std::shared_ptr<RemoteControl> basicRemoteForTV = std::make_shared<BasicRemote>(tv);
std::shared_ptr<RemoteControl> advancedRemoteForRadio = std::make_shared<AdvancedRemote>(radio);

std::cout << "Using Basic Remote for TV:" << std::endl;
basicRemoteForTV->pressPowerButton();

std::cout << "Using Advanced Remote for Radio:" << std::endl;
advancedRemoteForRadio->pressPowerButton();

// Safe downcast to access AdvancedRemote-specific functionality
if (auto advancedRemote = dynamic_cast<AdvancedRemote*>(advancedRemoteForRadio.get())) {
    advancedRemote->pressPowerOffButton();
}

// Demonstrate flexibility: AdvancedRemote can also control TV
std::shared_ptr<RemoteControl> advancedRemoteForTV = std::make_shared<AdvancedRemote>(tv);
std::cout << "Using Advanced Remote for TV:" << std::endl;
advancedRemoteForTV->pressPowerButton();
if (auto advancedRemote = dynamic_cast<AdvancedRemote*>(advancedRemoteForTV.get())) {
    advancedRemote->pressPowerOffButton();
}
```

---