#include "../include/ArticleCard.h"
#include "../include/IndependentPublishingCard.h"

ArticleCard::ArticleCard(const std::string& author, 
                         const std::string& title, 
                         const std::string& authorMark,
                         const std::string& inventoryNumber,
                         const std::string& thematicCatalogCode,
                         Article* article,
                         IndependentPublishingCard* publication)
    : LibraryCard(author, title, authorMark, inventoryNumber, thematicCatalogCode),
      article(article),
      publication(publication) 
{}

ArticleCard::ArticleCard(const ArticleCard& other)
    : LibraryCard(other),
      article(nullptr),
      publication(nullptr)
{
    copyFrom(other);
}

ArticleCard& ArticleCard::operator=(const ArticleCard& other) {
    if (this != &other) {
        LibraryCard::operator=(other);
        cleanup();
        copyFrom(other);
    }
    return *this;
}

ArticleCard::ArticleCard(ArticleCard&& other) noexcept
    : LibraryCard(std::move(other)),
      article(nullptr),
      publication(nullptr)
{
    moveFrom(std::move(other));
}

ArticleCard& ArticleCard::operator=(ArticleCard&& other) noexcept {
    if (this != &other) {
        LibraryCard::operator=(std::move(other));
        cleanup();
        moveFrom(std::move(other));
    }
    return *this;
}

void ArticleCard::copyFrom(const ArticleCard& other) {
    if (other.article) {
        article = new Article(*other.article);
    }
    publication = other.publication;
}

void ArticleCard::moveFrom(ArticleCard&& other) noexcept {
    article = other.article;
    publication = other.publication;
    
    other.article = nullptr;
    other.publication = nullptr;
}

void ArticleCard::cleanup() {
    delete article;
    article = nullptr;
    publication = nullptr;
}

Article* ArticleCard::getArticle() const { 
    return article; 
}

IndependentPublishingCard* ArticleCard::getPublication() const {
    return publication;
}

std::string ArticleCard::getArticleAuthor() const {
    if (article) {
        return article->getAuthor();
    }
    return LibraryCard::getAuthor();
}