#pragma once
#include "../include/LibraryCard.h"

class IndependentPublishingCard : public LibraryCard {
protected:
  std::string publisher;
  int year;
  int circulation;
  int pages;

public:
  IndependentPublishingCard(const std::string &a, const std::string &t,
                            const std::string &am, const std::string &in,
                            const std::string &tcc, const std::string &p, int y,
                            int c, int pg);

  std::string getPublisher() const;
  int getYear() const;
  int getCirculation() const;
  int getPages() const;
};