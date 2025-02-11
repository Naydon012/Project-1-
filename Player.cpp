// Name: Naydon Jeffrey 
// CSCI 13500
#include "Player.hpp"

// Constructor with default parameters for name and inventory
Player::Player(const std::string& name, const Inventory& inventory)
    : name_(name), inventory_(inventory) {}

// Getter
std::string Player::getName() const {
    return name_;
}

// Getter 
Inventory& Player::getInventoryRef() {
    return inventory_;
}

// Copy constructor
Player::Player(const Player& rhs)
    : name_(rhs.name_), inventory_(rhs.inventory_) {}

// Move constructor
Player::Player(Player&& rhs) 
    : name_(std::move(rhs.name_)), inventory_(std::move(rhs.inventory_)) {}

// Copy assignment operator
Player& Player::operator=(const Player& rhs) {
    if (this != &rhs) { // Avoid self-assignment
        name_ = rhs.name_;
        inventory_ = rhs.inventory_;
    }
    return *this;
}

// Move assignment
Player& Player::operator=(Player&& rhs) {
    if (this != &rhs) { // Avoid self-assignment
        name_ = std::move(rhs.name_);
        inventory_ = std::move(rhs.inventory_);
    }
    return *this;
}

// Destructor for the Player class
Player::~Player() = default;
