#pragma once
#include "../include/LibraryCard.h"

class Catalog {
protected:
    LibraryCard** cards;          // Динамический массив указателей на карточки
    int count;                    // Текущее количество карточек
    int capacity;                 // Текущая вместимость массива
    
    void resize();                // Метод для расширения массива

public:
    Catalog();
    virtual ~Catalog();
    
    void addCard(LibraryCard* card);
    virtual LibraryCard** search(const std::string& query, int& resultCount) = 0;
    int getCount() const;
};