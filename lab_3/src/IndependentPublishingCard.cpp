#include "../include/IndependentPublishingCard.h"

IndependentPublishingCard::IndependentPublishingCard(
    const std::string &a, const std::string &t, const std::string &am,
    const std::string &in, const std::string &tcc, const std::string &p, int y,
    int c, int pg)
    : LibraryCard(a, t, am, in, tcc), publisher(p), year(y), circulation(c),
      pages(pg) {}

std::string IndependentPublishingCard::getPublisher() const {
  return publisher;
}

int IndependentPublishingCard::getYear() const { return year; }

int IndependentPublishingCard::getCirculation() const { return circulation; }

int IndependentPublishingCard::getPages() const { return pages; }