#include "../include/ArticleCard.h"
#include "../include/IndependentPublishingCard.h"

ArticleCard::ArticleCard(const std::string &author, const std::string &title,
                         const std::string &authorMark,
                         const std::string &inventoryNumber,
                         const std::string &thematicCatalogCode,
                         Article *article,
                         IndependentPublishingCard *publication)
    : LibraryCard(author, title, authorMark, inventoryNumber,
                  thematicCatalogCode),
      article(article), publication(publication) {}

ArticleCard::~ArticleCard() {
  article = nullptr;
  publication = nullptr;
}

Article *ArticleCard::getArticle() const { return article; }

IndependentPublishingCard *ArticleCard::getPublication() const {
  return publication;
}

std::string ArticleCard::getAuthor() const {
  if (article) {
    return article->getAuthor();
  }
  return LibraryCard::getAuthor();
}