#include "../include/LibraryCard.h"

LibraryCard::LibraryCard(const LibraryCardParams& params)
    : author(params.author), title(params.title), authorMark(params.authorMark),
      inventoryNumber(params.inventoryNumber), thematicCatalogCode(params.thematicCatalogCode) {}

LibraryCard::LibraryCard(LibraryCard&& other) noexcept
    : author(std::move(other.author)), title(std::move(other.title)),
      authorMark(std::move(other.authorMark)),
      inventoryNumber(std::move(other.inventoryNumber)),
      thematicCatalogCode(std::move(other.thematicCatalogCode)) {}

LibraryCard& LibraryCard::operator=(LibraryCard&& other) noexcept {
  if (this != &other) {
    author = std::move(other.author);
    title = std::move(other.title);
    authorMark = std::move(other.authorMark);
    inventoryNumber = std::move(other.inventoryNumber);
    thematicCatalogCode = std::move(other.thematicCatalogCode);
  }
  return *this;
}

LibraryCard::~LibraryCard() {
    author.clear();
    title.clear();
    authorMark.clear();
    inventoryNumber.clear();
    thematicCatalogCode.clear();
}

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