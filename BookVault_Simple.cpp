#include <bits/stdc++.h>
using namespace std;

class Book {
private:
    string bookId;
    string title;
    string author;
    bool booked;

public:
    Book() {
        bookId = "";
        title = "";
        author = "";
        booked = false;
    }

    Book(string id, string bookTitle, string bookAuthor) {
        bookId = id;
        title = bookTitle;
        author = bookAuthor;
        booked = false;
    }

    string getBookId() {
        return bookId;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    bool isBooked() {
        return booked;
    }

    void issueBook() {
        booked = true;
    }

    void returnBook() {
        booked = false;
    }

    void displayBook() {
        cout << "Book ID: " << bookId
             << " | Title: " << title
             << " | Author: " << author
             << " | Status: " << (booked ? "Not Available" : "Available") << endl;
    }
};
 
class Member {
private:
    string memberId;
    string name;
    vector<string> borrowedBookIds;

public:
    Member() {
        memberId = "";
        name = "";
    }

    Member(string id, string memberName) {
        memberId = id;
        name = memberName;
    }

    virtual ~Member() {}

    string getMemberId() {
        return memberId;
    }

    string getName() {
        return name;
    }

    virtual string getMemberType() = 0;

    int getBorrowedCount() {
        return borrowedBookIds.size();
    }

    virtual int getBorrowLimit() = 0;

    bool hasBorrowedBook(string bookId) {
        for (int i = 0; i < borrowedBookIds.size(); i++) {
            if (borrowedBookIds[i] == bookId) {
                return true;
            }
        }
        return false;
    }

    void borrowBook(string bookId) {
        borrowedBookIds.push_back(bookId);
    }

    void returnBorrowedBook(string bookId) {
        for (int i = 0; i < borrowedBookIds.size(); i++) {
            if (borrowedBookIds[i] == bookId) {
                borrowedBookIds.erase(borrowedBookIds.begin() + i);
                break;
            }
        }
    }

    virtual void displayMember() {
        cout << "Member ID: " << memberId
             << " | Name: " << name
             << " | Type: " << getMemberType()
             << " | Borrowed: " << getBorrowedCount() << endl;
    }
};

class StudentMember : public Member {
public:
    StudentMember(string id, string memberName) : Member(id, memberName) {}

    string getMemberType() {
        return "Student";
    }

    int getBorrowLimit() {
        return 2;
    }
};

class FacultyMember : public Member {
public:
    FacultyMember(string id, string memberName) : Member(id, memberName) {}

    string getMemberType() {
        return "Faculty";
    }

    int getBorrowLimit() {
        return 5;
    }
};

class Library {
private:
    vector<Book> books;
    vector<shared_ptr<Member> > members;

public:
    int findBookIndex(string bookId) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getBookId() == bookId) {
                return i;
            }
        }
        return -1;
    }

    int findMemberIndex(string memberId) {
        for (int i = 0; i < members.size(); i++) {
            if (members[i]->getMemberId() == memberId) {
                return i;
            }
        }
        return -1;
    }

    bool addBook(Book book) {
        if (findBookIndex(book.getBookId()) != -1) {
            return false;
        }

        books.push_back(book);
        return true;
    }

    bool registerMember(shared_ptr<Member> member) {
        if (member == NULL || findMemberIndex(member->getMemberId()) != -1) {
            return false;
        }

        members.push_back(member);
        return true;
    }

    void displayBooks() {
        cout << "\nAvailable Library Books" << endl;

        if (books.empty()) {
            cout << "No books are available in the library." << endl;
            return;
        }

        for (int i = 0; i < books.size(); i++) {
            books[i].displayBook();
        }
    }

    void displayMembers() {
        cout << "\nRegistered Members" << endl;

        if (members.empty()) {
            cout << "No members are registered yet." << endl;
            return;
        }

        for (int i = 0; i < members.size(); i++) {
            members[i]->displayMember();
        }
    }

    void borrowBook(string bookId, string memberId) {
        int bIndex = findBookIndex(bookId);
        int mIndex = findMemberIndex(memberId);

        if (bIndex == -1) {
            cout << "Borrow failed: book not found." << endl;
            return;
        }

        if (mIndex == -1) {
            cout << "Borrow failed: member not found." << endl;
            return;
        }

        if (books[bIndex].isBooked()) {
            cout << "Borrow failed: " << books[bIndex].getTitle()
                 << " is already booked." << endl;
            return;
        }

        if (members[mIndex]->getBorrowedCount() >= members[mIndex]->getBorrowLimit()) {
            cout << "Borrow failed: " << members[mIndex]->getName()
                 << " has reached the borrowing limit." << endl;
            return;
        }

        books[bIndex].issueBook();
        members[mIndex]->borrowBook(bookId);

        cout << "Book borrowed successfully: " << books[bIndex].getTitle()
             << " by " << members[mIndex]->getName() << endl;
    }

    void returnBook(string bookId, string memberId) {
        int bIndex = findBookIndex(bookId);
        int mIndex = findMemberIndex(memberId);

        if (bIndex == -1 || mIndex == -1) {
            cout << "Return failed: invalid book or member." << endl;
            return;
        }

        if (!members[mIndex]->hasBorrowedBook(bookId)) {
            cout << "Return failed: " << members[mIndex]->getName()
                 << " did not borrow " << books[bIndex].getTitle() << "." << endl;
            return;
        }

        books[bIndex].returnBook();
        members[mIndex]->returnBorrowedBook(bookId);

        cout << "Book returned successfully: " << books[bIndex].getTitle()
             << " by " << members[mIndex]->getName() << endl;
    }
};

