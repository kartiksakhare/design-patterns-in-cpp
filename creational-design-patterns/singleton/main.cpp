#include <map>
#include <string>
#include <iostream>

// Singleton class to manage global coffee configuration settings
class GlobalCoffeeConfig final {
private:
    // Stores coffee configuration as key-value pairs (e.g., "milk" -> "Almond")
    std::map<std::string, std::string> coffeeState;

    // Private constructor prevents external instantiation of the class
    GlobalCoffeeConfig() {}

    // Prevent heap allocation
    static void* operator new(std::size_t) = delete;
    static void operator delete(void*) = delete;

public:
    // Delete copy constructor to prevent copying the singleton instance
    GlobalCoffeeConfig(const GlobalCoffeeConfig&) = delete;

    // Delete assignment operator to prevent assignment
    GlobalCoffeeConfig& operator=(const GlobalCoffeeConfig&) = delete;

    // Delete move constructor and move assignment operator
    GlobalCoffeeConfig(GlobalCoffeeConfig&&) = delete;
    GlobalCoffeeConfig& operator=(GlobalCoffeeConfig&&) = delete;

    // Static method to access the single instance (thread-safe in C++11 and later)
    static GlobalCoffeeConfig& getInstance() {
        static GlobalCoffeeConfig config;  // Guaranteed to be initialized only once
        return config;
    }

    // Sets a key-value pair in the configuration
    void setState(const std::string& key, const std::string& value) {
        coffeeState.insert({key, value});
    }

    // Retrieves the value for a given key; returns an empty string if not found
    std::string getState(const std::string& key) {
        auto it = coffeeState.find(key);
        if (it != coffeeState.end()) {
            return it->second;
        }
        return "";
    }

    // Clears all key-value pairs in the configuration
    void clearState() {
        coffeeState.clear();
    }

    // Removes a specific key-value pair by key
    void removeState(const std::string& key) {
        coffeeState.erase(key);
    }

    // Checks if a key exists in the configuration
    bool hasState(const std::string& key) {
        return coffeeState.find(key) != coffeeState.end();
    }

    // Retrieves the value for a key or returns a default value if key is not found
    std::string getStateOrDefault(const std::string& key, const std::string& defaultValue) {
        auto it = coffeeState.find(key);
        if (it != coffeeState.end()) {
            return it->second;
        }
        return defaultValue;
    }

    // Prints all key-value pairs to the console
    void printState() {
        for (const auto& pair : coffeeState) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

// Simple test function to check singleton restrictions
void testSingletonRestrictions() {
    std::cout << "\nTesting singleton restrictions:\n";

    // 1. Attempt to copy construct (should fail to compile if uncommented)
    // GlobalCoffeeConfig copyConfig(GlobalCoffeeConfig::getInstance()); // Error

    // 2. Attempt to assign (should fail to compile if uncommented)
    // GlobalCoffeeConfig assignConfig = GlobalCoffeeConfig::getInstance(); // Error

    // 3. Attempt to directly construct (should fail to compile if uncommented)
    // GlobalCoffeeConfig directConfig; // Error

    // 4. Attempt to allocate on heap (should fail to compile if uncommented)
    // GlobalCoffeeConfig* heapConfig = new GlobalCoffeeConfig(); // Error

    // 5. Attempt to delete instance (should fail to compile if uncommented)
    // delete &GlobalCoffeeConfig::getInstance(); // Error

    std::cout << "All singleton restrictions are enforced by the compiler (see commented lines).\n";
}

// Demonstrates usage of the GlobalCoffeeConfig singleton
int main() {
    // Get reference to the singleton instance
    GlobalCoffeeConfig& config = GlobalCoffeeConfig::getInstance();

    // Check if both references point to the same instance:
    GlobalCoffeeConfig& config2 = GlobalCoffeeConfig::getInstance();
    std::cout << "config and config2 are the same instance: "
              << (&config == &config2 ? "Yes" : "No") << std::endl;

    // Set some coffee preferences
    config.setState("coffeeType", "Espresso");
    config.setState("milk", "Almond");
    config.setState("sugar", "Brown");

    std::cout << "Current Coffee Config:" << std::endl;
    config.printState();  // Display current configuration

    // Check for a specific setting and get a value with a fallback
    std::cout << "Has milk: " << (config.hasState("milk") ? "Yes" : "No") << std::endl;
    std::cout << "Sugar: " << config.getStateOrDefault("sugar", "None") << std::endl;

    // Get a value directly
    std::cout << "Coffee Type: " << config.getState("coffeeType") << std::endl;

    // Remove a setting and display the updated configuration
    std::string removedSugar = config.getState("sugar");
    config.removeState("sugar");
    std::cout << "Removed sugar: " << removedSugar << std::endl;
    std::cout << "After removing sugar:" << std::endl;
    config.printState();

    // Clear all settings
    config.clearState();
    std::cout << "After clearing all settings:" << std::endl;
    config.printState();

    // Demonstrate hasState and getStateOrDefault after clearing
    std::cout << "Has milk after clear: " << (config.hasState("milk") ? "Yes" : "No") << std::endl;
    std::cout << "Milk (default): " << config.getStateOrDefault("milk", "None") << std::endl;

    // Run singleton restriction tests
    testSingletonRestrictions();

    return 0;
}
