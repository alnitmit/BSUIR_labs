#include "../include/Article.h"

Article::Article(const std::string& t, const std::string& a)
    : title(t), author(a) {}

std::string Article::getTitle() const { 
    return title; 
}

std::string Article::getAuthor() const { 
    return author; 
}

void Article::setTitle(std::string_view t) { 
    title = t; 
}

void Article::setAuthor(std::string_view a) { 
    author = a; 
}