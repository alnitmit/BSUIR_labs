#ifndef CATALOG_H
#define CATALOG_H

#include "LibraryCard.h"
#include <vector>

class Catalog {
protected:
    std::vector<LibraryCard*> cards;
public:
    virtual ~Catalog() = default;
    void addCard(LibraryCard* card);
    virtual LibraryCard* search(const std::string& query) = 0;
};

class ThematicCatalog : public Catalog {
public:
    LibraryCard* search(const std::string& thematicCode) override;
};

class AlphabeticalCatalog : public Catalog {
public:
    LibraryCard* search(const std::string& authorOrTitle) override;
};

#endif