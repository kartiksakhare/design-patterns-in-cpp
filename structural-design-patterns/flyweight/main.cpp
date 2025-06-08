/*
 * Flyweight Pattern Example: Efficiently sharing car data using flyweights.
 *
 * - Flyweight: CarFlyweight (intrinsic state: model, brand, engineType)
 * - Flyweight Factory: CarFlyweightFactory (creates and manages shared flyweight objects)
 * - Client: Requests flyweights and supplies extrinsic state (registration number, owner)
 *
 * This demonstrates how the Flyweight pattern minimizes memory usage by sharing as much data as possible
 * with similar objects. Only the unique, extrinsic data is stored separately for each usage.
 */

#include <iostream>
#include <unordered_map>
#include <memory>

// Flyweight: Represents shared car data (intrinsic state)
class CarFlyweight {
private:
    std::string model;
    std::string brand;
    std::string engineType;

public:
    CarFlyweight(const std::string& model, const std::string& brand, const std::string& engineType)
        : model(model), brand(brand), engineType(engineType) {}

    // Displays car details, combining intrinsic (shared) and extrinsic (unique) state
    void displayCarDetails(const std::string& registrationNumber, const std::string& owner) const {
        std::cout << "Car Details:\n"
                  << "Model: " << model << "\n"
                  << "Brand: " << brand << "\n"
                  << "Engine Type: " << engineType << "\n"
                  << "Registration Number: " << registrationNumber << "\n"
                  << "Owner: " << owner << "\n";
    }
};

// Flyweight Factory: Creates and manages flyweight objects
class CarFlyweightFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<CarFlyweight>> carMap;

    // Generates a unique key for each combination of intrinsic state
    std::string generateKey(const std::string& model, const std::string& brand, const std::string& engineType) {
        return model + "_" + brand + "_" + engineType;
    }

public:
    // Returns a shared flyweight for the given intrinsic state, creating it if necessary
    std::shared_ptr<CarFlyweight> getCarFlyweight(const std::string& model, const std::string& brand, const std::string& engineType) {
        std::string key = generateKey(model, brand, engineType);
        if (carMap.find(key) == carMap.end()) {
            carMap[key] = std::make_shared<CarFlyweight>(model, brand, engineType);
            std::cout << "Creating new CarFlyweight: " << key << "\n";
        } else {
            std::cout << "Reusing existing CarFlyweight: " << key << "\n";
        }
        return carMap[key];
    }
};

int main() {
    // Create the flyweight factory
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

    return 0;
}