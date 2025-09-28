#include "../include/ArticleCard.h"

ArticleCard::ArticleCard(Article *art, LibraryCard *pub)
    : article(art), publication(pub) {}

ArticleCard::~ArticleCard() = default;

std::string ArticleCard::getAuthor() const { return article->getAuthor(); }

Article *ArticleCard::getArticle() const { return article; }

LibraryCard *ArticleCard::getPublication() const { return publication; }