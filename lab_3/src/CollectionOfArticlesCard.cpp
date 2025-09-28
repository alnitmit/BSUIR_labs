#include "../include/CollectionOfArticlesCard.h"
#include <iostream>

CollectionOfArticlesCard::CollectionOfArticlesCard(
    const std::string& a, const std::string& t,
    const std::string& am, const std::string& in,
    const std::string& tcc, const std::string& p,
    int y, int c, int pg)
    : IndependentPublishingCard(a, t, am, in, tcc, p, y, c, pg),
      articleCount(0), capacity(2) {
    
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
    int newCapacity = capacity * 2;  // Увеличиваем емкость в 2 раза
    Article** newArticles = new Article*[newCapacity];
    
    // Копируем существующие статьи
    for (int i = 0; i < articleCount; ++i) {
        newArticles[i] = articles[i];
    }
    
    // Инициализируем оставшиеся элементы как nullptr
    for (int i = articleCount; i < newCapacity; ++i) {
        newArticles[i] = nullptr;
    }
    
    // Освобождаем старый массив и заменяем на новый
    delete[] articles;
    articles = newArticles;
    capacity = newCapacity;
    
    std::cout << "Массив расширен до " << capacity << " элементов\n";
}

void CollectionOfArticlesCard::addArticle(Article* article) {
    if (articleCount >= capacity) {
        resize();  // Расширяем массив если нужно
    }
    articles[articleCount++] = article;
}

Article* CollectionOfArticlesCard::getArticle(int index) const {
    return (index >= 0 && index < articleCount) ? articles[index] : nullptr;
}

int CollectionOfArticlesCard::getArticleCount() const { 
    return articleCount; 
}