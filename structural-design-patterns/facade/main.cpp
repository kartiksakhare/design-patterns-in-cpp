/*
 * Facade Pattern Example: Simplifying home theater system usage.
 *
 * - Subsystems: Projector, SoundSystem, DVDPlayer, Screen (each with their own interface)
 * - Facade: HomeTheaterFacade (provides a simple interface to control the whole system)
 *
 * This demonstrates how the Facade pattern provides a unified, high-level interface
 * to a set of interfaces in a subsystem, making the subsystem easier to use.
 * The client interacts only with the Facade, not with the individual subsystem classes.
 */

#include <iostream>
#include <memory>

// Subsystem 1: Projector
class Projector {
public:
    void turnOn() {
        std::cout << "Projector is now ON." << std::endl;
    }
    void turnOff() {
        std::cout << "Projector is now OFF." << std::endl;
    }
};

// Subsystem 2: SoundSystem
class SoundSystem {
public:
    void turnOn() {
        std::cout << "Sound System is now ON." << std::endl;
    }
    void turnOff() {
        std::cout << "Sound System is now OFF." << std::endl;
    }
    void setVolume(int level) {
        std::cout << "Setting sound system volume to " << level << "." << std::endl;
    }
}; 

// Subsystem 3: DVDPlayer
class DVDPlayer {
public:
    void turnOn() {
        std::cout << "DVD Player is now ON." << std::endl;
    }
    void turnOff() {
        std::cout << "DVD Player is now OFF." << std::endl;
    }
    void playMovie(const std::string& movie) {
        std::cout << "Playing movie: " << movie << std::endl;
    }
};

// Subsystem 4: Screen
class Screen {
public:
    void lower() {
        std::cout << "Screen is now lowered." << std::endl;
    }
    void raise() {
        std::cout << "Screen is now raised." << std::endl;
    }
};

// Facade Class: Provides a simple interface to control the home theater system
class HomeTheaterFacade {
private:
    std::unique_ptr<Projector> projector;
    std::unique_ptr<SoundSystem> soundSystem;
    std::unique_ptr<DVDPlayer> dvdPlayer;
    std::unique_ptr<Screen> screen;

public:
    // Constructor initializes all subsystems
    HomeTheaterFacade()
        : projector(std::make_unique<Projector>()),
          soundSystem(std::make_unique<SoundSystem>()),
          dvdPlayer(std::make_unique<DVDPlayer>()),
          screen(std::make_unique<Screen>()) {}

    // High-level method to start watching a movie
    void watchMovie(const std::string& movie) {
        std::cout << "Getting ready to watch a movie..." << std::endl;
        screen->lower();
        projector->turnOn();
        soundSystem->turnOn();
        soundSystem->setVolume(5);
        dvdPlayer->turnOn();
        dvdPlayer->playMovie(movie);
    }

    // High-level method to end the movie and shut down the system
    void endMovie() {
        std::cout << "Shutting down home theater..." << std::endl;
        dvdPlayer->turnOff();
        soundSystem->turnOff();
        projector->turnOff();
        screen->raise();
    }
};

int main() {
    // Client uses only the Facade to control the home theater
    HomeTheaterFacade homeTheater;

    homeTheater.watchMovie("Inception");
    std::cout << "Enjoy the movie!" << std::endl;

    homeTheater.endMovie();
    std::cout << "Movie ended. Home theater is now off." << std::endl;

    return 0;
}