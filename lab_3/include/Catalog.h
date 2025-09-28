#pragma once
#include "../include/LibraryCard.h"

class Catalog {
private:
  LibraryCard **cards = nullptr;
  int count = 0;
  int capacity = 2;

  void resize();

protected:
  LibraryCard *getCard(int index) const {
    if (index >= 0 && index < count) {
      return cards[index];
    }
    return nullptr;
  }

  int getInternalCount() const { return count; }

public:
  Catalog();
  virtual ~Catalog();

  void addCard(LibraryCard *card);
  virtual LibraryCard **search(const std::string &query, int &resultCount) = 0;
  int getCount() const;
};