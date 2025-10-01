#include "../include/ThematicCatalog.h"

LibraryCard** ThematicCatalog::search(const std::string& code, int& resultCount) {
    auto results = new LibraryCard*[getCount()];
    resultCount = 0;

    for (int i = 0; i < getCount(); ++i) {
        LibraryCard* card = getCard(i);
        if (card && card->getThematicCatalogCode() == code) {
            results[resultCount++] = card;
        }
    }

    return results;
}