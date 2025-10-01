#pragma once
#include "../include/IndependentPublishingCard.h"
#include "../include/Article.h"

class CollectionOfArticlesCard : public IndependentPublishingCard {
private:
    Article** articles;
    int articleCount;
    int capacity;
    void resize();

public:
    CollectionOfArticlesCard(const std::string& author, 
                            const std::string& title, 
                            const std::string& authorMark,
                            const std::string& inventoryNumber,
                            const std::string& thematicCatalogCode,
                            const PublishingDetails& pubDetails);

    ~CollectionOfArticlesCard();

    Article* getArticle(int index) const; 

    void addArticle(Article* article);
    void addArticle(const std::string& title, const std::string& author);
    int getArticleCount() const;
};