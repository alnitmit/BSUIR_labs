#pragma once
#include <string>

struct BasicCardParams {
    std::string author;
    std::string title;
    std::string authorMark;
    
    BasicCardParams(const std::string& a, const std::string& t, const std::string& am)
        : author(a), title(t), authorMark(am) {}
};

struct LibraryCardParams : BasicCardParams {
    std::string inventoryNumber;
    std::string thematicCatalogCode;
    
    LibraryCardParams(const std::string& a, const std::string& t, const std::string& am,
                     const std::string& in, const std::string& tcc)
        : BasicCardParams(a, t, am), inventoryNumber(in), thematicCatalogCode(tcc) {}
};

struct PublishingDetails {
    std::string publisher;
    int year;
    int circulation;
    int pages;
    
    PublishingDetails(const std::string& p, int y, int c, int pg)
        : publisher(p), year(y), circulation(c), pages(pg) {}
};

struct IndependentPublishingParams {
    LibraryCardParams libraryParams;
    PublishingDetails publishingDetails;
    
    IndependentPublishingParams(const LibraryCardParams& libParams, const PublishingDetails& pubDetails)
        : libraryParams(libParams), publishingDetails(pubDetails) {}
};

class LibraryCard {
private:
    std::string author;
    std::string title;
    std::string authorMark;
    std::string inventoryNumber;
    std::string thematicCatalogCode;

public:
    explicit LibraryCard(const LibraryCardParams& params);
    
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