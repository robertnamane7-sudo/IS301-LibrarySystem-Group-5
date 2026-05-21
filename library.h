/* =====================================================
 * library.h
 * Shared header file for LibrarySystem
 * Contains all struct definitions used by the team
 * ===================================================== */

#ifndef LIBRARY_H
#define LIBRARY_H

/* Maximum number of books the system can hold */
#define MAX_BOOKS 100

/* -------------------------------------------------------
 * struct Book
 * Holds all details for one book in the library
 * ------------------------------------------------------- */
struct Book {
    int  bookID;
    char title[100];
    char author[50];
    char genre[30];
    int  yearPublished;
    int  quantity;
    char status[20];   /* "Available" or "Unavailable" */
};
/* Maximum number of members the system can hold */
#define MAX_MEMBERS 100

/* -------------------------------------------------------
 * struct Member
 * Holds all details for one library member
 * ------------------------------------------------------- */
struct Member {
    int  memberID;
    char name[50];
    char email[50];
    char phone[20];
    char status[20];   /* "Active" or "Inactive" */
};
/* Maximum number of borrow records */
#define MAX_BORROWS 200

/* -------------------------------------------------------
 * struct BorrowRecord
 * Holds details of one borrowing transaction
 * ------------------------------------------------------- */
struct BorrowRecord {
    int  borrowID;
    int  bookID;
    int  memberID;
    char bookTitle[100];
    char memberName[50];
    char borrowDate[20];
    char returnDate[20];
    char status[20];    /* "Borrowed" or "Returned" */
};

#endif