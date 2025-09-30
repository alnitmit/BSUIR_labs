#pragma once
#include "../include/Article.h"
#include "../include/IndependentPublishingCard.h"

class BookCard : public IndependentPublishingCard {
private:
  Article *article;

public:
  // Конструктор с 1 параметром вместо 9
  BookCard(const IndependentPublishingParams& params);

  BookCard(const BookCard &) = delete;
  BookCard &operator=(const BookCard &) = delete;

  BookCard(BookCard &&other) noexcept;
  BookCard &operator=(BookCard &&other) noexcept;

  ~BookCard() override;

  Article *getArticle() const;
};