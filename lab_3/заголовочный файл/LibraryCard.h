#ifndef LIBRARYCARD_H
#define LIBRARYCARD_H

#include "Article.h"
#include <string>
#include <vector>

class LibraryCard {
protected:
    std::string author;
    std::string title;
    std::string authorMark;
    std::string inventoryNumber;
    std::string thematicCode;
public:
    LibraryCard(const std::string& a, const std::string& t, 
                const std::string& am, const std::string& in, 
                const std::string& tc);
    virtual ~LibraryCard() = default;
    std::string getAuthor() const;
    std::string getTitle() const;
    std::string getAuthorMark() const;
    std::string getInventoryNumber() const;
    std::string getThematicCode() const;
    virtual std::string getAlphabeticalIndex() const;
};

class IndependentPublication : public LibraryCard {
protected:
    std::string publisher;
    int year;
    int circulation;
    int pageCount;
public:
    IndependentPublication(const std::string& a, const std::string& t,
                          const std::string& am, const std::string& in,
                          const std::string& tc, const std::string& pub,
                          int y, int circ, int pages);
    std::string getPublisher() const;
    int getYear() const;
    int getCirculation() const;
    int getPageCount() const;
};

class ArticleCollection : public IndependentPublication {
private:
    std::vector<Article> articles;
public:
    ArticleCollection(const std::string& a, const std::string& t,
                     const std::string& am, const std::string& in,
                     const std::string& tc, const std::string& pub,
                     int y, int circ, int pages);
    void addArticle(const Article& article);
    std::vector<Article> getArticles() const;
};

class Book : public IndependentPublication {
private:
    Article article;
public:
    Book(const std::string& a, const std::string& t,
         const std::string& am, const std::string& in,
         const std::string& tc, const std::string& pub,
         int y, int circ, int pages);
    Article getArticle() const;
};

class ArticleCard : public LibraryCard {
private:
    Article article;
    LibraryCard* publicationCard;
public:
    ArticleCard(const std::string& a, const std::string& t,
               const std::string& am, const std::string& in,
               const std::string& tc, LibraryCard* pubCard);
    Article getArticle() const;
    LibraryCard* getPublicationCard() const;
};

#endif