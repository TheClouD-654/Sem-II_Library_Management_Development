# BookVault Simple Library Management System

BookVault Simple is a menu-driven C++ console application for managing a small library. It demonstrates basic object-oriented programming concepts using books, members, borrowing, returning, menus, and file handling.

## Objective

The objective of this project is to demonstrate a simple Library Management System using C++ classes and objects.

## Features

- Loads books from `Storage/books.txt`.
- Loads members from `Storage/members.txt`.
- Staff can add books.
- Staff can register student or faculty members.
- Visitors can view books.
- Visitors can borrow books.
- Visitors can return books.
- New books and members are saved to text files.
- Duplicate book IDs and member IDs are not allowed.
- A book cannot be borrowed if it is already booked.
- Students can borrow up to 2 books.
- Faculty members can borrow up to 5 books.

## Files

- `BookValut_Simple.cpp` - main source code.
- `BookValut_Simple.exe` - compiled executable.
- `Storage/books.txt` - stores book records.
- `Storage/members.txt` - stores member records.
- `BookValut_Simple_UML.mdj` - StarUML project file for the class diagram.

## How to Run

Compile the program:

```bash
g++ BookValut_Simple.cpp -o BookValut_Simple.exe
```

Run the program:

```bash
.\BookValut_Simple.exe
```

## Text File Format

`Storage/books.txt`

```text
bookId|title|author
01|Harry Potter|J K Rowlin
02|Second Book|Tarun
```

`Storage/members.txt`

```text
memberId|name|type
01|Arunangshu|Student
05|Dr. Yasotha R|Faculty
```

Member type should be either `Student` or `Faculty`.

## User Roles

When the program starts, it asks the user to choose a role:

```text
1. Staff
2. Visitor
3. Exit
```

Staff password:

```text
4213
```

Staff options:

```text
1. Add Book
2. Register Member
3. View Books
4. View Members
5. Back to Role Selection
```

Visitor options:

```text
1. View Books
2. Borrow Book
3. Return Book
4. Back to Role Selection
```

## Classes Used

### Book

Stores book details and availability status.

Main data members:

- `bookId`
- `title`
- `author`
- `booked`

Main functions:

- `getBookId()`
- `getTitle()`
- `getAuthor()`
- `isBooked()`
- `issueBook()`
- `returnBook()`
- `displayBook()`

### Member

Abstract base class that stores common member details and borrowed book IDs.

Main data members:

- `memberId`
- `name`
- `borrowedBookIds`

Main functions:

- `getMemberId()`
- `getName()`
- `getMemberType()`
- `getBorrowedCount()`
- `getBorrowLimit()`
- `hasBorrowedBook()`
- `borrowBook()`
- `returnBorrowedBook()`
- `displayMember()`

### StudentMember

Inherits from `Member` and returns a borrowing limit of 2 books.

### FacultyMember

Inherits from `Member` and returns a borrowing limit of 5 books.

### Library

Stores all books and members, and controls library operations.

Main data members:

- `books`
- `members`

Main functions:

- `findBookIndex()`
- `findMemberIndex()`
- `addBook()`
- `registerMember()`
- `displayBooks()`
- `displayMembers()`
- `borrowBook()`
- `returnBook()`

## OOP Concepts Used

- **Class and Object:** `Book`, `Member`, `StudentMember`, `FacultyMember`, and `Library` are classes. Objects are created for books, members, and the library.
- **Encapsulation:** Data members are private and accessed through public member functions.
- **Inheritance:** `StudentMember` and `FacultyMember` inherit common member behavior from the `Member` base class.
- **Polymorphism:** `Library` stores `shared_ptr<Member>` objects and calls virtual functions such as `getBorrowLimit()` and `getMemberType()`, so the correct student or faculty behavior runs at runtime.
- **Abstraction:** `Member` is an abstract class with pure virtual functions for member type and borrow limit.
- **Composition:** `Library` contains collections of `Book` objects and polymorphic `Member` pointers.
- **File Handling:** `fstream` is used to read and write book/member records.

`Application` represents the non-class helper functions from the C++ file, such as menu display, input reading, file loading, file saving, and `main()`.

## Demonstration Flow

1. Start the program.
2. Choose `Staff`.
3. Enter password `4213`.
4. Add a new book or register a new member.
5. Go back to role selection.
6. Choose `Visitor`.
7. View books.
8. Borrow a book using book ID and member ID.
9. Try borrowing the same book again to show validation.
10. Return the borrowed book.
11. Exit the program.

## Expected Output Summary

The program displays role-based menus, allows staff to add books and members, saves new records to text files, allows visitors to borrow and return books, prevents duplicate borrowing, and exits cleanly.
