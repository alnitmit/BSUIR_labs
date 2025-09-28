#include <iostream>
#include "../include/BookCard.h"
#include "../include/CollectionOfArticlesCard.h"
#include "../include/ArticleCard.h"
#include "../include/ThematicCatalog.h"
#include "../include/AlphabeticalCatalog.h"

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

int main() {
    BookCard* book = nullptr;
    CollectionOfArticlesCard* collection = nullptr;
    ArticleCard* articleCard = nullptr;
    ThematicCatalog thematicCatalog;
    AlphabeticalCatalog alphabeticalCatalog;
    
    int choice;

    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                // Создание карточки книги (существующий код)
                if (book) {
                    delete book;
                    book = nullptr;
                }
                
                std::string author, title, authMark, invNum, catCode, publisher;
                int year, circulation, pages;

                std::cout << "Author: "; std::getline(std::cin, author);
                std::cout << "Title: "; std::getline(std::cin, title);
                std::cout << "Author mark: "; std::getline(std::cin, authMark);
                std::cout << "Inventory number: "; std::getline(std::cin, invNum);
                std::cout << "Catalog code: "; std::getline(std::cin, catCode);
                std::cout << "Publisher: "; std::getline(std::cin, publisher);
                std::cout << "Year: "; std::cin >> year;
                std::cout << "Circulation: "; std::cin >> circulation;
                std::cout << "Pages: "; std::cin >> pages;
                std::cin.ignore();

                book = new BookCard(author, title, authMark, invNum, 
                                   catCode, publisher, year, circulation, pages);
                std::cout << "Book card created!\n";
                break;
            }
            case 2: {
                // Создание карточки сборника (существующий код)
                if (collection) {
                    delete collection;
                    collection = nullptr;
                }
                
                std::string author, title, authMark, invNum, catCode, publisher;
                int year, circulation, pages;

                std::cout << "Collection author: "; std::getline(std::cin, author);
                std::cout << "Collection title: "; std::getline(std::cin, title);
                std::cout << "Author mark: "; std::getline(std::cin, authMark);
                std::cout << "Inventory number: "; std::getline(std::cin, invNum);
                std::cout << "Catalog code: "; std::getline(std::cin, catCode);
                std::cout << "Publisher: "; std::getline(std::cin, publisher);
                std::cout << "Year: "; std::cin >> year;
                std::cout << "Circulation: "; std::cin >> circulation;
                std::cout << "Pages: "; std::cin >> pages;
                std::cin.ignore();

                collection = new CollectionOfArticlesCard(author, title, authMark,
                                                         invNum, catCode, publisher,
                                                         year, circulation, pages);
                std::cout << "Collection card created!\n";
                break;
            }
            case 3: {
                // Добавление статьи в сборник (существующий код)
                if (!collection) {
                    std::cout << "First create a collection card!\n";
                    break;
                }
                
                std::string author, title;
                std::cout << "Article author: "; std::getline(std::cin, author);
                std::cout << "Article title: "; std::getline(std::cin, title);
                
                collection->addArticle(new Article(title, author));
                std::cout << "Article added to collection!\n";
                break;
            }
            case 4: {
                // Создание карточки статьи
                if (articleCard) {
                    delete articleCard;
                    articleCard = nullptr;
                }
                
                if (!book && !collection) {
                    std::cout << "First create a book or collection!\n";
                    break;
                }
                
                std::string author, title;
                std::cout << "Article author: "; std::getline(std::cin, author);
                std::cout << "Article title: "; std::getline(std::cin, title);
                
                Article* article = new Article(title, author);
                
                // Выбор публикации для статьи
                LibraryCard* publication = nullptr;
                int pubChoice;
                std::cout << "Select publication:\n";
                std::cout << "1. Book\n";
                std::cout << "2. Collection\n";
                std::cout << "Choice: "; std::cin >> pubChoice;
                std::cin.ignore();
                
                if (pubChoice == 1 && book) {
                    publication = book;
                } else if (pubChoice == 2 && collection) {
                    publication = collection;
                } else {
                    std::cout << "Invalid choice or publication not available!\n";
                    delete article;
                    break;
                }
                
                articleCard = new ArticleCard(article, publication);
                std::cout << "Article card created!\n";
                break;
            }
            case 5: {
                // Добавление карточки в тематический каталог
                LibraryCard* cardToAdd = nullptr;
                int cardChoice;
                std::cout << "Select card to add:\n";
                std::cout << "1. Book\n";
                std::cout << "2. Collection\n";
                std::cout << "Choice: "; std::cin >> cardChoice;
                std::cin.ignore();
                
                if (cardChoice == 1 && book) {
                    cardToAdd = book;
                } else if (cardChoice == 2 && collection) {
                    cardToAdd = collection;
                } else {
                    std::cout << "Invalid choice or card not available!\n";
                    break;
                }
                
                thematicCatalog.addCard(cardToAdd);
                std::cout << "Card added to thematic catalog!\n";
                break;
            }
            case 6: {
                // Добавление карточки в алфавитный каталог
                LibraryCard* cardToAdd = nullptr;
                int cardChoice;
                std::cout << "Select card to add:\n";
                std::cout << "1. Book\n";
                std::cout << "2. Collection\n";
                std::cout << "Choice: "; std::cin >> cardChoice;
                std::cin.ignore();
                
                if (cardChoice == 1 && book) {
                    cardToAdd = book;
                } else if (cardChoice == 2 && collection) {
                    cardToAdd = collection;
                } else {
                    std::cout << "Invalid choice or card not available!\n";
                    break;
                }
                
                alphabeticalCatalog.addCard(cardToAdd);
                std::cout << "Card added to alphabetical catalog!\n";
                break;
            }
            case 7: {
                // Поиск в тематическом каталоге
                std::string code;
                std::cout << "Enter thematic catalog code: "; 
                std::getline(std::cin, code);
                
                int resultCount;
                LibraryCard** results = thematicCatalog.search(code, resultCount);
                
                std::cout << "Found " << resultCount << " results:\n";
                for (int i = 0; i < resultCount; ++i) {
                    std::cout << i+1 << ". " << results[i]->getAlphabeticalSearch() << std::endl;
                }
                
                delete[] results;
                break;
            }
            case 8: {
                // Поиск в алфавитном каталоге
                std::string query;
                std::cout << "Enter search query (author or title): "; 
                std::getline(std::cin, query);
                
                int resultCount;
                LibraryCard** results = alphabeticalCatalog.search(query, resultCount);
                
                std::cout << "Found " << resultCount << " results:\n";
                for (int i = 0; i < resultCount; ++i) {
                    std::cout << i+1 << ". " << results[i]->getAlphabeticalSearch() << std::endl;
                }
                
                delete[] results;
                break;
            }
            case 9: {
                // Показать информацию о книге (существующий код)
                if (book) {
                    std::cout << "\n=== Book Information ===\n"
                              << "Alphabetical search: " << book->getAlphabeticalSearch() << "\n"
                              << "Author mark: " << book->getAuthorMark() << "\n"
                              << "Inventory number: " << book->getInventoryNumber() << "\n"
                              << "Publisher: " << book->getPublisher() << "\n"
                              << "Year: " << book->getYear() << "\n"
                              << "Article: " << book->getArticle()->getAuthor() 
                              << " - " << book->getArticle()->getTitle() << std::endl;
                } else {
                    std::cout << "First create a book card!\n";
                }
                break;
            }
            case 10: {
                // Показать информацию о сборнике (существующий код)
                if (collection) {
                    std::cout << "\n=== Collection Information ===\n"
                              << "Alphabetical search: " << collection->getAlphabeticalSearch() << "\n"
                              << "Author mark: " << collection->getAuthorMark() << "\n"
                              << "Inventory number: " << collection->getInventoryNumber() << "\n"
                              << "Publisher: " << collection->getPublisher() << "\n"
                              << "Year: " << collection->getYear() << "\n"
                              << "Articles count: " << collection->getArticleCount() << std::endl;
                    
                    for (int i = 0; i < collection->getArticleCount(); ++i) {
                        Article* article = collection->getArticle(i);
                        if (article) {
                            std::cout << "  Article " << (i + 1) << ": " 
                                      << article->getAuthor() << " - " 
                                      << article->getTitle() << std::endl;
                        }
                    }
                } else {
                    std::cout << "First create a collection card!\n";
                }
                break;
            }
            case 11:
                delete book;
                delete collection;
                delete articleCard;
                std::cout << "Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}