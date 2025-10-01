#include "../include/AlphabeticalCatalog.h"
#include <algorithm>
#include <cctype>

LibraryCard** AlphabeticalCatalog::search(const std::string& query, int& resultCount) {
    auto results = new LibraryCard*[getCount()];
    resultCount = 0;

    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (int i = 0; i < getCount(); ++i) {
        LibraryCard* card = getCard(i);
        if (card) {
            std::string author = card->getAuthor();
            std::string title = card->getTitle();
            
            std::transform(author.begin(), author.end(), author.begin(), ::tolower);
            std::transform(title.begin(), title.end(), title.begin(), ::tolower);

            if (author.find(lowerQuery) != std::string::npos ||
                title.find(lowerQuery) != std::string::npos) {
                results[resultCount++] = card;
            }
        }
    }

    return results;
}