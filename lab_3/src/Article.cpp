#include "../include/Article.h"

Article::Article(const std::string& t, const std::string& a)
    : title(t), author(a) {}

Article::~Article() {
    title.clear();
    author.clear();
}

std::string Article::getTitle() const { 
    return title; 
}

std::string Article::getAuthor() const { 
    return author; 
}

void Article::setTitle(const std::string& t) { 
    title = t; 
}

void Article::setAuthor(const std::string& a) { 
    author = a; 
}