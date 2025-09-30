#pragma once
#include <string>

class Article {
private:
    std::string title;
    std::string author;

public:
    Article(const std::string& t, const std::string& a);
    ~Article();

    std::string getTitle() const;
    std::string getAuthor() const;
    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
};