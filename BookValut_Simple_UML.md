# BookVault Simple UML Diagram

```mermaid
classDiagram
direction LR

class Book {
  - string bookId
  - string title
  - string author
  - bool booked
  + Book()
  + Book(string id, string bookTitle, string bookAuthor)
  + string getBookId()
  + string getTitle()
  + string getAuthor()
  + bool isBooked()
  + void issueBook()
  + void returnBook()
  + void displayBook()
}

class Member {
  <<abstract>>
  - string memberId
  - string name
  - vector~string~ borrowedBookIds
  + Member()
  + Member(string id, string memberName)
  + virtual ~Member()
  + string getMemberId()
  + string getName()
  + virtual string getMemberType()*
  + int getBorrowedCount()
  + virtual int getBorrowLimit()*
  + bool hasBorrowedBook(string bookId)
  + void borrowBook(string bookId)
  + void returnBorrowedBook(string bookId)
  + virtual void displayMember()
}

class StudentMember {
  + StudentMember(string id, string memberName)
  + string getMemberType()
  + int getBorrowLimit()
}

class FacultyMember {
  + FacultyMember(string id, string memberName)
  + string getMemberType()
  + int getBorrowLimit()
}

class Library {
  - vector~Book~ books
  - vector~shared_ptr~Member~~ members
  + int findBookIndex(string bookId)
  + int findMemberIndex(string memberId)
  + bool addBook(Book book)
  + bool registerMember(shared_ptr~Member~ member)
  + void displayBooks()
  + void displayMembers()
  + void borrowBook(string bookId, string memberId)
  + void returnBook(string bookId, string memberId)
}

class Application {
  <<utility>>
  + vector~string~ splitLine(string line, char separator)
  + string readText(string message)
  + int readChoice(int minimum, int maximum)
  + shared_ptr~Member~ createMemberFromChoice(string memberId, string name, string typeChoice)
  + shared_ptr~Member~ createMemberFromType(string memberId, string name, string memberType)
  + void showRoleMenu()
  + void showStaffMenu()
  + void showVisitorMenu()
  + bool saveBookToFile(string fileName, Book book)
  + bool saveMemberToFile(string fileName, Member member)
  + Library loadBooksFromFile(Library library, string fileName)
  + Library loadMembersFromFile(Library library, string fileName)
  + Library addBookFromInput(Library library, string booksFile)
  + Library registerNewMember(Library library, string membersFile)
  + Library borrowBookFromInput(Library library)
  + Library returnBookFromInput(Library library)
  + Library runStaffMenu(Library library, string booksFile, string membersFile)
  + Library runVisitorMenu(Library library)
}

class main {
  + int main()
}

Library "1" o-- "0..*" Book : contains
Library "1" o-- "0..*" Member : contains polymorphic pointers
Member <|-- StudentMember
Member <|-- FacultyMember
Member "1" --> "0..*" string : borrowedBookIds
Application ..> Book : creates / saves / loads
Application ..> Member : creates / saves / loads
Application ..> Library : controls
main ..> Application : uses
main ..> Library : initializes
```

## Notes

- `Book`, abstract `Member`, `StudentMember`, `FacultyMember`, and `Library` are the core domain classes.
- `Application` groups the free functions that handle menus, input, parsing, file I/O, and role-based flow.
- `Library` owns the collections of `Book` objects and polymorphic `Member` pointers, then enforces borrowing rules through virtual member behavior.
- Persistence uses `Storage/books.txt` and `Storage/members.txt`.
