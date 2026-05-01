/* =====================================================
 * borrowing.c
 * Borrowing record functions
 * Member 3: Eau
 * ===================================================== */

#include <stdio.h>
#include <string.h>
#include "borrowing.h"
#include "filehandling.h"
#include "books.h"
#include "members.h"

/* -------------------------------------------------------
 * issueBook()
 * Issues a book to a member
 * ------------------------------------------------------- */
void issueBook(void) {

    int bookID;
    int memberID;
    int i;
    int bookFound   = 0;
    int memberFound = 0;
    int bookIndex   = -1;
    int memberIndex = -1;

    printf("\n========================================\n");
    printf("           ISSUE A BOOK\n");
    printf("========================================\n");
    printf("  Enter Book ID   : ");
    scanf("%d", &bookID);
    printf("  Enter Member ID : ");
    scanf("%d", &memberID);

    for (i = 0; i < totalBooks; i++) {
        if (books[i].bookID == bookID) {
            bookFound = 1;
            bookIndex = i;
            break;
        }
    }

    for (i = 0; i < totalMembers; i++) {
        if (members[i].memberID == memberID) {
            memberFound = 1;
            memberIndex = i;
            break;
        }
    }

    if (bookFound == 0) {
        printf("\n  Book ID %d not found.\n", bookID);
        return;
    }

    if (memberFound == 0) {
        printf("\n  Member ID %d not found.\n", memberID);
        return;
    }

    if (books[bookIndex].quantity == 0) {
        printf("\n  Sorry! \"%s\" is currently unavailable.\n",
               books[bookIndex].title);
        return;
    }

    borrows[totalBorrows].borrowID  = totalBorrows + 1;
    borrows[totalBorrows].bookID    = bookID;
    borrows[totalBorrows].memberID  = memberID;
    strcpy(borrows[totalBorrows].bookTitle,  books[bookIndex].title);
    strcpy(borrows[totalBorrows].memberName, members[memberIndex].name);
    strcpy(borrows[totalBorrows].borrowDate, "2024-01-01");
    strcpy(borrows[totalBorrows].returnDate, "N/A");
    strcpy(borrows[totalBorrows].status,     "Borrowed");

    books[bookIndex].quantity--;
    if (books[bookIndex].quantity == 0) {
        strcpy(books[bookIndex].status, "Unavailable");
    }

    totalBorrows++;
    saveBorrows();
    saveBooks();

    printf("\n  Book issued successfully!\n");
    printf("  Book   : %s\n", books[bookIndex].title);
    printf("  Member : %s\n", members[memberIndex].name);
    printf("  Status : Borrowed\n");
}

/* -------------------------------------------------------
 * returnBook()
 * Processes the return of a borrowed book
 * ------------------------------------------------------- */
void returnBook(void) {

    int borrowID;
    int i;
    int found = 0;

    printf("\n========================================\n");
    printf("           RETURN A BOOK\n");
    printf("========================================\n");
    printf("  Enter Borrow ID : ");
    scanf("%d", &borrowID);

    for (i = 0; i < totalBorrows; i++) {
        if (borrows[i].borrowID == borrowID &&
            strcmp(borrows[i].status, "Borrowed") == 0) {

            strcpy(borrows[i].status,     "Returned");
            strcpy(borrows[i].returnDate, "2024-01-15");

            int j;
            for (j = 0; j < totalBooks; j++) {
                if (books[j].bookID == borrows[i].bookID) {
                    books[j].quantity++;
                    strcpy(books[j].status, "Available");
                    break;
                }
            }

            saveBorrows();
            saveBooks();

            printf("\n  Book returned successfully!\n");
            printf("  Book   : %s\n", borrows[i].bookTitle);
            printf("  Member : %s\n", borrows[i].memberName);
            printf("  Status : Returned\n");
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\n  Borrow ID %d not found or already returned.\n", borrowID);
    }
}

/* -------------------------------------------------------
 * viewBorrowHistory()
 * Displays all borrowing records
 * ------------------------------------------------------- */
void viewBorrowHistory(void) {

    int i;

    if (totalBorrows == 0) {
        printf("\n  No borrowing records found.\n");
        return;
    }

    printf("\n========================================\n");
    printf("         BORROWING HISTORY\n");
    printf("========================================\n");

    for (i = 0; i < totalBorrows; i++) {
        printf("\n  Record %d of %d\n",  i + 1, totalBorrows);
        printf("  Borrow ID  : %d\n",   borrows[i].borrowID);
        printf("  Book       : %s\n",   borrows[i].bookTitle);
        printf("  Member     : %s\n",   borrows[i].memberName);
        printf("  Borrow Date: %s\n",   borrows[i].borrowDate);
        printf("  Return Date: %s\n",   borrows[i].returnDate);
        printf("  Status     : %s\n",   borrows[i].status);
        printf("  ..............................\n");
    }
}