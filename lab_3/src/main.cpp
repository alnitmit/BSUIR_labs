#include "../include/AlphabeticalCatalog.h"
#include "../include/ArticleCard.h"
#include "../include/BookCard.h"
#include "../include/CollectionOfArticlesCard.h"
#include "../include/ThematicCatalog.h"
#include <iostream>

void showMenu();
IndependentPublishingParams getPublicationParams(bool isCollection = false);
void createPublicationCard(BookCard *&book, CollectionOfArticlesCard *&collection, bool isBook);
void addArticleToCollection(CollectionOfArticlesCard *collection);
void createArticleCard(ArticleCard *&articleCard, BookCard *book,
                       CollectionOfArticlesCard *collection);
void addToCatalog(Catalog &catalog, BookCard *book, CollectionOfArticlesCard *collection, const std::string& catalogType);
void searchInCatalog(Catalog &catalog, const std::string& searchType);
void showBookInfo(const BookCard *book);
void showCollectionInfo(const CollectionOfArticlesCard *collection);
void cleanup(BookCard *&book, CollectionOfArticlesCard *&collection,
             ArticleCard *&articleCard);

void showMenu() {
  std::cout << "\n=== Library System ===\n"
            << "1. Create book card\n"
            << "2. Create collection of articles card\n"
            << "3. Add article to collection\n"
            << "4. Create article card\n"
            << "5. Add card to thematic catalog\n"
            << "6. Add card to alphabetical catalog\n"
            << "7. Search in thematic catalog\n"
            << "8. Search in alphabetical catalog\n"
            << "9. Show book information\n"
            << "10. Show collection information\n"
            << "11. Exit\n"
            << "Choice: ";
}

IndependentPublishingParams getPublicationParams(bool isCollection) {
  std::string author;
  std::string title;
  std::string authMark;
  std::string invNum;
  std::string catCode;
  std::string publisher;
  int year;
  int circulation;
  int pages;

  std::cout << (isCollection ? "Collection author: " : "Author: ");
  std::getline(std::cin, author);
  std::cout << (isCollection ? "Collection title: " : "Title: ");
  std::getline(std::cin, title);
  std::cout << "Author mark: ";
  std::getline(std::cin, authMark);
  std::cout << "Inventory number: ";
  std::getline(std::cin, invNum);
  std::cout << "Catalog code: ";
  std::getline(std::cin, catCode);
  std::cout << "Publisher: ";
  std::getline(std::cin, publisher);
  std::cout << "Year: ";
  std::cin >> year;
  std::cout << "Circulation: ";
  std::cin >> circulation;
  std::cout << "Pages: ";
  std::cin >> pages;
  std::cin.ignore();

  LibraryCardParams libraryParams(author, title, authMark, invNum, catCode);
  PublishingDetails pubDetails(publisher, year, circulation, pages);
  return IndependentPublishingParams(libraryParams, pubDetails);
}

void createPublicationCard(BookCard *&book, CollectionOfArticlesCard *&collection, bool isBook) {
  if (isBook && book) {
    delete book;
    book = nullptr;
  } else if (!isBook && collection) {
    delete collection;
    collection = nullptr;
  }

  IndependentPublishingParams params = getPublicationParams(!isBook);
  
  if (isBook) {
    book = new BookCard(params);
    std::cout << "Book card created!\n";
  } else {
    collection = new CollectionOfArticlesCard(params);
    std::cout << "Collection card created!\n";
  }
}

void addArticleToCollection(CollectionOfArticlesCard *collection) {
  if (!collection) {
    std::cout << "First create a collection card!\n";
    return;
  }

  std::string author;
  std::string title;

  std::cout << "Article author: ";
  std::getline(std::cin, author);
  std::cout << "Article title: ";
  std::getline(std::cin, title);

  collection->addArticle(new Article(title, author));
  std::cout << "Article added to collection!\n";
}

void createArticleCard(ArticleCard *&articleCard, BookCard *book,
                       CollectionOfArticlesCard *collection) {
  if (articleCard) {
    delete articleCard;
    articleCard = nullptr;
  }

  if (!book && !collection) {
    std::cout << "First create a book or collection!\n";
    return;
  }

  std::string author;
  std::string title;

  std::cout << "Article author: ";
  std::getline(std::cin, author);
  std::cout << "Article title: ";
  std::getline(std::cin, title);

  auto article = new Article(title, author);

  LibraryCard *publication = nullptr;
  int pubChoice;
  std::cout << "Select publication:\n";
  std::cout << "1. Book\n";
  std::cout << "2. Collection\n";
  std::cout << "Choice: ";
  std::cin >> pubChoice;
  std::cin.ignore();

  if (pubChoice == 1 && book) {
    publication = book;
  } else if (pubChoice == 2 && collection) {
    publication = collection;
  } else {
    std::cout << "Invalid choice or publication not available!\n";
    delete article;
    return;
  }

  articleCard = new ArticleCard(article, publication);
  std::cout << "Article card created!\n";
}

