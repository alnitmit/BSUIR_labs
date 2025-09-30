#pragma once
#include <string>

class Article {
private:
    std::string title;
    std::string author;

public:
    // Конструктор
    Article(const std::string& t, const std::string& a);
    
    // Правило пяти: деструктор, копирование, перемещение
    ~Article();
    
    // Конструктор копирования
    Article(const Article& other);
    
    // Оператор присваивания копированием
    Article& operator=(const Article& other);
    
    // Конструктор перемещения
    Article(Article&& other) noexcept;
    
    // Оператор присваивания перемещением
    Article& operator=(Article&& other) noexcept;
    
    // Геттеры
    std::string getTitle() const;
    std::string getAuthor() const;
    
    // Сеттеры
    void setTitle(const std::string& t);
    void setAuthor(const std::string& a);
    
    // Метод обмена
    void swap(Article& other) noexcept;
};