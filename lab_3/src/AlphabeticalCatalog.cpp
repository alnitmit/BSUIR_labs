#include "../include/AlphabeticalCatalog.h"
#include <algorithm>
#include <cstring>
#include <iostream>


LibraryCard **AlphabeticalCatalog::search(const std::string &query,
                                          int &resultCount) {
  auto results = new LibraryCard *[count];
  resultCount = 0;

  std::string lowerQuery = query;
  std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                 ::tolower);

  for (int i = 0; i < count; ++i) {
    if (cards[i]) {
      std::string author = cards[i]->getAuthor();
      std::string title = cards[i]->getTitle();

      std::transform(author.begin(), author.end(), author.begin(), ::tolower);
      std::transform(title.begin(), title.end(), title.begin(), ::tolower);

      if (author.find(lowerQuery) != std::string::npos ||
          title.find(lowerQuery) != std::string::npos) {
        results[resultCount++] = cards[i];
      }
    }
  }

  return results;
}