vector<string> splitLine(string line, char separator) {
    vector<string> parts;
    string current = "";

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == separator) {
            parts.push_back(current);
            current = "";
        } else {
            current += line[i];
        }
    }

    parts.push_back(current);
    return parts;
}

string readText(string message) {
    string value;

    do {
        cout << message;
        getline(cin, value);

        if (value.empty()) {
            cout << "Input cannot be empty. Please try again." << endl;
        } else if (value.find('|') != string::npos) {
            cout << "Please do not use the | character." << endl;
            value = "";
        }
    } while (value.empty());

    return value;
}

int readChoice(int minimum, int maximum) {
    string input;
    int choice;

    cout << "\nEnter your choice: ";
    getline(cin, input);

    if (input.length() != 1 || input[0] < '0' || input[0] > '9') {
        return 0;
    }

    choice = input[0] - '0';

    if (choice < minimum || choice > maximum) {
        return 0;
    }

    return choice;
}

shared_ptr<Member> createMemberFromChoice(string memberId, string name, string typeChoice) {
    if (typeChoice == "1") {
        return shared_ptr<Member>(new StudentMember(memberId, name));
    }

    if (typeChoice == "2") {
        return shared_ptr<Member>(new FacultyMember(memberId, name));
    }

    return shared_ptr<Member>();
}

shared_ptr<Member> createMemberFromType(string memberId, string name, string memberType) {
    if (memberType == "Student") {
        return shared_ptr<Member>(new StudentMember(memberId, name));
    }

    if (memberType == "Faculty") {
        return shared_ptr<Member>(new FacultyMember(memberId, name));
    }

    return shared_ptr<Member>();
}

void showRoleMenu() {
    cout << "\n========== Library Management System ==========" << endl;
    cout << "1. Staff" << endl;
    cout << "2. Visitor" << endl;
    cout << "3. Exit" << endl;
}

void showStaffMenu() {
    cout << "\n========== Staff Menu ==========" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Register Member" << endl;
    cout << "3. View Books" << endl;
    cout << "4. View Members" << endl;
    cout << "5. Back to Role Selection" << endl;
}

void showVisitorMenu() {
    cout << "\n========== Visitor Menu ==========" << endl;
    cout << "1. View Books" << endl;
    cout << "2. Borrow Book" << endl;
    cout << "3. Return Book" << endl;
    cout << "4. Back to Role Selection" << endl;
}

bool saveBookToFile(string fileName, Book book) {
    ofstream file(fileName.c_str(), ios::app);

    if (!file) {
        return false;
    }

    file << book.getBookId() << "|"
         << book.getTitle() << "|"
         << book.getAuthor() << endl;

    return true;
}

bool saveMemberToFile(string fileName, shared_ptr<Member> member) {
    ofstream file(fileName.c_str(), ios::app);

    if (!file || member == NULL) {
        return false;
    }

    file << member->getMemberId() << "|"
         << member->getName() << "|"
         << member->getMemberType() << endl;

    return true;
}

