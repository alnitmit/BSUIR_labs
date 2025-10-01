#include "../include/IndependentPublishingCard.h"

IndependentPublishingCard::IndependentPublishingCard(
    const std::string& author, 
    const std::string& title, 
    const std::string& authorMark,
    const std::string& inventoryNumber,
    const std::string& thematicCatalogCode,
    const PublishingDetails& pubDetails)
    : LibraryCard(author, title, authorMark, inventoryNumber, thematicCatalogCode),
      publisher(pubDetails.publisher), 
      year(pubDetails.year), 
      circulation(pubDetails.circulation), 
      pages(pubDetails.pages) {
}

std::string IndependentPublishingCard::getPublisher() const {
    return publisher;
}

int IndependentPublishingCard::getYear() const {
    return year;
}

int IndependentPublishingCard::getCirculation() const {
    return circulation;
}

int IndependentPublishingCard::getPages() const {
    return pages;
}