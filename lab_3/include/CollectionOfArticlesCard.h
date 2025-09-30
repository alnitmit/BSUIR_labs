#pragma once
#include "Article.h"
#include "IndependentPublishingCard.h"

class CollectionOfArticlesCard : public IndependentPublishingCard {
private:
  Article **articles;
  int articleCount = 0;
  int capacity = 2;

  void resize();

public:
  // Конструктор с 1 параметром вместо 9
  CollectionOfArticlesCard(const IndependentPublishingParams& params);

  CollectionOfArticlesCard(CollectionOfArticlesCard &&other) noexcept;
  CollectionOfArticlesCard &operator=(CollectionOfArticlesCard &&other) noexcept;

  CollectionOfArticlesCard(const CollectionOfArticlesCard &) = delete;
  CollectionOfArticlesCard &operator=(const CollectionOfArticlesCard &) = delete;

  ~CollectionOfArticlesCard() override;

  void addArticle(Article *article);
  Article *getArticle(int index) const;
  int getArticleCount() const;
};