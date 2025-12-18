#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

class Book {
private:
    string title;
    string author;
    int id;
    bool available;

public:
    Book(string t = "", string a = "", int i = 0, bool avail = true) {
        title = t;
        author = a;
        id = i;
        available = avail;
    }

    void setBook() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter the title of the Book: ";
        getline(cin, title);

        cout << "Enter the author of the Book: ";
        getline(cin, author);

        cout << "Enter the id number of the book: ";
        cin >> id;

        available = true;
    }

    void displayBook() {
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nID: " << id;
        cout << "\nStatus: " << (available ? "[Available]\n" : "[Borrowed]\n");
    }

    int getId() {
        return id;
    }

    bool isAvailable() {
        return available;
    }

    void borrowBook() {
        available = false;
    }

    void returnBook() {
        available = true;
    }

    string toFileString() {
        return title + "|" + author + "|" + to_string(id) + "|" + (available ? "1" : "0");
    }

    static Book fromFileString(string line) {
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);

        string title = line.substr(0, p1);
        string author = line.substr(p1 + 1, p2 - p1 - 1);
        int id = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        bool available = (line.substr(p3 + 1) == "1");

        return Book(title, author, id, available);
    }
};

int main11() {
    vector<Book> library;
    int choice;

    do {
        cout << "\n---- LIBRARY MENU ----\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Save Library\n";
        cout << "6. Load Library\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Book b;
            b.setBook();
            library.push_back(b);
            cout << "Book added successfully.\n";
        }
        else if (choice == 2) {
            if (library.empty()) {
                cout << "No books available.\n";
            } else {
                for (int i = 0; i < library.size(); i++) {
                    library[i].displayBook();
                }
            }
        }
        else if (choice == 3) {
            int num;
            cout << "Enter book ID to borrow: ";
            cin >> num;

            bool found = false;
            for (int i = 0; i < library.size(); i++) {
                if (library[i].getId() == num) {
                    found = true;
                    if (library[i].isAvailable()) {
                        library[i].borrowBook();
                        cout << "Book borrowed successfully.\n";
                    } else {
                        cout << "Book already borrowed.\n";
                    }
                    break;
                }
            }
            if (!found) cout << "Book not found.\n";
        }
        else if (choice == 4) {
            int num;
            cout << "Enter book ID to return: ";
            cin >> num;

            bool found = false;
            for (int i = 0; i < library.size(); i++) {
                if (library[i].getId() == num) {
                    found = true;
                    if (!library[i].isAvailable()) {
                        library[i].returnBook();
                        cout << "Book returned successfully.\n";
                    } else {
                        cout << "Book was not borrowed.\n";
                    }
                    break;
                }
            }
            if (!found) cout << "Book not found.\n";
        }
        else if (choice == 5) {
            ofstream file("Library.txt");
            for (int i = 0; i < library.size(); i++) {
                file << library[i].toFileString() << endl;
            }
            file.close();
            cout << "Library saved to file.\n";
        }
        else if (choice == 6) {
            library.clear();
            ifstream file("Library.txt");
            string line;

            while (getline(file, line)) {
                library.push_back(Book::fromFileString(line));
            }

            file.close();
            cout << "Library loaded from file.\n";
        }
        else if (choice == 7) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
