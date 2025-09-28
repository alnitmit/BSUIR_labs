#include "../include/ThematicCatalog.h"
#include <iostream>

LibraryCard **ThematicCatalog::search(const std::string &code,
                                      int &resultCount) {
  auto results = new LibraryCard *[getInternalCount()];
  resultCount = 0;

  for (int i = 0; i < getInternalCount(); ++i) {
    LibraryCard *card = getCard(i);
    if (card && card->getThematicCatalogCode() == code) {
      results[resultCount++] = card;
    }
  }

  return results;
}