#pragma once
#include "../include/LibraryCard.h"

class IndependentPublishingCard : public LibraryCard {
private:
    std::string publisher;
    int year;
    int circulation;
    int pages;

public:
    IndependentPublishingCard(const IndependentPublishingParams& params);

    IndependentPublishingCard(const IndependentPublishingCard&) = delete;
    IndependentPublishingCard& operator=(const IndependentPublishingCard&) = delete;

    IndependentPublishingCard(IndependentPublishingCard&& other) noexcept;
    IndependentPublishingCard& operator=(IndependentPublishingCard&& other) noexcept;

    ~IndependentPublishingCard() override;

    std::string getPublisher() const;
    int getYear() const;
    int getCirculation() const;
    int getPages() const;
};