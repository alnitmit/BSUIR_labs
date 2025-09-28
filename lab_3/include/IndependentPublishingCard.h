#pragma once
#include "../include/LibraryCard.h"

class IndependentPublishingCard : public LibraryCard {
private:
  std::string publisher;
  int year;
  int circulation;
  int pages;

public:
  IndependentPublishingCard(const std::string &a, const std::string &t,
                            const std::string &am, const std::string &in,
                            const std::string &tcc, const std::string &p, int y,
                            int c, int pg);

  IndependentPublishingCard(const IndependentPublishingCard &) = delete;
  IndependentPublishingCard &
  operator=(const IndependentPublishingCard &) = delete;

  IndependentPublishingCard(IndependentPublishingCard &&other) noexcept;
  IndependentPublishingCard &
  operator=(IndependentPublishingCard &&other) noexcept;

  ~IndependentPublishingCard() = default;

  std::string getPublisher() const;
  int getYear() const;
  int getCirculation() const;
  int getPages() const;
};