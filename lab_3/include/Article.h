#pragma once
#include <string>
#include <string_view>

class Article {
private:
    std::string title;
    std::string author;

public:
    explicit Article(const std::string& t, const std::string& a);
    
    std::string getTitle() const;
    std::string getAuthor() const;
    
    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
};