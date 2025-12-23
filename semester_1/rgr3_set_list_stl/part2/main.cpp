#include <iostream>
#include <set>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <limits>

struct Author {
    std::string surname;
    std::string name;
    std::string patronymic;
    
    bool operator<(const Author& other) const {
        if (surname != other.surname) return surname < other.surname;
        if (name != other.name) return name < other.name;
        return patronymic < other.patronymic;
    }
};

struct Book {
    int udc_code;
    std::set<Author> writers;
    std::string book_title;
    int publish_year;
    
    bool operator<(const Book& other) const {
        return book_title < other.book_title;
    }
};

class LibrarySystem {
private:
    std::set<Book> catalog;
    
    std::set<Book>::iterator findBook(const std::string& title) {
        return std::find_if(catalog.begin(), catalog.end(), 
            [&title](const Book& b) { return b.book_title == title; });
    }
    
    void validateBookExists(const std::string& title) const {
        auto exists = std::any_of(catalog.begin(), catalog.end(),
            [&title](const Book& b) { return b.book_title == title; });
        if (!exists) {
            throw std::runtime_error("Book not found: " + title);
        }
    }
    
    void validateAuthorInBook(const Book& book, const Author& writer) const {
        if (book.writers.find(writer) == book.writers.end()) {
            throw std::runtime_error("Author not found in book: " + writer.surname);
        }
    }
    
public:
    void addBook(const Book& new_book) {
        if (catalog.find(new_book) != catalog.end()) {
            throw std::runtime_error("Book already exists: " + new_book.book_title);
        }
        
        if (new_book.udc_code <= 0) {
            throw std::invalid_argument("Invalid UDC code");
        }
        
        if (new_book.publish_year < 0 || new_book.publish_year > 2025) {
            throw std::invalid_argument("Invalid publication year");
        }
        
        if (new_book.book_title.empty()) {
            throw std::invalid_argument("Book title cannot be empty");
        }
        
        catalog.insert(new_book);
    }
    
    void deleteBook(const std::string& title) {
        auto position = findBook(title);
        if (position == catalog.end()) {
            throw std::runtime_error("Cannot delete: book not found - " + title);
        }
        catalog.erase(position);
    }
    
    void searchByWriter(const Author& writer) {
        bool found = false;
        std::cout << "Books by " << writer.surname << " " << writer.name << ":\n";
        
        for (const auto& item : catalog) {
            if (item.writers.find(writer) != item.writers.end()) {
                std::cout << "- " << item.book_title << " (" << item.publish_year << ")\n";
                found = true;
            }
        }
        
        if (!found) {
            throw std::runtime_error("No books found for author: " + writer.surname);
        }
    }
    
    void addWriterToBook(const std::string& title, const Author& writer) {
        validateBookExists(title);
        
        auto position = findBook(title);
        if (position == catalog.end()) {
            throw std::runtime_error("Book not found: " + title);
        }
        
        Book modified = *position;
        
        if (modified.writers.find(writer) != modified.writers.end()) {
            throw std::runtime_error("Author already exists in book: " + writer.surname);
        }
        
        catalog.erase(position);
        modified.writers.insert(writer);
        catalog.insert(modified);
    }
    
    void removeWriterFromBook(const std::string& title, const Author& writer) {
        validateBookExists(title);
        
        auto position = findBook(title);
        if (position == catalog.end()) {
            throw std::runtime_error("Book not found: " + title);
        }
        
        Book modified = *position;
        validateAuthorInBook(modified, writer);
        
        if (modified.writers.size() <= 1) {
            throw std::runtime_error("Cannot remove last author from book");
        }
        
        catalog.erase(position);
        modified.writers.erase(writer);
        catalog.insert(modified);
    }
    
