#include <iostream>
#include "../заголовочный файл/Article.h"
#include "../заголовочный файл/LibraryCard.h"
#include "../заголовочный файл/Catalog.h"

using namespace std;

void displayMenu() {
    cout << "1. Add Book\n"
         << "2. Add Article Collection\n"
         << "3. Add Article Card\n"
         << "4. Search in Thematic Catalog\n"
         << "5. Search in Alphabetical Catalog\n"
         << "6. Exit\n"
         << "Choose option: ";
}

int main() {
    ThematicCatalog thematicCatalog;
    AlphabeticalCatalog alphabeticalCatalog;
    vector<LibraryCard*> allCards;

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string author, title, authorMark, invNum, thematicCode, publisher;
                int year, circulation, pages;
                
                cout << "Enter author: "; getline(cin, author);
                cout << "Enter title: "; getline(cin, title);
                cout << "Enter author mark: "; getline(cin, authorMark);
                cout << "Enter inventory number: "; getline(cin, invNum);
                cout << "Enter thematic code: "; getline(cin, thematicCode);
                cout << "Enter publisher: "; getline(cin, publisher);
                cout << "Enter year: "; cin >> year;
                cout << "Enter circulation: "; cin >> circulation;
                cout << "Enter page count: "; cin >> pages;
                
                Book* book = new Book(author, title, authorMark, invNum, 
                                    thematicCode, publisher, year, circulation, pages);
                thematicCatalog.addCard(book);
                alphabeticalCatalog.addCard(book);
                allCards.push_back(book);
                break;
            }
            case 2: {
                string author, title, authorMark, invNum, thematicCode, publisher;
                int year, circulation, pages;
                
                cout << "Enter author: "; getline(cin, author);
                cout << "Enter title: "; getline(cin, title);
                cout << "Enter author mark: "; getline(cin, authorMark);
                cout << "Enter inventory number: "; getline(cin, invNum);
                cout << "Enter thematic code: "; getline(cin, thematicCode);
                cout << "Enter publisher: "; getline(cin, publisher);
                cout << "Enter year: "; cin >> year;
                cout << "Enter circulation: "; cin >> circulation;
                cout << "Enter page count: "; cin >> pages;
                
                ArticleCollection* collection = new ArticleCollection(
                    author, title, authorMark, invNum, 
                    thematicCode, publisher, year, circulation, pages
                );
                
                int articleCount;
                cout << "Enter number of articles: "; cin >> articleCount;
                cin.ignore();
                for (int i = 0; i < articleCount; i++) {
                    string artTitle, artAuthor;
                    cout << "Article " << i+1 << " title: "; getline(cin, artTitle);
                    cout << "Article " << i+1 << " author: "; getline(cin, artAuthor);
                    collection->addArticle(Article(artTitle, artAuthor));
                }
                
                thematicCatalog.addCard(collection);
                alphabeticalCatalog.addCard(collection);
                allCards.push_back(collection);
                break;
            }
            case 3: {
                string author, title, authorMark, invNum, thematicCode;
                cout << "Enter author: "; getline(cin, author);
                cout << "Enter title: "; getline(cin, title);
                cout << "Enter author mark: "; getline(cin, authorMark);
                cout << "Enter inventory number: "; getline(cin, invNum);
                cout << "Enter thematic code: "; getline(cin, thematicCode);
                
                LibraryCard* pubCard = allCards.empty() ? nullptr : allCards[0];
                ArticleCard* articleCard = new ArticleCard(
                    author, title, authorMark, invNum, thematicCode, pubCard
                );
                
                thematicCatalog.addCard(articleCard);
                alphabeticalCatalog.addCard(articleCard);
                allCards.push_back(articleCard);
                break;
            }
            case 4: {
                string code;
                cout << "Enter thematic code: "; getline(cin, code);
                LibraryCard* result = thematicCatalog.search(code);
                if (result) {
                    cout << "Found: " << result->getTitle() << endl;
                } else {
                    cout << "Not found!" << endl;
                }
                break;
            }
            case 5: {
                string query;
                cout << "Enter author or title: "; getline(cin, query);
                LibraryCard* result = alphabeticalCatalog.search(query);
                if (result) {
                    cout << "Found: " << result->getAlphabeticalIndex() << endl;
                } else {
                    cout << "Not found!" << endl;
                }
                break;
            }
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 6);

    for (auto card : allCards) delete card;
    return 0;
}