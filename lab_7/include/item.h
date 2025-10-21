#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <fstream>

class Item {
private:
    int id;
    std::string name;
    int quantity;
    double cost;

public:
    Item();
    Item(int id, const std::string& name, int quantity, double cost);
    
    int getId() const;
    std::string getName() const;
    int getQuantity() const;
    double getCost() const;
    
    void setId(int newId);
    void setName(const std::string& newName);
    void setQuantity(int newQuantity);
    void setCost(double newCost);
    
    void serialize(std::ostream& os) const;
    bool deserialize(std::istream& is);
    void display() const;
};

#endif