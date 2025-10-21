#include "../include/item.h"

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
    os.write((const char*)&id, sizeof(id));
    
    size_t nameLength = name.length();
    os.write((const char*)&nameLength, sizeof(nameLength));
    os.write(name.c_str(), nameLength);
    
    os.write((const char*)&quantity, sizeof(quantity));
    os.write((const char*)&cost, sizeof(cost));
}

bool Item::deserialize(std::istream& is) {
    is.read((char*)&id, sizeof(id));
    if (is.fail()) return false;
    
    size_t nameLength;
    is.read((char*)&nameLength, sizeof(nameLength));
    if (is.fail()) return false;
    
    char* buffer = new char[nameLength + 1];
    is.read(buffer, nameLength);
    if (is.fail()) {
        delete[] buffer;
        return false;
    }
    buffer[nameLength] = '\0';
    name = buffer;
    delete[] buffer;
    
    is.read((char*)&quantity, sizeof(quantity));
    if (is.fail()) return false;
    
    is.read((char*)&cost, sizeof(cost));
    return !is.fail();
}

void Item::display() const {
    std::cout << "ID: " << id << ", Name: " << name
              << ", Quantity: " << quantity << ", Cost: " << cost << '\n';
}