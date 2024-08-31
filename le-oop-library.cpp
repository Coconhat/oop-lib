#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Library {
public:
    Library() {
        loadBooks();
    }

    // function to add a book to the library
    void addBook(string title, string author, int year) {
        books.push_back({title, author, year});
        saveBooks(); // save data after addBook()
        system("cls");
        cout << "Book added successfully!" << endl;
    }
    

    //function to display books
    void displayBooks() {
        system("cls");
        cout << "Book List:" << endl;
        cout << setw(30) << left << "Title"
             << setw(20) << left << "Author"
             << setw(5) << left << "Year" << endl;
        cout << "-----------------------------------------------------" << endl;
        for (Book book : books) {
            cout << setw(30) << left << book.title
                 << setw(20) << left << book.author
                 << setw(5) << left << book.year << endl;
        }
    }

    //function to search book by title
    void searchBook(string title) {
        bool found = false;
        for (Book book : books) {
            if (book.title == title) {
                system("cls");
                cout << "Book found!" << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Year: " << book.year << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found!" << endl;
        }
    }

private:
    struct Book {
        string title;
        string author;
        int year;
    };

    //container to hold books
    vector<Book> books;

    // function to save data to a text file
    void saveBooks() {
        ofstream outFile("books.txt");
        if (!outFile.is_open()) {
            cerr << "Error opening file for writing" << endl;
            return;
        }
        for (Book book : books) {
            outFile << book.title << endl;
            outFile << book.author << endl;
            outFile << book.year << endl;
        }
        outFile.close();
    }

    //function for constructor, load book data from the file "books.txt" into the vector
    void loadBooks() {
        ifstream inFile("books.txt");
        if (!inFile.is_open()) {
            cerr << "Error opening file for reading" << endl;
            return;
        }
        string title;
        string author;
        int year;
        while (getline(inFile, title) && getline(inFile, author) && inFile >> year) {
            inFile.ignore(); 
            books.push_back({title, author, year});
        }
        inFile.close();
    }
};

// Function to display the menu
void displayMenu();

int main() {
    displayMenu();
    return 0;
}

void displayMenu() {
    Library library;
    int choice;
    string title;
    string author;
    int year;

    do {
        cout << "\nMenu" << endl;
        cout << "1 - Add Book" << endl;
        cout << "2 - Display Books" << endl;
        cout << "3 - Search Book" << endl;
        cout << "4 - Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(); 
                library.addBook(title, author, year); //add book details 
                break;
            case 2:
                library.displayBooks(); //display books from vector
                break;
            case 3:
                cout << "Enter a book title to search: ";
                getline(cin, title);
                library.searchBook(title); //search book using title
                break;
            case 4:
                cout << "Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);
}
