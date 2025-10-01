#include "../include/CollectionOfArticlesCard.h"
#include <iostream>

CollectionOfArticlesCard::CollectionOfArticlesCard(
    const std::string& author, 
    const std::string& title, 
    const std::string& authorMark,
    const std::string& inventoryNumber,
    const std::string& thematicCatalogCode,
    const PublishingDetails& pubDetails)
    : IndependentPublishingCard(author, title, authorMark, inventoryNumber, 
                               thematicCatalogCode, pubDetails)
{
    capacity = 2;
    articles = new Article*[capacity];
    for (int i = 0; i < capacity; ++i) {
        articles[i] = nullptr;
    }
}

CollectionOfArticlesCard::~CollectionOfArticlesCard() {
    for (int i = 0; i < articleCount; ++i) {
        delete articles[i];
    }
    delete[] articles;
}

void CollectionOfArticlesCard::resize() {
    int newCapacity = capacity * 2;
    auto newArticles = new Article*[newCapacity];
    
    for (int i = 0; i < articleCount; ++i) {
        newArticles[i] = articles[i];
    }

    for (int i = articleCount; i < newCapacity; ++i) {
        newArticles[i] = nullptr;
    }
    
    delete[] articles;
    articles = newArticles;
    capacity = newCapacity; 
}

void CollectionOfArticlesCard::addArticle(Article* article) {
    if (articleCount >= capacity) {
        resize();
    }
    articles[articleCount++] = article;
}

void CollectionOfArticlesCard::addArticle(const std::string& title, const std::string& author) {
    addArticle(new Article(title, author));
}

Article* CollectionOfArticlesCard::getArticle(int index) const {
    if (index >= 0 && index < articleCount) {
        return articles[index];
    }
    return nullptr;
}

int CollectionOfArticlesCard::getArticleCount() const {
    return articleCount;
}