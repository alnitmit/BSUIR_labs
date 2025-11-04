#include "../include/inventory.h"
#include <fstream>
#include <iostream>
#include <limits>


Inventory::Inventory(const std::string &filename,
                     const std::string &tempFilename)
    : filename(filename), tempFilename(tempFilename) {
  initializeFile();
}

bool Inventory::getValidInput(const std::string &prompt, int &value) {
  if (!prompt.empty()) {
    std::cout << prompt;
  }
  std::cin >> value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Operation cancelled.\n";
    return false;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return true;
}

bool Inventory::getValidInput(const std::string &prompt, double &value) {
  std::cout << prompt;
  std::cin >> value;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Operation cancelled.\n";
    return false;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return true;
}

bool Inventory::itemExists(int id) {
  std::ifstream file(filename);
  if (!file)
    return false;

  Item temp;
  while (temp.deserialize(file)) {
    if (temp.getId() == id) {
      file.close();
      return true;
    }
  }
  file.close();
  return false;
}

bool Inventory::findItem(int id, Item &foundItem, long &position) {
  std::ifstream file(filename);
  if (!file)
    return false;

  position = file.tellg();
  Item temp;
  while (temp.deserialize(file)) {
    if (temp.getId() == id) {
      foundItem = temp;
      file.close();
      return true;
    }
    position = file.tellg();
  }
  file.close();
  return false;
}

bool Inventory::updateItemInFile(long position, const Item &item) {
  std::fstream file(filename, std::ios::in | std::ios::out);
  if (!file)
    return false;

  file.seekp(position, std::ios::beg);
  if (file.fail()) {
    file.close();
    return false;
  }

  item.serialize(file);
  bool success = !file.fail();
  file.close();
  return success;
}

void Inventory::initializeFile() {
  std::fstream file(filename, std::ios::out | std::ios::in);
  if (!file) {
    file.open(filename, std::ios::out);
    file.close();
  }
}

void Inventory::addItem() {
  int id;
  if (!getValidInput("Enter item ID: ", id))
    return;

  if (itemExists(id)) {
    std::cout << "Item with this ID already exists.\n";
    return;
  }

  std::string name;
  std::cout << "Enter item name: ";
  std::getline(std::cin, name);

  int quantity;
  if (!getValidInput("Enter quantity: ", quantity))
    return;

  double cost;
  if (!getValidInput("Enter cost: ", cost))
    return;

  Item newItem(id, name, quantity, cost);

  std::ofstream file(filename, std::ios::app);
  if (file) {
    newItem.serialize(file);
    std::cout << "Item added successfully.\n";
  } else {
    std::cout << "Error opening file for writing.\n";
  }
  file.close();
}

void Inventory::displayAllItems() {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "No items found.\n";
    return;
  }

  Item temp;
  bool found = false;
  while (temp.deserialize(file)) {
    temp.display();
    found = true;
  }

  if (!found) {
    std::cout << "No items found.\n";
  }
  file.close();
}

void Inventory::deleteItem() {
  int idToDelete;
  if (!getValidInput("Enter item ID to delete: ", idToDelete))
    return;

  std::ifstream inFile(filename);
  if (!inFile) {
    std::cout << "Error opening file for reading.\n";
    return;
  }

  std::ofstream tempFile(tempFilename, std::ios::out);
  if (!tempFile) {
    std::cout << "Error creating temporary file.\n";
    inFile.close();
    return;
  }

  Item temp;
  bool found = false;

  while (temp.deserialize(inFile)) {
    if (temp.getId() == idToDelete) {
      found = true;
    } else {
      temp.serialize(tempFile);
    }
  }

  inFile.close();
  tempFile.close();

  if (found) {
    if (std::remove(filename.c_str()) != 0) {
      std::cout << "Error deleting original file.\n";
      return;
    }
    if (std::rename(tempFilename.c_str(), filename.c_str()) != 0) {
      std::cout << "Error renaming temporary file.\n";
    } else {
      std::cout << "Item deleted successfully.\n";
    }
  } else {
    std::remove(tempFilename.c_str());
    std::cout << "Item not found.\n";
  }
}

void Inventory::updateItem() {
  int idToUpdate;
  if (!getValidInput("Enter item ID to update: ", idToUpdate))
    return;

  Item foundItem;
  long position;
  if (findItem(idToUpdate, foundItem, position)) {
    std::cout << "Current item: ";
    foundItem.display();

    std::string name;
    std::cout << "Enter new name: ";
    std::getline(std::cin, name);

    int quantity;
    if (!getValidInput("Enter new quantity: ", quantity))
      return;

    double cost;
    if (!getValidInput("Enter new cost: ", cost))
      return;

    foundItem.setName(name);
    foundItem.setQuantity(quantity);
    foundItem.setCost(cost);

    if (updateItemInFile(position, foundItem)) {
      std::cout << "Item updated successfully.\n";
    } else {
      std::cout << "Error updating file.\n";
    }
  } else {
    std::cout << "Item not found.\n";
  }
}