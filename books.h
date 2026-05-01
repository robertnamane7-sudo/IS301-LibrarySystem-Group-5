/* =====================================================
 * books.h
 * Header for book management functions
 * Member 3: Eau
 * ===================================================== */

#ifndef BOOKS_H
#define BOOKS_H

#include "library.h"

extern struct Book books[];
extern int totalBooks;

/* Function declarations */
void displayAllBooks(void);
void searchBook(void);
void addBook(void);
void removeBook(void);
void updateQuantity(void);
void generateReport(void);

#endif