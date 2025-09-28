#pragma once
#include "Article.h"
#include "IndependentPublishingCard.h"


class CollectionOfArticlesCard : public IndependentPublishingCard {
private:
  Article **articles; 
  int articleCount; 
  int capacity;

  void resize(); 

public:
  CollectionOfArticlesCard(const std::string &a, const std::string &t,
                           const std::string &am, const std::string &in,
                           const std::string &tcc, const std::string &p, int y,
                           int c, int pg);

  CollectionOfArticlesCard(const CollectionOfArticlesCard &) = delete;
  CollectionOfArticlesCard &
  operator=(const CollectionOfArticlesCard &) = delete;

  ~CollectionOfArticlesCard();

  void addArticle(Article *article);
  Article *getArticle(int index) const;
  int getArticleCount() const;
};