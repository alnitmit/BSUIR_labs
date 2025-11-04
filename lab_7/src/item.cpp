#include "../include/item.h"
#include <sstream>

Item::Item() : id(0), name(""), quantity(0), cost(0.0) {}

Item::Item(int id, const std::string& name, int quantity, double cost) 
    : id(id), name(name), quantity(quantity), cost(cost) {}

int Item::getId() const { return id; }
std::string Item::getName() const { return name; }
int Item::getQuantity() const { return quantity; }
double Item::getCost() const { return cost; }

void Item::setId(int newId) { id = newId; }
void Item::setName(const std::string& newName) { name = newName; }
void Item::setQuantity(int newQuantity) { quantity = newQuantity; }
void Item::setCost(double newCost) { cost = newCost; }

void Item::serialize(std::ostream& os) const {
    os << id << "\t" << name << "\t" << quantity << "\t" << cost << "\n";
}

bool Item::deserialize(std::istream& is) {
    std::string line;
    if (!std::getline(is, line)) {
        return false;
    }

    std::istringstream iss(line);
    if (!(iss >> id)) return false;
    
    iss >> std::ws;
    if (!std::getline(iss, name, '\t')) return false;
    
    if (!(iss >> quantity)) return false;
    if (!(iss >> cost)) return false;

    return true;
}

void Item::display() const {
    std::cout << "ID: " << id << ", Name: " << name
              << ", Quantity: " << quantity << ", Cost: " << cost << '\n';
}