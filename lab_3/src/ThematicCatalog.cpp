#include "../include/ThematicCatalog.h"
#include <iostream>

LibraryCard** ThematicCatalog::search(const std::string& code, int& resultCount) {
    // Временный массив для результатов
    LibraryCard** results = new LibraryCard*[count];
    resultCount = 0;
    
    for (int i = 0; i < count; ++i) {
        if (cards[i] && cards[i]->getThematicCatalogCode() == code) {
            results[resultCount++] = cards[i];
        }
    }
    
    return results;
}