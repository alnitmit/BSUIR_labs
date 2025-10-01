#include "../include/BookCard.h"

BookCard::BookCard(const std::string &author, const std::string &title,
                   const std::string &authorMark,
                   const std::string &inventoryNumber,
                   const std::string &thematicCatalogCode,
                   const PublishingDetails &pubDetails)
    : IndependentPublishingCard(author, title, authorMark, inventoryNumber,
                                thematicCatalogCode, pubDetails),
      article(new Article(title, author)) {}

BookCard::~BookCard() { delete article; }

Article *BookCard::getArticle() const { return article; }