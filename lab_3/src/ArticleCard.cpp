#include "../include/ArticleCard.h"

// Конструктор теперь инициализирует LibraryCard
ArticleCard::ArticleCard(const LibraryCardParams& params, Article* art)
    : LibraryCard(params), article(art) {}

ArticleCard::~ArticleCard() {
    delete article;  // удаляем статью
}

Article* ArticleCard::getArticle() const { 
    return article; 
}