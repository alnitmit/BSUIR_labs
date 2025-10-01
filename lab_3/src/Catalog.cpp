#include "../include/Catalog.h"
#include <iostream>

Catalog::Catalog() 
    : cards(new LibraryCard*[2]), count(0), capacity(2) 
{
    for (int i = 0; i < capacity; ++i) {
        cards[i] = nullptr;
    }
}

Catalog::~Catalog() {
    delete[] cards;
}

void Catalog::resize() {
    int newCapacity = capacity * 2;
    LibraryCard** newCards = new LibraryCard*[newCapacity];
    
    for (int i = 0; i < count; ++i) {
        newCards[i] = cards[i];
    }
    
    for (int i = count; i < newCapacity; ++i) {
        newCards[i] = nullptr;
    }
    
    delete[] cards;
    cards = newCards;
    capacity = newCapacity;
}

void Catalog::addCard(LibraryCard* card) {
    if (count >= capacity) {
        resize();
    }
    cards[count++] = card;
}

int Catalog::getCount() const {
    return count;
}

LibraryCard* Catalog::getCard(int index) const {
    if (index >= 0 && index < count) {
        return cards[index];
    }
    return nullptr;
}