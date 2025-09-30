#include "../include/CollectionOfArticlesCard.h"
#include <iostream>

// Конструктор теперь принимает только 1 параметр
CollectionOfArticlesCard::CollectionOfArticlesCard(const IndependentPublishingParams& params)
    : IndependentPublishingCard(params) {
    
    articles = new Article*[capacity];
    for (int i = 0; i < capacity; ++i) {
        articles[i] = nullptr;
    }
}

CollectionOfArticlesCard::CollectionOfArticlesCard(CollectionOfArticlesCard&& other) noexcept
    : IndependentPublishingCard(std::move(other)),
      articles(other.articles),
      articleCount(other.articleCount),
      capacity(other.capacity) {
    other.articles = nullptr;
    other.articleCount = 0;
    other.capacity = 0;
}

CollectionOfArticlesCard& CollectionOfArticlesCard::operator=(CollectionOfArticlesCard&& other) noexcept {
    if (this != &other) {
        IndependentPublishingCard::operator=(std::move(other));
        
        for (int i = 0; i < articleCount; ++i) {
            delete articles[i];
        }
        delete[] articles;
        
        articles = other.articles;
        articleCount = other.articleCount;
        capacity = other.capacity;
        
        other.articles = nullptr;
        other.articleCount = 0;
        other.capacity = 0;
    }
    return *this;
}

CollectionOfArticlesCard::~CollectionOfArticlesCard() {
    for (int i = 0; i < articleCount; ++i) {
        delete articles[i];
    }
    delete[] articles;
    articles = nullptr;
    articleCount = 0;
    capacity = 0;
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
    
    std::cout << "Массив расширен до " << capacity << " элементов\n";
}

void CollectionOfArticlesCard::addArticle(Article* article) {
    if (articleCount >= capacity) {
        resize();
    }
    articles[articleCount++] = article;
}

Article* CollectionOfArticlesCard::getArticle(int index) const {
    return (index >= 0 && index < articleCount) ? articles[index] : nullptr;
}

int CollectionOfArticlesCard::getArticleCount() const { 
    return articleCount; 
}