#pragma once
#include <string>

struct LibraryCardParams {
    std::string author;
    std::string title;
    std::string authorMark;
    std::string inventoryNumber;
    std::string thematicCatalogCode;
    
    // Конструктор для удобства
    LibraryCardParams(const std::string& a, const std::string& t, 
                     const std::string& am, const std::string& in, 
                     const std::string& tcc)
        : author(a), title(t), authorMark(am), inventoryNumber(in), thematicCatalogCode(tcc) {}
};

struct IndependentPublishingParams {
    std::string author;
    std::string title;
    std::string authorMark;
    std::string inventoryNumber;
    std::string thematicCatalogCode;
    std::string publisher;
    int year;
    int circulation;
    int pages;
    
    // Конструктор для удобства
    IndependentPublishingParams(const std::string& a, const std::string& t, 
                               const std::string& am, const std::string& in, 
                               const std::string& tcc, const std::string& p, 
                               int y, int c, int pg)
        : author(a), title(t), authorMark(am), inventoryNumber(in), 
          thematicCatalogCode(tcc), publisher(p), year(y), circulation(c), pages(pg) {}
};

class LibraryCard {
private:
    std::string author;
    std::string title;
    std::string authorMark;
    std::string inventoryNumber;
    std::string thematicCatalogCode;

public:
    // Конструктор с 1 параметром вместо 5
    LibraryCard(const LibraryCardParams& params);
    
    LibraryCard(const LibraryCard&) = delete;
    LibraryCard& operator=(const LibraryCard&) = delete;
    
    LibraryCard(LibraryCard&& other) noexcept;
    LibraryCard& operator=(LibraryCard&& other) noexcept;
    
    virtual ~LibraryCard();

    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getAuthorMark() const;
    std::string getInventoryNumber() const;
    std::string getThematicCatalogCode() const;
    std::string getAlphabeticalSearch() const;
};