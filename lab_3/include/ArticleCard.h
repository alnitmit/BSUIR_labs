#pragma once
#include "../include/LibraryCard.h"
#include "../include/Article.h"
#include "../include/IndependentPublishingCard.h" 

class ArticleCard : public LibraryCard {
private:
    Article* article;
    IndependentPublishingCard* publication;

public:
    ArticleCard(const std::string& author, 
                const std::string& title, 
                const std::string& authorMark,
                const std::string& inventoryNumber,
                const std::string& thematicCatalogCode,
                Article* article,
                IndependentPublishingCard* publication);

    ArticleCard(const ArticleCard& other);
    ArticleCard& operator=(const ArticleCard& other);
    
    ArticleCard(ArticleCard&& other) noexcept;
    ArticleCard& operator=(ArticleCard&& other) noexcept;

    ~ArticleCard() override = default;

    Article* getArticle() const;
    IndependentPublishingCard* getPublication() const;
    
    std::string getArticleAuthor() const;

private:
    void copyFrom(const ArticleCard& other);
    void cleanup();
    void moveFrom(ArticleCard&& other) noexcept;
};