#pragma once
#include "../include/LibraryCard.h"
#include <string>

struct PublishingDetails {
    std::string publisher;
    int year;
    int circulation;
    int pages;
    
    PublishingDetails(const std::string& p, int y, int c, int pg)
        : publisher(p), year(y), circulation(c), pages(pg) {}
};

class IndependentPublishingCard : public LibraryCard {
private:
    std::string publisher;
    int year;
    int circulation;
    int pages;

public:
    IndependentPublishingCard(const std::string& author, 
                             const std::string& title, 
                             const std::string& authorMark,
                             const std::string& inventoryNumber,
                             const std::string& thematicCatalogCode,
                             const PublishingDetails& pubDetails);

    std::string getPublisher() const;
    int getYear() const;
    int getCirculation() const;
    int getPages() const;

    ~IndependentPublishingCard() override = default;
};