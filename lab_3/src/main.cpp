#include "../include/AlphabeticalCatalog.h"
#include "../include/ArticleCard.h"
#include "../include/BookCard.h"
#include "../include/CollectionOfArticlesCard.h"
#include "../include/IndependentPublishingCard.h"
#include "../include/LibraryCard.h"
#include "../include/ThematicCatalog.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int inputInt(const string &prompt, int min = 0, int max = 1000000) {
  int value;
  while (true) {
    cout << prompt;
    cin >> value;
    if (cin.fail() || value < min || value > max) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error! Please enter an integer from " << min << " to " << max
           << endl;
    } else {
      cin.ignore();
      return value;
    }
  }
}

string inputString(const string &prompt) {
  string value;
  cout << prompt;
  getline(cin, value);
  while (value.empty()) {
    cout << "Error! Field cannot be empty. " << prompt;
    getline(cin, value);
  }
  return value;
}

PublishingDetails inputPublishingDetails() {
  cout << "\n\tPUBLISHING DETAILS" << endl;
  string publisher = inputString("Enter publisher: ");
  int year = inputInt("Enter publication year: ", 1000, 2100);
  int circulation = inputInt("Enter circulation: ", 1);
  int pages = inputInt("Enter number of pages: ", 1);

  return PublishingDetails(publisher, year, circulation, pages);
}

void createBookCard(ThematicCatalog &thematicCatalog,
                    AlphabeticalCatalog &alphabeticalCatalog) {
  cout << "\n\t CREATE BOOK CARD" << endl;

  string author = inputString("Enter book author: ");
  string title = inputString("Enter book title: ");
  string authorMark = inputString("Enter author mark: ");
  string inventoryNumber = inputString("Enter inventory number: ");
  string catalogCode = inputString("Enter thematic catalog code: ");

  PublishingDetails pubDetails = inputPublishingDetails();

  BookCard *book = new BookCard(author, title, authorMark, inventoryNumber,
                                catalogCode, pubDetails);

  thematicCatalog.addCard(book);
  alphabeticalCatalog.addCard(book);

  cout << "Book card created and added to catalogs!" << endl;
  cout << "Author: " << book->getAuthor() << endl;
  cout << "Title: " << book->getTitle() << endl;
  cout << "Publisher: " << book->getPublisher() << endl;
}

void createCollectionCard(ThematicCatalog &thematicCatalog,
                          AlphabeticalCatalog &alphabeticalCatalog) {
  cout << "\n\tCREATE COLLECTION CARD" << endl;

  string author = inputString("Enter collection author/editor: ");
  string title = inputString("Enter collection title: ");
  string authorMark = inputString("Enter author mark: ");
  string inventoryNumber = inputString("Enter inventory number: ");
  string catalogCode = inputString("Enter thematic catalog code: ");

  PublishingDetails pubDetails = inputPublishingDetails();

  CollectionOfArticlesCard *collection = new CollectionOfArticlesCard(
      author, title, authorMark, inventoryNumber, catalogCode, pubDetails);

  cout << "\n\tADD ARTICLES TO COLLECTION" << endl;
  char addMore;
  do {
    string articleAuthor = inputString("Enter article author: ");
    string articleTitle = inputString("Enter article title: ");

    collection->addArticle(articleTitle, articleAuthor);
    cout << "Article added to collection!" << endl;

    cout << "Add another article? (y/n): ";
    cin >> addMore;
    cin.ignore();
  } while (addMore == 'y' || addMore == 'Y');

  thematicCatalog.addCard(collection);
  alphabeticalCatalog.addCard(collection);

  cout << "Collection card created and added to catalogs!" << endl;
  cout << "Articles in collection: " << collection->getArticleCount() << endl;
}

void searchInThematicCatalog(ThematicCatalog &catalog) {
  cout << "\n\tSEARCH IN THEMATIC CATALOG" << endl;

  if (catalog.getCount() == 0) {
    cout << "Catalog is empty! Please add cards first." << endl;
    return;
  }

  string code = inputString("Enter thematic catalog code to search: ");

  int resultCount;
  LibraryCard **results = catalog.search(code, resultCount);

  if (resultCount == 0) {
    cout << "No results found for code '" << code << "'" << endl;
  } else {
    cout << "Found " << resultCount << " results:" << endl;
    for (int i = 0; i < resultCount; ++i) {
      cout << "  " << (i + 1) << ". " << results[i]->getAuthor() << " - "
           << results[i]->getTitle() << endl;
    }
  }

  delete[] results;
}

void searchInAlphabeticalCatalog(AlphabeticalCatalog &catalog) {
  cout << "\n\tSEARCH IN ALPHABETICAL CATALOG" << endl;

  if (catalog.getCount() == 0) {
    cout << "Catalog is empty! Please add cards first." << endl;
    return;
  }

  string query = inputString("Enter author or title to search: ");

  int resultCount;
  LibraryCard **results = catalog.search(query, resultCount);

  if (resultCount == 0) {
    cout << "No results found for '" << query << "'" << endl;
  } else {
    cout << "Found " << resultCount << " results:" << endl;
    for (int i = 0; i < resultCount; ++i) {
      cout << "  " << (i + 1) << ". " << results[i]->getAuthor() << " - "
           << results[i]->getTitle() << endl;
    }
  }

  delete[] results;
}

void showCatalogInfo(Catalog &catalog, const string &catalogType) {
  cout << "\n\t" << catalogType << " CATALOG INFO" << endl;
  cout << "Number of cards: " << catalog.getCount() << endl;

  if (catalog.getCount() > 0) {
    cout << "Catalog contents:" << endl;
    for (int i = 0; i < catalog.getCount(); ++i) {
      LibraryCard *card = catalog.getCard(i);
      cout << "  " << (i + 1) << ". " << card->getAuthor() << " - "
           << card->getTitle() << endl;
    }
  }
}

void showMenu() {
  cout << "\n=== LIBRARY SYSTEM ===" << endl;
  cout << "1. Create book card and add to catalogs" << endl;
  cout << "2. Create collection card and add to catalogs" << endl;
  cout << "3. Search in thematic catalog" << endl;
  cout << "4. Search in alphabetical catalog" << endl;
  cout << "5. Show thematic catalog info" << endl;
  cout << "6. Show alphabetical catalog info" << endl;
  cout << "7. Exit" << endl;
  cout << "Enter your choice: ";
}

int main() {
  ThematicCatalog thematicCatalog;
  AlphabeticalCatalog alphabeticalCatalog;

  cout << "Welcome to Library System!" << endl;

  int choice;
  bool running = true;

  while (running) {
    showMenu();
    choice = inputInt("", 1, 7);

    switch (choice) {
    case 1: {
      createBookCard(thematicCatalog, alphabeticalCatalog);
      break;
    }
    case 2: {
      createCollectionCard(thematicCatalog, alphabeticalCatalog);
      break;
    }
    case 3: {
      searchInThematicCatalog(thematicCatalog);
      break;
    }
    case 4: {
      searchInAlphabeticalCatalog(alphabeticalCatalog);
      break;
    }
    case 5: {
      showCatalogInfo(thematicCatalog, "THEMATIC");
      break;
    }
    case 6: {
      showCatalogInfo(alphabeticalCatalog, "ALPHABETICAL");
      break;
    }
    case 7: {
      running = false;
      break;
    }
    }
  }

  return 0;
}