void addToCatalog(Catalog &catalog, BookCard *book, CollectionOfArticlesCard *collection, const std::string& catalogType) {
  LibraryCard *cardToAdd = nullptr;
  int cardChoice;
  std::cout << "Select card to add to " << catalogType << " catalog:\n";
  std::cout << "1. Book\n";
  std::cout << "2. Collection\n";
  std::cout << "Choice: ";
  std::cin >> cardChoice;
  std::cin.ignore();

  if (cardChoice == 1 && book) {
    cardToAdd = book;
  } else if (cardChoice == 2 && collection) {
    cardToAdd = collection;
  } else {
    std::cout << "Invalid choice or card not available!\n";
    return;
  }

  catalog.addCard(cardToAdd);
  std::cout << "Card added to " << catalogType << " catalog!\n";
}

void searchInCatalog(Catalog &catalog, const std::string& searchType) {
  std::string query;
  int resultCount;
  LibraryCard **results;

  if (searchType == "thematic") {
    std::cout << "Enter thematic catalog code: ";
    std::getline(std::cin, query);
  } else {
    std::cout << "Enter search query (author or title): ";
    std::getline(std::cin, query);
  }

  results = catalog.search(query, resultCount);

  std::cout << "Found " << resultCount << " results:\n";
  for (int i = 0; i < resultCount; ++i) {
    std::cout << i + 1 << ". " << results[i]->getAlphabeticalSearch() << std::endl;
  }

  delete[] results;
}

void showBookInfo(const BookCard *book) {
  if (book) {
    std::cout << "\n=== Book Information ===\n"
              << "Alphabetical search: " << book->getAlphabeticalSearch() << "\n"
              << "Author mark: " << book->getAuthorMark() << "\n"
              << "Inventory number: " << book->getInventoryNumber() << "\n"
              << "Publisher: " << book->getPublisher() << "\n"
              << "Year: " << book->getYear() << "\n"
              << "Article: " << book->getArticle()->getAuthor() << " - "
              << book->getArticle()->getTitle() << std::endl;
  } else {
    std::cout << "First create a book card!\n";
  }
}

void showCollectionInfo(const CollectionOfArticlesCard *collection) {
  if (collection) {
    std::cout << "\n=== Collection Information ===\n"
              << "Alphabetical search: " << collection->getAlphabeticalSearch() << "\n"
              << "Author mark: " << collection->getAuthorMark() << "\n"
              << "Inventory number: " << collection->getInventoryNumber() << "\n"
              << "Publisher: " << collection->getPublisher() << "\n"
              << "Year: " << collection->getYear() << "\n"
              << "Articles count: " << collection->getArticleCount() << std::endl;

    for (int i = 0; i < collection->getArticleCount(); ++i) {
      const Article *article = collection->getArticle(i);
      if (article) {
        std::cout << "  Article " << (i + 1) << ": " << article->getAuthor()
                  << " - " << article->getTitle() << std::endl;
      }
    }
  } else {
    std::cout << "First create a collection card!\n";
  }
}

void cleanup(BookCard *&book, CollectionOfArticlesCard *&collection,
             ArticleCard *&articleCard) {
  delete book;
  delete collection;
  delete articleCard;
  book = nullptr;
  collection = nullptr;
  articleCard = nullptr;
}

int main() {
  BookCard *book = nullptr;
  CollectionOfArticlesCard *collection = nullptr;
  ArticleCard *articleCard = nullptr;
  ThematicCatalog thematicCatalog;
  AlphabeticalCatalog alphabeticalCatalog;

  int choice;

  while (true) {
    showMenu();
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1:
      createPublicationCard(book, collection, true);
      break;
    case 2:
      createPublicationCard(book, collection, false);
      break;
    case 3:
      addArticleToCollection(collection);
      break;
    case 4:
      createArticleCard(articleCard, book, collection);
      break;
    case 5:
      addToCatalog(thematicCatalog, book, collection, "thematic");
      break;
    case 6:
      addToCatalog(alphabeticalCatalog, book, collection, "alphabetical");
      break;
    case 7:
      searchInCatalog(thematicCatalog, "thematic");
      break;
    case 8:
      searchInCatalog(alphabeticalCatalog, "alphabetical");
      break;
    case 9:
      showBookInfo(book);
      break;
    case 10:
      showCollectionInfo(collection);
      break;
    case 11:
      cleanup(book, collection, articleCard);
      std::cout << "Goodbye!\n";
      return 0;
    default:
      std::cout << "Invalid choice!\n";
    }
  }
}