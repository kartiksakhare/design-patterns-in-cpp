/*
 * Adapter Pattern Example: Adapting a European plug to an American socket.
 * 
 * - Target: AmericanSocket (interface expected by the client)
 * - Adaptee: EuropeanPlug (incompatible interface)
 * - Adapter: PlugAdapter (makes EuropeanPlug compatible with AmericanSocket)
 * 
 * This demonstrates how to use the Adapter pattern to allow incompatible interfaces to work together.
 */

#include <iostream>
#include <memory>

// Target interface: AmericanSocket
class AmericanSocket {
public:
    // Provides power to an American plug
    virtual void providePower() const = 0;
    virtual ~AmericanSocket() = default;
};

// Adaptee: EuropeanPlug (incompatible with AmericanSocket)
class EuropeanPlug {
public:
    // Connects to a European socket
    void connect() const {
        std::cout << "European plug connected to European socket." << std::endl;
    }
};

// Adapter: Allows a EuropeanPlug to be used with an AmericanSocket
class PlugAdapter : public AmericanSocket {
private:
    std::shared_ptr<EuropeanPlug> europeanPlug;
public:
    explicit PlugAdapter(std::shared_ptr<EuropeanPlug> plug) : europeanPlug(std::move(plug)) {}

    void providePower() const override {
        if (!europeanPlug) {
            std::cout << "No plug connected to adapter!" << std::endl;
            return;
        }
        std::cout << "Adapter converting plug..." << std::endl;
        europeanPlug->connect();
        std::cout << "Power provided through adapter." << std::endl;
    }
};

int main() {
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

    return 0;
}