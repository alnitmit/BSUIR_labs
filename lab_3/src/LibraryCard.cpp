#include "../include/LibraryCard.h"

LibraryCard::LibraryCard(const std::string &a, const std::string &t,
                         const std::string &am, const std::string &in,
                         const std::string &tcc)
    : author(a), title(t), authorMark(am), inventoryNumber(in),
      thematicCatalogCode(tcc) {}

std::string LibraryCard::getAuthor() const { return author; }

std::string LibraryCard::getTitle() const { return title; }

std::string LibraryCard::getAuthorMark() const { return authorMark; }

std::string LibraryCard::getInventoryNumber() const { return inventoryNumber; }

std::string LibraryCard::getThematicCatalogCode() const {
  return thematicCatalogCode;
}

std::string LibraryCard::getAlphabeticalSearch() const {
  return author + " " + title;
}