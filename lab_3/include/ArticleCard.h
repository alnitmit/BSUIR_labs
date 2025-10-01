#pragma once
#include "../include/LibraryCard.h"
#include "../include/Article.h"

class IndependentPublishingCard;

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

    ~ArticleCard();

    Article* getArticle() const;
    IndependentPublishingCard* getPublication() const;

    std::string getAuthor() const;
};