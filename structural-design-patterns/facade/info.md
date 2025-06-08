# Facade Pattern in C++

---

## 🟦 What is the Facade Pattern?

The **Facade Pattern** is a structural design pattern that provides a simplified, unified interface to a complex subsystem.  
It hides the complexities of the subsystem and exposes only what is necessary for the client.

---

## 🟦 Why Use the Facade Pattern?

- To make a complex system easier to use.
- To reduce dependencies and coupling between client code and subsystem classes.
- To provide a single entry point to a set of related classes.

---

## 🟦 Advantages of Facade

- **Simplicity:** Provides a simple interface to a complex subsystem.
- **Decoupling:** Reduces dependencies between clients and subsystems.
- **Flexibility:** Subsystems can be changed without affecting client code.

---

## 🟦 Disadvantages of Facade

- **Limited Functionality:** May not expose all features of the subsystem.
- **Overuse:** Too many facades can lead to unnecessary abstraction.

---

## ✅ Key Features of the Facade Pattern

- **Subsystems:**  
  The complex set of classes and their interactions (e.g., `Projector`, `SoundSystem`, `DVDPlayer`, `Screen`).

- **Facade:**  
  A class that provides a simplified interface to the subsystems (e.g., `HomeTheaterFacade`).

- **Client:**  
  Uses the facade instead of interacting with the subsystems directly.

---

## 🛠️ Scope for Further Modifications

- **Add More Subsystems:**  
  Extend the facade to control more devices (e.g., lighting, streaming).

- **Parameterization:**  
  Allow the client to customize subsystem behavior through the facade.

- **Multiple Facades:**  
  Provide different facades for different use cases.

---

## ⚠️ What NOT to Do

- Do **not** let the client interact directly with subsystem classes if you want to keep things simple.
- Do **not** expose unnecessary subsystem details through the facade.

---

## 🟦 Interview Questions and Answers

### 1. What is the Facade pattern?
**Answer:**  
A structural pattern that provides a unified interface to a set of interfaces in a subsystem, making the subsystem easier to use.

**Example:**  
```cpp
class HomeTheaterFacade {
    std::unique_ptr<Projector> projector;
    std::unique_ptr<SoundSystem> soundSystem;
    std::unique_ptr<DVDPlayer> dvdPlayer;
    std::unique_ptr<Screen> screen;
public:
    void watchMovie(const std::string& movie) {
        screen->lower();
        projector->turnOn();
        soundSystem->turnOn();
        soundSystem->setVolume(5);
        dvdPlayer->turnOn();
        dvdPlayer->playMovie(movie);
    }
    void endMovie() {
        dvdPlayer->turnOff();
        soundSystem->turnOff();
        projector->turnOff();
        screen->raise();
    }
};
```

---

### 2. When would you use the Facade pattern?
**Answer:**  
When you want to provide a simple interface to a complex subsystem or set of classes.

---

### 3. How do you implement the Facade pattern in C++?
**Answer:**  
- Identify the subsystem classes.
- Create a facade class that wraps and coordinates the subsystem classes.
- The client interacts only with the facade.

---

### 4. How do you use the Facade pattern in client code?
**Answer:**  
- Create an instance of the facade.
- Call high-level methods on the facade instead of dealing with subsystems directly.

**Example:**
```cpp
HomeTheaterFacade homeTheater;
homeTheater.watchMovie("Inception");
homeTheater.endMovie();
```

---

## 🟦 Example Usage

```cpp
// Client uses only the Facade to control the home theater
HomeTheaterFacade homeTheater;

homeTheater.watchMovie("Inception");
std::cout << "Enjoy the movie!" << std::endl;

homeTheater.endMovie();
std::cout << "Movie ended. Home theater is now off." << std::endl;
```

---