    void loadFromFile(const std::string& filename) {
        std::ifstream input_file(filename);
        if (!input_file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        int book_count;
        if (!(input_file >> book_count)) {
            throw std::runtime_error("Invalid file format: cannot read book count");
        }
        
        for (int i = 0; i < book_count; i++) {
            Book current_book;
            int writer_count;
            
            if (!(input_file >> current_book.udc_code >> current_book.book_title >> current_book.publish_year >> writer_count)) {
                throw std::runtime_error("Invalid book data format for book " + std::to_string(i + 1));
            }
            
            if (writer_count < 0) {
                throw std::runtime_error("Invalid author count for book " + std::to_string(i + 1));
            }
            
            current_book.writers.clear();
            
            for (int j = 0; j < writer_count; j++) {
                Author current_writer;
                if (!(input_file >> current_writer.surname >> current_writer.name >> current_writer.patronymic)) {
                    throw std::runtime_error("Invalid author data for book " + std::to_string(i + 1) + ", author " + std::to_string(j + 1));
                }
                current_book.writers.insert(current_writer);
            }
            
            catalog.insert(current_book);
        }
        
        input_file.close();
    }
    
    void showAllBooks() {
        if (catalog.empty()) {
            throw std::runtime_error("Library catalog is empty");
        }
        
        for (const auto& item : catalog) {
            std::cout << "Title: " << item.book_title << "\n";
            std::cout << "UDC: " << item.udc_code << "\n";
            std::cout << "Year: " << item.publish_year << "\n";
            std::cout << "Authors: ";
            
            if (item.writers.empty()) {
                std::cout << "No authors";
            } else {
                for (const auto& writer : item.writers) {
                    std::cout << writer.surname << " " << writer.name << " " << writer.patronymic << "; ";
                }
            }
            std::cout << "\n---\n";
        }
    }
    
    void clearCatalog() {
        catalog.clear();
    }
    
    size_t getBookCount() const {
        return catalog.size();
    }
};

Book inputBookData() {
    Book new_book;
    
    std::cout << "Enter book title: ";
    std::cin.ignore();
    std::getline(std::cin, new_book.book_title);
    
    std::cout << "Enter UDC code: ";
    std::cin >> new_book.udc_code;
    
    std::cout << "Enter publication year: ";
    std::cin >> new_book.publish_year;
    
    std::cout << "Enter number of authors: ";
    int author_count;
    std::cin >> author_count;
    
    new_book.writers.clear();
    for (int i = 0; i < author_count; i++) {
        Author author;
        std::cout << "Author " << i + 1 << " surname: ";
        std::cin >> author.surname;
        std::cout << "Author " << i + 1 << " name: ";
        std::cin >> author.name;
        std::cout << "Author " << i + 1 << " patronymic: ";
        std::cin >> author.patronymic;
        new_book.writers.insert(author);
    }
    
    return new_book;
}

Author inputAuthorData() {
    Author author;
    std::cout << "Enter author surname: ";
    std::cin >> author.surname;
    std::cout << "Enter author name: ";
    std::cin >> author.name;
    std::cout << "Enter author patronymic: ";
    std::cin >> author.patronymic;
    return author;
}

void displayMenu() {
    std::cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
    std::cout << "1. Add new book\n";
    std::cout << "2. Delete book\n";
    std::cout << "3. Add author to book\n";
    std::cout << "4. Remove author from book\n";
    std::cout << "5. Search books by author\n";
    std::cout << "6. Show all books\n";
    std::cout << "7. Load books from file\n";
    std::cout << "8. Clear catalog\n";
    std::cout << "9. Show book count\n";
    std::cout << "0. Exit\n";
    std::cout << "===============================================\n";
    std::cout << "Choises option: ";
}

void Menu() {
    LibrarySystem lib;
    int choice = 0;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    Book new_book = inputBookData();
                    lib.addBook(new_book);
                    std::cout << "Book add!\n";
                    break;
                }
                case 2: {
                    std::string title;
                    std::cout << "Enter book title delete: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    lib.deleteBook(title);
                    std::cout << "Book delete!\n";
                    break;
                }
                case 3: {
                    std::string title;
                    std::cout << "Enter book title: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    Author author = inputAuthorData();
                    lib.addWriterToBook(title, author);
                    std::cout << "Author add!\n";
                    break;
                }
                case 4: {
                    std::string title;
                    std::cout << "Enter book title: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    Author author = inputAuthorData();
                    lib.removeWriterFromBook(title, author);
                    std::cout << "Author remove!\n";
                    break;
                }
                case 5: {
                    Author author = inputAuthorData();
                    lib.searchByWriter(author);
                    break;
                }
                case 6: {
                    lib.showAllBooks();
                    break;
                }
                case 7: {
                    std::string filename;
                    std::cout << "Enter filename: ";
                    std::cin >> filename;
                    lib.loadFromFile(filename);
                    std::cout << "Books add success!\n";
                    break;
                }
                case 8: {
                    lib.clearCatalog();
                    std::cout << "Catalog clear!\n";
                    break;
                }
                case 9: {
                    std::cout << "All books in catalog: " << lib.getBookCount() << "\n";
                    break;
                }
                case 0: {
                    std::cout << "EXIT...\n";
                    break;
                }
                default: {
                    std::cout << "No this option! Try again.\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
    } while (choice != 0);
}

int main() {
    Menu();
    return 0;
}