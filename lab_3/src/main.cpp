#include "../include/AlphabeticalCatalog.h"
#include "../include/ArticleCard.h"
#include "../include/BookCard.h"
#include "../include/CollectionOfArticlesCard.h"
#include "../include/ThematicCatalog.h"
#include <iostream>

// Прототипы функций
void showMenu();
IndependentPublishingParams getPublicationParams(bool isCollection = false);
void createBookCard(BookCard *&book);
void createCollectionCard(CollectionOfArticlesCard *&collection);
void addArticleToCollection(CollectionOfArticlesCard *collection);
void createArticleCard(ArticleCard *&articleCard, BookCard *book,
                       CollectionOfArticlesCard *collection);
void addToCatalog(ThematicCatalog &thematicCatalog, AlphabeticalCatalog &alphabeticalCatalog, 
                  BookCard *book, CollectionOfArticlesCard *collection, bool isThematic);
void searchCatalog(ThematicCatalog &thematicCatalog, AlphabeticalCatalog &alphabeticalCatalog, bool isThematic);
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

// Общая функция для получения параметров публикации
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

// Общая функция для создания карточки
template<typename T>
void createPublicationCard(T*& publication) {
  if (publication) {
    delete publication;
    publication = nullptr;
  }

  bool isCollection = (typeid(T) == typeid(CollectionOfArticlesCard*));
  IndependentPublishingParams params = getPublicationParams(isCollection);
  publication = new T(params);
  
  std::cout << (isCollection ? "Collection card created!\n" : "Book card created!\n");
}

void createBookCard(BookCard *&book) {
  createPublicationCard(book);
}

void createCollectionCard(CollectionOfArticlesCard *&collection) {
  createPublicationCard(collection);
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

// Общая функция для добавления в каталог
void addToCatalog(ThematicCatalog &thematicCatalog, AlphabeticalCatalog &alphabeticalCatalog, 
                  BookCard *book, CollectionOfArticlesCard *collection, bool isThematic) {
  LibraryCard *cardToAdd = nullptr;
  int cardChoice;
  std::cout << "Select card to add:\n";
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

  if (isThematic) {
    thematicCatalog.addCard(cardToAdd);
    std::cout << "Card added to thematic catalog!\n";
  } else {
    alphabeticalCatalog.addCard(cardToAdd);
    std::cout << "Card added to alphabetical catalog!\n";
  }
}

void addToThematicCatalog(ThematicCatalog &catalog, BookCard *book,
                          CollectionOfArticlesCard *collection) {
  // Создаем временный alphabeticalCatalog, так как он не используется в этой функции
  AlphabeticalCatalog tempCatalog;
  addToCatalog(catalog, tempCatalog, book, collection, true);
}

void addToAlphabeticalCatalog(AlphabeticalCatalog &catalog, BookCard *book,
                              CollectionOfArticlesCard *collection) {
  // Создаем временный thematicCatalog, так как он не используется в этой функции
  ThematicCatalog tempCatalog;
  addToCatalog(tempCatalog, catalog, book, collection, false);
}

// Общая функция для поиска в каталоге
void searchCatalog(ThematicCatalog &thematicCatalog, AlphabeticalCatalog &alphabeticalCatalog, bool isThematic) {
  std::string query;
  int resultCount;
  LibraryCard **results;

  if (isThematic) {
    std::cout << "Enter thematic catalog code: ";
    std::getline(std::cin, query);
    results = thematicCatalog.search(query, resultCount);
  } else {
    std::cout << "Enter search query (author or title): ";
    std::getline(std::cin, query);
    results = alphabeticalCatalog.search(query, resultCount);
  }

  std::cout << "Found " << resultCount << " results:\n";
  for (int i = 0; i < resultCount; ++i) {
    std::cout << i + 1 << ". " << results[i]->getAlphabeticalSearch() << std::endl;
  }

  delete[] results;
}

void searchThematicCatalog(ThematicCatalog &catalog) {
  AlphabeticalCatalog tempCatalog;
  searchCatalog(catalog, tempCatalog, true);
}

void searchAlphabeticalCatalog(AlphabeticalCatalog &catalog) {
  ThematicCatalog tempCatalog;
  searchCatalog(tempCatalog, catalog, false);
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
      createBookCard(book);
      break;
    case 2:
      createCollectionCard(collection);
      break;
    case 3:
      addArticleToCollection(collection);
      break;
    case 4:
      createArticleCard(articleCard, book, collection);
      break;
    case 5:
      addToThematicCatalog(thematicCatalog, book, collection);
      break;
    case 6:
      addToAlphabeticalCatalog(alphabeticalCatalog, book, collection);
      break;
    case 7:
      searchThematicCatalog(thematicCatalog);
      break;
    case 8:
      searchAlphabeticalCatalog(alphabeticalCatalog);
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