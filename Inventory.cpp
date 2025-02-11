// Name: Naydon Jeffrey 
// CSCI 13500
#include "Inventory.hpp"
#include "Item.hpp"  // Ensure Item.hpp is included
#include <stdexcept>

// Constructor
Inventory::Inventory(const std::vector<std::vector<Item>>& items, Item* equipped)
    : inventory_grid_(items), equipped_(equipped), weight_(0), item_count_(0) {
    for (const auto& row : inventory_grid_) {
        for (const auto& item : row) {
            if (item.type_ != ItemType::NONE) {  // Direct access to type_
                weight_ += item.weight_;  // Direct access to weight_
                item_count_++;
            }
        }
    }
}

// Getters
Item* Inventory::getEquipped() const {
    return equipped_;
}

std::vector<std::vector<Item>> Inventory::getItems() const {
    return inventory_grid_;
}

float Inventory::getWeight() const {
    return weight_;
}

size_t Inventory::getCount() const {
    return item_count_;
}

// Equip item
void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip;
}

// Discard equipped item
void Inventory::discardEquipped() {
    if (equipped_) {
        delete equipped_;
        equipped_ = nullptr;
    }
}

// Get item at position
Item Inventory::at(const size_t& row, const size_t& col) const {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[0].size()) {
        throw std::out_of_range("Invalid inventory position");
    }
    return inventory_grid_[row][col];
}

// Store item
bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup) {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[0].size()) {
        throw std::out_of_range("Invalid inventory position");
    }
    if (inventory_grid_[row][col].type_ != ItemType::NONE) {  // Direct access to type_
        return false; // Cell is occupied
    }
    inventory_grid_[row][col] = pickup;
    weight_ += pickup.weight_;  // Direct access to weight_
    item_count_++;
    return true;
}

// Copy constructor
Inventory::Inventory(const Inventory& rhs)
    : inventory_grid_(rhs.inventory_grid_), weight_(rhs.weight_), item_count_(rhs.item_count_) {
    if (rhs.equipped_) {
        equipped_ = new Item(*rhs.equipped_);
    } else {
        equipped_ = nullptr;
    }
}

// Move constructor
Inventory::Inventory(Inventory&& rhs)
    : inventory_grid_(std::move(rhs.inventory_grid_)), equipped_(rhs.equipped_), weight_(rhs.weight_), item_count_(rhs.item_count_) {
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

// Copy assignment operator
Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        
        delete equipped_;
        if (rhs.equipped_) {
            equipped_ = new Item(*rhs.equipped_);
        } else {
            equipped_ = nullptr;
        }
    }
    return *this;
}

// Move assignment operator
Inventory& Inventory::operator=(Inventory&& rhs) {
    if (this != &rhs) {
        inventory_grid_ = std::move(rhs.inventory_grid_);
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        
        delete equipped_;
        equipped_ = rhs.equipped_;
        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

// Destructor
Inventory::~Inventory() {
    delete equipped_;
}
