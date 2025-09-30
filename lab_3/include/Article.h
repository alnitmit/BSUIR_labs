#pragma once
#include <string>
#include <string_view>

class Article {
private:
    std::string title;
    std::string author;

public:
    explicit Article(const std::string& t, const std::string& a);
    
    // Правило пяти с = default
    ~Article() = default;
    Article(const Article& other) = default;
    Article& operator=(const Article& other) = default;
    Article(Article&& other) = default;
    Article& operator=(Article&& other) = default;

    std::string getTitle() const;
    std::string getAuthor() const;
    
    // Сеттеры с std::string_view
    void setTitle(std::string_view t);
    void setAuthor(std::string_view a);
};