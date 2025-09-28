#pragma once
#include "../include/Article.h"
#include "../include/LibraryCard.h"

class ArticleCard {
private:
  Article *article;
  LibraryCard *publication;

public:
  ArticleCard(Article *art, LibraryCard *pub);
  ~ArticleCard();

  std::string getAuthor() const;
  Article *getArticle() const;
  LibraryCard *getPublication() const;
};