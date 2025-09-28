#include "../include/BookCard.h"

BookCard::BookCard(const std::string &a, const std::string &t,
                   const std::string &am, const std::string &in,
                   const std::string &tcc, const std::string &p, int y, int c,
                   int pg)
    : IndependentPublishingCard(a, t, am, in, tcc, p, y, c, pg),
      article(new Article(t, a)) {}

BookCard::~BookCard() { delete article; }

Article *BookCard::getArticle() const { return article; }