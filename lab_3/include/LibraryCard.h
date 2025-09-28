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
    LibraryCard(const std::string& a, const std::string& t, const std::string& am,
               const std::string& in, const std::string& tcc);
    
    LibraryCard(const LibraryCard&) = delete;
    LibraryCard& operator=(const LibraryCard&) = delete;
    
    LibraryCard(LibraryCard&& other) noexcept;
    LibraryCard& operator=(LibraryCard&& other) noexcept;
    
    virtual ~LibraryCard() = default;

    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getAuthorMark() const;
    std::string getInventoryNumber() const;
    std::string getThematicCatalogCode() const;
    std::string getAlphabeticalSearch() const;
};