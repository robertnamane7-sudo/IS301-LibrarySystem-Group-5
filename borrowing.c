#include <stdio.h>
#include <string.h>
#include <time.h>
#include "library.h"
#include "borrowing.h"
#include "filehandling.h"
#include "books.h"
#include "members.h"

void issueBook(void){
    int m, b;
    printf("Member ID: "); scanf("%d", &m);
    printf("Book ID: ");  scanf("%d", &b);
    getchar();

    int bookIdx = findBookIndexByID(b);
    if (bookIdx == -1 || books[bookIdx].available <= 0) {
        printf("Unavailable\n");
        return;
    }

    // check member exists
    if (findMemberIndexByID(m) == -1) {
        printf("Member not found\n");
        return;
    }

    borrows[totalBorrows].recordID = totalBorrows + 1;
    borrows[totalBorrows].memberID = m;
    borrows[totalBorrows].bookID = b;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(borrows[totalBorrows].borrowDate, MAX_DATE, "%Y-%m-%d", tm);
    borrows[totalBorrows].returnDate[0] = '\0';
    strcpy(borrows[totalBorrows].status, "Borrowed");

    totalBorrows++;
    books[bookIdx].available--;

    saveBorrows();
    saveBooks();
    printf("Book issued successfully.\n");
}

void returnBook(void){
    int id;
    printf("Record ID: "); scanf("%d", &id); getchar();

    for (int i = 0; i < totalBorrows; i++) {
        if (borrows[i].recordID == id && strcmp(borrows[i].status, "Borrowed") == 0) {
            strcpy(borrows[i].status, "Returned");

            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            strftime(borrows[i].returnDate, MAX_DATE, "%Y-%m-%d", tm);

            int bookIdx = findBookIndexByID(borrows[i].bookID);
            if (bookIdx != -1 && books[bookIdx].available < books[bookIdx].quantity) {
                books[bookIdx].available++;
            }

            saveBorrows();
            saveBooks();
            printf("Book returned successfully.\n");
            return;
        }
    }
    printf("Record not found or already returned.\n");
}

void viewBorrowHistory(void) {
    if (totalBorrows == 0) {
        printf("\n  No borrowing records.\n");
        return;
    }

    printf("\n  --- Borrowing History ---\n");
    for (int i = 0; i < totalBorrows; i++) {
        // Find book title for clarity
        char bookTitle[MAX_TITLE] = "Unknown";
        for (int j = 0; j < totalBooks; j++) {
            if (books[j].bookID == borrows[i].bookID) {
                strncpy(bookTitle, books[j].title, MAX_TITLE);
                break;
            }
        }

        printf("  Record #%d\n", borrows[i].recordID);
        printf("  Book     : %s (ID: %d)\n", bookTitle, borrows[i].bookID);
        printf("  Member ID: %d\n", borrows[i].memberID);
        printf("  Borrowed : %s\n", borrows[i].borrowDate);
        printf("  Returned : %s\n",
               strlen(borrows[i].returnDate) > 0 ? borrows[i].returnDate : "Not yet");
        printf("  Status   : %s\n", borrows[i].status);
        printf("  ..............................\n");
    }
    printf("  Total: %d record(s)\n", totalBorrows);
}