/*
 * filehandling.h  -  File Handling Module Header
 * IS301 Library Management System
 *
 * Handles loading and saving of system data.
 */

#ifndef FILEHANDLING_H
#define FILEHANDLING_H

/* ===============================
   BOOK FILE OPERATIONS
   =============================== */

/* Load books from books.txt */
void loadBooks(void);

/* Save books to books.txt */
void saveBooks(void);


/* ===============================
   MEMBER FILE OPERATIONS
   =============================== */

/* Load members from members.txt */
void loadMembers(void);

/* Save members to members.txt */
void saveMembers(void);


/* ===============================
   BORROWING FILE OPERATIONS
   =============================== */

/* Load borrowing records */
void loadBorrows(void);

/* Save borrowing records */
void saveBorrows(void);


/* ===============================
   REPORT GENERATION
   =============================== */

/* Generate inventory report */
void generateReport(void);

#endif /* FILEHANDLING_H */