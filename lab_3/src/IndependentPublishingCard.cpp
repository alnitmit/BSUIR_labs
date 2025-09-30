#include "../include/IndependentPublishingCard.h"

IndependentPublishingCard::IndependentPublishingCard(const IndependentPublishingParams& params)
    : LibraryCard(params.libraryParams), 
      publisher(params.publishingDetails.publisher), 
      year(params.publishingDetails.year), 
      circulation(params.publishingDetails.circulation), 
      pages(params.publishingDetails.pages) {}

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