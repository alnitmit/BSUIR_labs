#pragma once
#include "../include/Article.h"
#include "../include/IndependentPublishingCard.h"

class BookCard : public IndependentPublishingCard {
private:
    Article* article;

public:
    BookCard(const std::string& author, 
             const std::string& title, 
             const std::string& authorMark,
             const std::string& inventoryNumber,
             const std::string& thematicCatalogCode,
             const PublishingDetails& pubDetails);

    ~BookCard();

    Article* getArticle() const;
};