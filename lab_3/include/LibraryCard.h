#pragma once
#include <string>

class LibraryCard {
private:
  std::string author;
  std::string title;
  std::string authorMark;
  std::string inventoryNumber;
  std::string thematicCatalogCode;

public:
  LibraryCard(const std::string &author, const std::string &title,
              const std::string &authorMark, const std::string &inventoryNumber,
              const std::string &thematicCatalogCode);

  LibraryCard(const LibraryCard& other) = default;
  LibraryCard& operator=(const LibraryCard& other) = default;
  
  LibraryCard(LibraryCard&& other) noexcept = default;
  LibraryCard& operator=(LibraryCard&& other) noexcept = default;

  virtual ~LibraryCard() = default;

  std::string getAuthor() const;
  std::string getTitle() const;
  std::string getAuthorMark() const;
  std::string getInventoryNumber() const;
  std::string getThematicCatalogCode() const;

  bool alphabeticalSearch(const std::string &query) const;
  std::string getSearchString() const;
};