#include "../заголовочный файл/Catalog.h"

void Catalog::addCard(LibraryCard* card) {
    cards.push_back(card);
}

LibraryCard* ThematicCatalog::search(const std::string& thematicCode) {
    for (auto card : cards) {
        if (card->getThematicCode() == thematicCode) {
            return card;
        }
    }
    return nullptr;
}

LibraryCard* AlphabeticalCatalog::search(const std::string& authorOrTitle) {
    for (auto card : cards) {
        if (card->getAuthor() == authorOrTitle || card->getTitle() == authorOrTitle) {
            return card;
        }
    }
    return nullptr;
}