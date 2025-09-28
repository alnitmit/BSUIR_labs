#pragma once
#include "../include/LibraryCard.h"

class Catalog {
protected:
    LibraryCard** cards;
    int count;
    int capacity;
    
    void resize();

public:
    Catalog();
    virtual ~Catalog();
    
    void addCard(LibraryCard* card);
    virtual LibraryCard** search(const std::string& query, int& resultCount) = 0;
    int getCount() const;
};