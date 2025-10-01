#pragma once
#include "../include/LibraryCard.h"

class Catalog {
private:
    LibraryCard** cards = nullptr;
    int count = 0;
    int capacity = 0;

    void resize();

public:
    Catalog();
    Catalog(const Catalog& other) = delete;
    Catalog& operator=(const Catalog& other) = delete;
    
    Catalog(Catalog&& other) = delete;
    Catalog& operator=(Catalog&& other) = delete;
    
    virtual ~Catalog();

    void addCard(LibraryCard* card);
    virtual LibraryCard** search(const std::string& query, int& resultCount) = 0;
    int getCount() const;

    LibraryCard* getCard(int index) const;
};