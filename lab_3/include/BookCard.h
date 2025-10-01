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

    BookCard(const BookCard& other) = delete;
    BookCard& operator=(const BookCard& other) = delete;
    
    BookCard(BookCard&& other) = delete;
    BookCard& operator=(BookCard&& other) = delete;

    ~BookCard() override;

    Article* getArticle() const;
};