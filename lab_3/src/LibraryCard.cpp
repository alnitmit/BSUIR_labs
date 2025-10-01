#include "../include/LibraryCard.h"
#include <algorithm>
#include <cctype>
#include <utility>

LibraryCard::LibraryCard(const std::string &author, const std::string &title,
                         const std::string &authorMark,
                         const std::string &inventoryNumber,
                         const std::string &thematicCatalogCode)
    : author(author), title(title), authorMark(authorMark),
      inventoryNumber(inventoryNumber),
      thematicCatalogCode(thematicCatalogCode) {}

LibraryCard::LibraryCard(const LibraryCard& other)
    : author(other.author), title(other.title), authorMark(other.authorMark),
      inventoryNumber(other.inventoryNumber),
      thematicCatalogCode(other.thematicCatalogCode) {}

LibraryCard& LibraryCard::operator=(const LibraryCard& other) {
    if (this != &other) {
        author = other.author;
        title = other.title;
        authorMark = other.authorMark;
        inventoryNumber = other.inventoryNumber;
        thematicCatalogCode = other.thematicCatalogCode;
    }
    return *this;
}

LibraryCard::LibraryCard(LibraryCard&& other) noexcept
    : author(std::move(other.author)),
      title(std::move(other.title)),
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

std::string LibraryCard::getAuthor() const { return author; }
std::string LibraryCard::getTitle() const { return title; }
std::string LibraryCard::getAuthorMark() const { return authorMark; }
std::string LibraryCard::getInventoryNumber() const { return inventoryNumber; }
std::string LibraryCard::getThematicCatalogCode() const {
  return thematicCatalogCode;
}

std::string LibraryCard::getSearchString() const {
  return author + " " + title;
}

bool LibraryCard::alphabeticalSearch(const std::string &query) const {
  if (query.empty()) {
    return false;
  }

  std::string lowerQuery = query;
  std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                 ::tolower);

  std::string lowerAuthor = author;
  std::transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(),
                 ::tolower);

  std::string lowerTitle = title;
  std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(),
                 ::tolower);

  return (lowerAuthor.find(lowerQuery) != std::string::npos) ||
         (lowerTitle.find(lowerQuery) != std::string::npos);
}