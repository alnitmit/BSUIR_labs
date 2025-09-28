#include "../include/Catalog.h"
#include <cstring>
#include <iostream>


Catalog::Catalog() : count(0), capacity(2) {
  cards = new LibraryCard *[capacity];
  for (int i = 0; i < capacity; ++i) {
    cards[i] = nullptr;
  }
}

Catalog::~Catalog() { delete[] cards; }

void Catalog::resize() {
  int newCapacity = capacity * 2;
  auto newCards = new LibraryCard *[newCapacity];

  for (int i = 0; i < count; ++i) {
    newCards[i] = cards[i];
  }

  for (int i = count; i < newCapacity; ++i) {
    newCards[i] = nullptr;
  }

  delete[] cards;
  cards = newCards;
  capacity = newCapacity;

  std::cout << "Catalog array expanded to " << capacity << " elements\n";
}

void Catalog::addCard(LibraryCard *card) {
  if (count >= capacity) {
    resize();
  }
  cards[count++] = card;
}

int Catalog::getCount() const { return count; }