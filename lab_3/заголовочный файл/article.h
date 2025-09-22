#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
private:
    std::string title;
    std::string author;
public:
    Article(const std::string& t, const std::string& a);
    std::string getTitle() const;
    std::string getAuthor() const;
};

#endif