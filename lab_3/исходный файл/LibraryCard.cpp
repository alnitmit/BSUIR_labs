#include "../заголовочный файл/LibraryCard.h"

LibraryCard::LibraryCard(const std::string& a, const std::string& t,
                       const std::string& am, const std::string& in,
                       const std::string& tc)
    : author(a), title(t), authorMark(am), 
      inventoryNumber(in), thematicCode(tc) {}

std::string LibraryCard::getAuthor() const { return author; }
std::string LibraryCard::getTitle() const { return title; }
std::string LibraryCard::getAuthorMark() const { return authorMark; }
std::string LibraryCard::getInventoryNumber() const { return inventoryNumber; }
std::string LibraryCard::getThematicCode() const { return thematicCode; }
std::string LibraryCard::getAlphabeticalIndex() const {
    return author + " " + title;
}

IndependentPublication::IndependentPublication(const std::string& a, const std::string& t,
                                             const std::string& am, const std::string& in,
                                             const std::string& tc, const std::string& pub,
                                             int y, int circ, int pages)
    : LibraryCard(a, t, am, in, tc), publisher(pub),
      year(y), circulation(circ), pageCount(pages) {}

std::string IndependentPublication::getPublisher() const { return publisher; }
int IndependentPublication::getYear() const { return year; }
int IndependentPublication::getCirculation() const { return circulation; }
int IndependentPublication::getPageCount() const { return pageCount; }

ArticleCollection::ArticleCollection(const std::string& a, const std::string& t,
                                   const std::string& am, const std::string& in,
                                   const std::string& tc, const std::string& pub,
                                   int y, int circ, int pages)
    : IndependentPublication(a, t, am, in, tc, pub, y, circ, pages) {}

void ArticleCollection::addArticle(const Article& article) {
    articles.push_back(article);
}

std::vector<Article> ArticleCollection::getArticles() const {
    return articles;
}

Book::Book(const std::string& a, const std::string& t,
         const std::string& am, const std::string& in,
         const std::string& tc, const std::string& pub,
         int y, int circ, int pages)
    : IndependentPublication(a, t, am, in, tc, pub, y, circ, pages),
      article(a, t) {}

Article Book::getArticle() const {
    return article;
}

ArticleCard::ArticleCard(const std::string& a, const std::string& t,
                       const std::string& am, const std::string& in,
                       const std::string& tc, LibraryCard* pubCard)
    : LibraryCard(a, t, am, in, tc), article(a, t), publicationCard(pubCard) {}

Article ArticleCard::getArticle() const {
    return article;
}

LibraryCard* ArticleCard::getPublicationCard() const {
    return publicationCard;
}