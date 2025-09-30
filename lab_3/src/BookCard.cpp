#include "../include/BookCard.h"

// Конструктор теперь принимает только 1 параметр
BookCard::BookCard(const IndependentPublishingParams& params)
    : IndependentPublishingCard(params),
      article(new Article(params.title, params.author)) {}

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
    article = nullptr;
}

Article* BookCard::getArticle() const { 
    return article; 
}