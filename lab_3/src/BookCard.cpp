#include "../include/BookCard.h"

BookCard::BookCard(const std::string& a, const std::string& t,
                   const std::string& am, const std::string& in,
                   const std::string& tcc, const std::string& p,
                   int y, int c, int pg)
    : IndependentPublishingCard(a, t, am, in, tcc, p, y, c, pg),
      article(new Article(t, a)) {}

BookCard::BookCard(BookCard&& other) noexcept
    : IndependentPublishingCard(std::move(other)),
      article(other.article) {
    other.article = nullptr;
}

BookCard& BookCard::operator=(BookCard&& other) noexcept {
    if (this != &other) {
        IndependentPublishingCard::operator=(std::move(other));
        
        delete article;
        article = other.article;
        other.article = nullptr;
    }
    return *this;
}

BookCard::~BookCard() {
    delete article;
}

Article* BookCard::getArticle() const { 
    return article; 
}