/*
 * books.h  -  Book Management Module Header
 * IS301 Library Management System
 *
 * Contains function prototypes for managing books.
 */

#ifndef BOOKS_H
#define BOOKS_H

/* Display all books */
void displayAllBooks(void);

/* Search book by title or author */
void searchBook(void);

/* Add a new book */
void addBook(void);

/* Update quantity of a book */
void updateBookQuantity(void);

/* Find book index using Book ID */
int findBookIndexByID(int id);

/* Remove a book from the inventory by ID */
void removeBook(void);

#endif /* BOOKS_H */