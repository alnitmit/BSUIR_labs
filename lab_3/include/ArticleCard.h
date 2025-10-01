#pragma once
#include "../include/Article.h"
#include "../include/LibraryCard.h"

class ArticleCard : public LibraryCard {  // ← ДОБАВЛЕНО НАСЛЕДОВАНИЕ
private:
    Article* article;
    // publication удален, так как теперь ArticleCard сам является LibraryCard

public:
    // Конструктор теперь принимает параметры для LibraryCard
    ArticleCard(const LibraryCardParams& params, Article* art);
    ~ArticleCard() override;

    // Методы из LibraryCard уже унаследованы
    Article* getArticle() const;
    
    // getPublication() больше не нужен, так как ArticleCard теперь сам является карточкой
};