Library loadBooksFromFile(Library library, string fileName) {
    ifstream file(fileName.c_str());
    string line;

    if (!file) {
        ofstream newFile(fileName.c_str());
        return library;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> parts = splitLine(line, '|');

        if (parts.size() == 3) {
            Book book(parts[0], parts[1], parts[2]);
            library.addBook(book);
        }
    }

    return library;
}

Library loadMembersFromFile(Library library, string fileName) {
    ifstream file(fileName.c_str());
    string line;

    if (!file) {
        ofstream newFile(fileName.c_str());
        return library;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> parts = splitLine(line, '|');

        if (parts.size() == 3) {
            shared_ptr<Member> member = createMemberFromType(parts[0], parts[1], parts[2]);
            library.registerMember(member);
        }
    }

    return library;
}

Library addBookFromInput(Library library, string booksFile) {
    string bookId = readText("Enter book ID: ");
    string title = readText("Enter book title: ");
    string author = readText("Enter author name: ");

    Book book(bookId, title, author);

    if (library.addBook(book)) {
        cout << "Book added successfully." << endl;

        if (saveBookToFile(booksFile, book)) {
            cout << "Book saved to " << booksFile << "." << endl;
        } else {
            cout << "Book could not be saved to file." << endl;
        }
    } else {
        cout << "Book already exists with this ID." << endl;
    }

    return library;
}

Library registerNewMember(Library library, string membersFile) {
    string memberId = readText("Enter member ID: ");
    string name = readText("Enter member name: ");
    string type = readText("Enter member type (1 for Student, 2 for Faculty): ");
    shared_ptr<Member> member = createMemberFromChoice(memberId, name, type);

    if (member == NULL) {
        cout << "Invalid member type. Registration cancelled." << endl;
        return library;
    }

    if (library.registerMember(member)) {
        cout << "Member registered successfully." << endl;

        if (saveMemberToFile(membersFile, member)) {
            cout << "Member saved to " << membersFile << "." << endl;
        } else {
            cout << "Member could not be saved to file." << endl;
        }
    } else {
        cout << "Member already exists with this ID." << endl;
    }

    return library;
}

Library borrowBookFromInput(Library library) {
    string bookId = readText("Enter book ID to borrow: ");
    string memberId = readText("Enter member ID: ");
    library.borrowBook(bookId, memberId);
    return library;
}

Library returnBookFromInput(Library library) {
    string bookId = readText("Enter book ID to return: ");
    string memberId = readText("Enter member ID: ");
    library.returnBook(bookId, memberId);
    return library;
}

Library runStaffMenu(Library library, string booksFile, string membersFile) {
    int choice;

    do {
        showStaffMenu();
        choice = readChoice(1, 5);

        switch (choice) {
            case 1:
                library = addBookFromInput(library, booksFile);
                break;
            case 2:
                library = registerNewMember(library, membersFile);
                break;
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.displayMembers();
                break;
            case 5:
                cout << "Returning to role selection." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a number from 1 to 5." << endl;
        }
    } while (choice != 5);

    return library;
}

Library runVisitorMenu(Library library) {
    int choice;

    do {
        showVisitorMenu();
        choice = readChoice(1, 4);

        switch (choice) {
            case 1:
                library.displayBooks();
                break;
            case 2:
                library = borrowBookFromInput(library);
                break;
            case 3:
                library = returnBookFromInput(library);
                break;
            case 4:
                cout << "Returning to role selection." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a number from 1 to 4." << endl;
        }
    } while (choice != 4);

    return library;
}

int main() {
    string booksFile = "Storage/books.txt";
    string membersFile = "Storage/members.txt";
    Library library;
    int choice;

    library = loadBooksFromFile(library, booksFile);
    library = loadMembersFromFile(library, membersFile);

    do {
        showRoleMenu();
        choice = readChoice(1, 3);
        string pass;

        switch (choice) {
            case 1:
                do {
                    cout << "Enter pass: ";
                    getline(cin, pass);

                    if (pass != "4213") {
                        cout << "Access denied. Please try again." << endl;
                    }
                } while (pass != "4213");

                cout << "Access granted." << endl;
                library = runStaffMenu(library, booksFile, membersFile);
                break;
            case 2:
                library = runVisitorMenu(library);
                break;
            case 3:
                cout << "Thank you for using the Library Management System." << endl;
                break;
            default:
                cout << "Invalid choice. Please select a number from 1 to 3." << endl;
        }
    } while (choice != 3);

    return 0;
}
