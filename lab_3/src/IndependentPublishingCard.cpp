#include "../include/IndependentPublishingCard.h"

// Конструктор теперь принимает только 1 параметр
IndependentPublishingCard::IndependentPublishingCard(const IndependentPublishingParams& params)
    : LibraryCard(LibraryCardParams(params.author, params.title, params.authorMark, 
                                   params.inventoryNumber, params.thematicCatalogCode)),
      publisher(params.publisher), year(params.year), 
      circulation(params.circulation), pages(params.pages) {}

IndependentPublishingCard::IndependentPublishingCard(IndependentPublishingCard&& other) noexcept
    : LibraryCard(std::move(other)), publisher(std::move(other.publisher)),
      year(other.year), circulation(other.circulation), pages(other.pages) {}

IndependentPublishingCard& IndependentPublishingCard::operator=(
    IndependentPublishingCard&& other) noexcept {
  if (this != &other) {
    LibraryCard::operator=(std::move(other));
    publisher = std::move(other.publisher);
    year = other.year;
    circulation = other.circulation;
    pages = other.pages;
  }
  return *this;
}

std::string IndependentPublishingCard::getPublisher() const {
  return publisher;
}

int IndependentPublishingCard::getYear() const { return year; }

int IndependentPublishingCard::getCirculation() const { return circulation; }

int IndependentPublishingCard::getPages() const { return pages; }

IndependentPublishingCard::~IndependentPublishingCard() {
    publisher.clear();
    year = 0;
    circulation = 0;
    pages = 0;
}