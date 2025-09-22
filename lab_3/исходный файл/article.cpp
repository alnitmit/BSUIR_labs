#include "../заголовочный файл/Article.h"

Article::Article(const std::string& t, const std::string& a) 
    : title(t), author(a) {}

std::string Article::getTitle() const { return title; }
std::string Article::getAuthor() const { return author; }