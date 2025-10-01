#include "../include/AlphabeticalCatalog.h"
#include "../include/ArticleCard.h"
#include "../include/BookCard.h"
#include "../include/CollectionOfArticlesCard.h"
#include "../include/ThematicCatalog.h"
#include <iostream>
#include <string_view>

void showMenu();
IndependentPublishingParams getPublicationParams(bool isCollection = false);
LibraryCardParams getArticleCardParams();
void createPublicationCard(BookCard *&book, CollectionOfArticlesCard *&collection, bool isBook);
void addArticleToCollection(CollectionOfArticlesCard *collection);
void createArticleCard(ArticleCard *&articleCard);
void addToCatalog(Catalog &catalog, BookCard *book, CollectionOfArticlesCard *collection, 
                  ArticleCard *articleCard, std::string_view catalogType);
void searchInCatalog(Catalog &catalog, std::string_view searchType);
void showBookInfo(const BookCard *book);
void showCollectionInfo(const CollectionOfArticlesCard *collection);
void showArticleInfo(const ArticleCard *articleCard);
void cleanup(BookCard *&book, CollectionOfArticlesCard *&collection, ArticleCard *&articleCard);

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
            << "11. Show article information\n"
            << "12. Exit\n"
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

LibraryCardParams getArticleCardParams() {
  std::string author;
  std::string title;
  std::string authMark;
  std::string invNum;
  std::string catCode;

  std::cout << "Article author: ";
  std::getline(std::cin, author);
  std::cout << "Article title: ";
  std::getline(std::cin, title);
  std::cout << "Author mark for article: ";
  std::getline(std::cin, authMark);
  std::cout << "Inventory number for article: ";
  std::getline(std::cin, invNum);
  std::cout << "Catalog code for article: ";
  std::getline(std::cin, catCode);

  return LibraryCardParams(author, title, authMark, invNum, catCode);
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

void createArticleCard(ArticleCard *&articleCard) {
  if (articleCard) {
    delete articleCard;
    articleCard = nullptr;
  }

  LibraryCardParams params = getArticleCardParams();

  auto article = new Article(params.title, params.author);

  articleCard = new ArticleCard(params, article);
  std::cout << "Article card created!\n";
}

void addToCatalog(Catalog &catalog, BookCard *book, CollectionOfArticlesCard *collection, 
                  ArticleCard *articleCard, std::string_view catalogType) {
  LibraryCard *cardToAdd = nullptr;
  int cardChoice;
  std::cout << "Select card to add to " << catalogType << " catalog:\n";
  std::cout << "1. Book\n";
  std::cout << "2. Collection\n";
  std::cout << "3. Article Card\n";
  std::cout << "Choice: ";
  std::cin >> cardChoice;
  std::cin.ignore();

  if (cardChoice == 1 && book) {
    cardToAdd = book;
  } else if (cardChoice == 2 && collection) {
    cardToAdd = collection;
  } else if (cardChoice == 3 && articleCard) {
    cardToAdd = articleCard;
  } else {
    std::cout << "Invalid choice or card not available!\n";
    return;
  }

  catalog.addCard(cardToAdd);
  std::cout << "Card added to " << catalogType << " catalog!\n";
}

void searchInCatalog(Catalog &catalog, std::string_view searchType) {
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
              << "Circulation: " << book->getCirculation() << "\n"
              << "Pages: " << book->getPages() << "\n"
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
              << "Circulation: " << collection->getCirculation() << "\n"
              << "Pages: " << collection->getPages() << "\n"
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

void showArticleInfo(const ArticleCard *articleCard) {
  if (articleCard) {
    std::cout << "\n=== Article Card Information ===\n"
              << "Alphabetical search: " << articleCard->getAlphabeticalSearch() << "\n"
              << "Author mark: " << articleCard->getAuthorMark() << "\n"
              << "Inventory number: " << articleCard->getInventoryNumber() << "\n"
              << "Thematic catalog code: " << articleCard->getThematicCatalogCode() << "\n"
              << "Article: " << articleCard->getArticle()->getAuthor() << " - "
              << articleCard->getArticle()->getTitle() << std::endl;
  } else {
    std::cout << "First create an article card!\n";
  }
}

void cleanup(BookCard *&book, CollectionOfArticlesCard *&collection, ArticleCard *&articleCard) {
  delete book;
  delete collection;
  delete articleCard;
  book = nullptr;
  collection = nullptr;
  articleCard = nullptr;
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
      createArticleCard(articleCard);
      break;
    case 5:
      addToCatalog(thematicCatalog, book, collection, articleCard, "thematic");
      break;
    case 6:
      addToCatalog(alphabeticalCatalog, book, collection, articleCard, "alphabetical");
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
      showArticleInfo(articleCard);
      break;
    case 12:
      cleanup(book, collection, articleCard);
      std::cout << "Goodbye!\n";
      return 0;
    default:
      std::cout << "Invalid choice!\n";
    }
  }
}