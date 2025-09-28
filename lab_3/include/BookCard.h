#pragma once
#include "../include/IndependentPublishingCard.h"
#include "../include/Article.h"

class BookCard : public IndependentPublishingCard {
private:
    Article* article;
public:
    BookCard(const std::string& a, const std::string& t,
             const std::string& am, const std::string& in,
             const std::string& tcc, const std::string& p,
             int y, int c, int pg);
    
    BookCard(const BookCard&) = delete;
    BookCard& operator=(const BookCard&) = delete;
    
    BookCard(BookCard&& other) noexcept;
    BookCard& operator=(BookCard&& other) noexcept;
    
    ~BookCard() override;
    
    Article* getArticle() const;
};