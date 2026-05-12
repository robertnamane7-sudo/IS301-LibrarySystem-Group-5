/*
 * borrowing.h  -  Borrowing Module Header
 * IS301 Library Management System
 *
 * Contains function prototypes for issuing,
 * returning, and viewing borrowing records.
 */

#ifndef BORROWING_H
#define BORROWING_H

/* Issue a book to a member */
void issueBook(void);

/* Return a borrowed book */
void returnBook(void);

/* Display borrowing history */
void viewBorrowHistory(void);

#endif /* BORROWING_H */