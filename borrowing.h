/* =====================================================
 * borrowing.h
 * Header for borrowing record functions
 * Member 4: Ruhama
 * ===================================================== */

#ifndef BORROWING_H
#define BORROWING_H

#include "library.h"

extern struct BorrowRecord borrows[];
extern int totalBorrows;

/* Function declarations */
void issueBook(void);
void returnBook(void);
void viewBorrowHistory(void);

#endif