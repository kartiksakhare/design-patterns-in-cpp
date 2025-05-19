/*
 * Bridge Pattern Example: Decoupling abstraction (RemoteControl) from implementation (Device).
 *
 * - Abstraction: RemoteControl (interface for remotes)
 * - Refined Abstractions: BasicRemote, AdvancedRemote (different types of remotes)
 * - Implementor: Device (interface for devices)
 * - Concrete Implementors: TV, Radio (different devices)
 *
 * This demonstrates how the Bridge pattern allows remotes and devices to vary independently.
 * Any remote can control any device, and new remotes/devices can be added without modifying existing code.
 */

#include <iostream>
#include <memory>

// Implementation hierarchy: Device
class Device {
public:
    // Turns the device on
    virtual void turnOn() = 0;
    // Turns the device off
    virtual void turnOff() = 0;
    // Virtual destructor for safe polymorphic deletion
    virtual ~Device() = default;
};

// Concrete Implementor: TV
class TV : public Device {
public:
    void turnOn() override {
        std::cout << "TV is now ON." << std::endl;
    }
    void turnOff() override {
        std::cout << "TV is now OFF." << std::endl;
    }
};

// Concrete Implementor: Radio
class Radio : public Device {
public:
    void turnOn() override {
        std::cout << "Radio is now ON." << std::endl;
    }
    void turnOff() override {
        std::cout << "Radio is now OFF." << std::endl;
    }
};

// Abstraction hierarchy: RemoteControl
class RemoteControl {
protected:
    std::shared_ptr<Device> device;
public:
    // Constructor takes a device to control
    explicit RemoteControl(std::shared_ptr<Device> dev) : device(std::move(dev)) {}
    // Abstract method for pressing the power button
    virtual void pressPowerButton() = 0;
    virtual ~RemoteControl() = default;
};

// Refined Abstraction: BasicRemote
class BasicRemote : public RemoteControl {
public:
    explicit BasicRemote(std::shared_ptr<Device> dev) : RemoteControl(std::move(dev)) {}
    // Turns the device on
    void pressPowerButton() override {
        std::cout << "Basic remote!" << std::endl;
        device->turnOn();
    }
};

// Refined Abstraction: AdvancedRemote
class AdvancedRemote : public RemoteControl {
public:
    explicit AdvancedRemote(std::shared_ptr<Device> dev) : RemoteControl(std::move(dev)) {}
    // Turns the device on
    void pressPowerButton() override {
        std::cout << "Advanced remote!" << std::endl;
        device->turnOn();
    }
    // Turns the device off (additional functionality)
    void pressPowerOffButton() {
        std::cout << "Advanced remote!" << std::endl;
        device->turnOff();
    }
};

int main() {
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

    return 0;
}