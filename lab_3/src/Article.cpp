#include "../include/Article.h"
#include <utility> // для std::swap

// Конструктор
Article::Article(const std::string& t, const std::string& a)
    : title(t), author(a) {}

// Деструктор
Article::~Article() {
    title.clear();
    author.clear();
}

// Конструктор копирования
Article::Article(const Article& other)
    : title(other.title), author(other.author) {}

// Оператор присваивания копированием
Article& Article::operator=(const Article& other) {
    if (this != &other) {
        // Используем идиому copy-and-swap
        Article temp(other);
        swap(temp);
    }
    return *this;
}

// Конструктор перемещения
Article::Article(Article&& other) noexcept
    : title(std::move(other.title)), author(std::move(other.author)) {
    // Приводим moved-from объект в валидное состояние
    other.title.clear();
    other.author.clear();
}

// Оператор присваивания перемещением
Article& Article::operator=(Article&& other) noexcept {
    if (this != &other) {
        // Освобождаем текущие ресурсы
        title.clear();
        author.clear();
        
        // Перемещаем ресурсы из other
        title = std::move(other.title);
        author = std::move(other.author);
        
        // Приводим other в валидное состояние
        other.title.clear();
        other.author.clear();
    }
    return *this;
}

// Метод обмена
void Article::swap(Article& other) noexcept {
    using std::swap;
    swap(title, other.title);
    swap(author, other.author);
}

// Геттеры
std::string Article::getTitle() const { 
    return title; 
}

std::string Article::getAuthor() const { 
    return author; 
}

// Сеттеры
void Article::setTitle(const std::string& t) { 
    title = t; 
}

void Article::setAuthor(const std::string& a) { 
    author = a; 
}