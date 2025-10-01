#pragma once
#include "../include/IndependentPublishingCard.h"
#include "../include/Article.h"

class CollectionOfArticlesCard : public IndependentPublishingCard {
private:
    Article** articles = nullptr;
    int articleCount = 0;
    int capacity = 0;
    void resize();

public:
    CollectionOfArticlesCard(const std::string& author, 
                            const std::string& title, 
                            const std::string& authorMark,
                            const std::string& inventoryNumber,
                            const std::string& thematicCatalogCode,
                            const PublishingDetails& pubDetails);

    CollectionOfArticlesCard(const CollectionOfArticlesCard& other) = delete;
    CollectionOfArticlesCard& operator=(const CollectionOfArticlesCard& other) = delete;
    
    CollectionOfArticlesCard(CollectionOfArticlesCard&& other) = delete;
    CollectionOfArticlesCard& operator=(CollectionOfArticlesCard&& other) = delete;

    ~CollectionOfArticlesCard() override;

    Article* getArticle(int index) const; 

    void addArticle(Article* article);
    void addArticle(const std::string& title, const std::string& author);
    int getArticleCount() const;
};