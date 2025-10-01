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

ArticleCard::ArticleCard(ArticleCard&& other) noexcept
    : LibraryCard(std::move(other)),
      article(other.article),
      publication(other.publication)
{
    other.article = nullptr;
    other.publication = nullptr;
}

ArticleCard& ArticleCard::operator=(ArticleCard&& other) noexcept {
    if (this != &other) {
        cleanup();
        
        LibraryCard::operator=(std::move(other));
        
        article = other.article;
        publication = other.publication;
        
        other.article = nullptr;
        other.publication = nullptr;
    }
    return *this;
}

ArticleCard::~ArticleCard() {
    cleanup();
}

void ArticleCard::copyFrom(const ArticleCard& other) {
    if (other.article) {
        article = new Article(*other.article);
    }
    if (other.publication) {
        publication = new IndependentPublishingCard(*other.publication);
    }
}

void ArticleCard::cleanup() {
    delete article;
    delete publication;
    article = nullptr;
    publication = nullptr;
}

Article* ArticleCard::getArticle() const { 
    return article; 
}

IndependentPublishingCard* ArticleCard::getPublication() const {
    return publication;
}

std::string ArticleCard::getAuthor() const {
    if (article) {
        return article->getAuthor();
    }
    return LibraryCard::getAuthor();
}