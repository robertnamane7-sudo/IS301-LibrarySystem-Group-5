/* =====================================================
 * books.c
 * Book management functions
 * Member 3: Eau
 * ===================================================== */

#include <stdio.h>
#include <string.h>
#include "books.h"
#include "filehandling.h"

/* -------------------------------------------------------
 * displayAllBooks()
 * Prints all books currently loaded in memory
 * ------------------------------------------------------- */
void displayAllBooks(void) {

    int i;

    if (totalBooks == 0) {
        printf("\n  No books found in the system.\n");
        return;
    }

    printf("\n========================================\n");
    printf("           ALL BOOKS\n");
    printf("========================================\n");

    for (i = 0; i < totalBooks; i++) {
        printf("\n  Book %d of %d\n", i + 1, totalBooks);
        printf("  ID     : %d\n",  books[i].bookID);
        printf("  Title  : %s\n",  books[i].title);
        printf("  Author : %s\n",  books[i].author);
        printf("  Genre  : %s\n",  books[i].genre);
        printf("  Year   : %d\n",  books[i].yearPublished);
        printf("  Qty    : %d\n",  books[i].quantity);
        printf("  Status : %s\n",  books[i].status);
        printf("  ..............................\n");
    }
}

/* -------------------------------------------------------
 * searchBook()
 * Searches for a book by title or author name
 * ------------------------------------------------------- */
void searchBook(void) {

    char keyword[100];
    int  i;
    int  found = 0;

    while (getchar() != '\n');

    printf("\n========================================\n");
    printf("           SEARCH FOR A BOOK\n");
    printf("========================================\n");
    printf("  Enter title or author to search: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("\n  Search results for: \"%s\"\n", keyword);
    printf("  ..............................\n");

    for (i = 0; i < totalBooks; i++) {
        if (strstr(books[i].title,  keyword) != NULL ||
            strstr(books[i].author, keyword) != NULL) {

            printf("\n  ID     : %d\n", books[i].bookID);
            printf("  Title  : %s\n",   books[i].title);
            printf("  Author : %s\n",   books[i].author);
            printf("  Genre  : %s\n",   books[i].genre);
            printf("  Year   : %d\n",   books[i].yearPublished);
            printf("  Qty    : %d\n",   books[i].quantity);
            printf("  Status : %s\n",   books[i].status);
            printf("  ..............................\n");
            found++;
        }
    }

    if (found == 0) {
        printf("\n  No books found matching \"%s\"\n", keyword);
    } else {
        printf("\n  %d match(es) found.\n", found);
    }
}

/* -------------------------------------------------------
 * addBook()
 * Accepts input from user and adds a new book
 * ------------------------------------------------------- */
void addBook(void) {

    if (totalBooks >= MAX_BOOKS) {
        printf("\n  Library is full. Cannot add more books.\n");
        return;
    }

    while (getchar() != '\n');

    printf("\n========================================\n");
    printf("           ADD A NEW BOOK\n");
    printf("========================================\n");

    printf("  Enter Book ID     : ");
    scanf("%d", &books[totalBooks].bookID);
    while (getchar() != '\n');

    printf("  Enter Title       : ");
    fgets(books[totalBooks].title, 100, stdin);
    books[totalBooks].title[strcspn(books[totalBooks].title, "\n")] = 0;

    printf("  Enter Author      : ");
    fgets(books[totalBooks].author, 50, stdin);
    books[totalBooks].author[strcspn(books[totalBooks].author, "\n")] = 0;

    printf("  Enter Genre       : ");
    fgets(books[totalBooks].genre, 30, stdin);
    books[totalBooks].genre[strcspn(books[totalBooks].genre, "\n")] = 0;

    printf("  Enter Year        : ");
    scanf("%d", &books[totalBooks].yearPublished);

    printf("  Enter Quantity    : ");
    scanf("%d", &books[totalBooks].quantity);

    if (books[totalBooks].quantity > 0) {
        strcpy(books[totalBooks].status, "Available");
    } else {
        strcpy(books[totalBooks].status, "Unavailable");
    }

    totalBooks++;
    printf("\n  Book added successfully!\n");
    printf("  Total books in system: %d\n", totalBooks);
    saveBooks();
}

/* -------------------------------------------------------
 * removeBook()
 * Finds a book by ID and removes it from the array
 * ------------------------------------------------------- */
void removeBook(void) {

    int searchID;
    int i;
    int found = 0;

    printf("\n========================================\n");
    printf("           REMOVE A BOOK\n");
    printf("========================================\n");
    printf("  Enter Book ID to remove: ");
    scanf("%d", &searchID);

    for (i = 0; i < totalBooks; i++) {
        if (books[i].bookID == searchID) {

            printf("\n  Book found!\n");
            printf("  Title  : %s\n", books[i].title);
            printf("  Author : %s\n", books[i].author);
            printf("\n  Press 1 to confirm, 0 to cancel: ");
            int confirm;
            scanf("%d", &confirm);

            if (confirm != 1) {
                printf("\n  Remove cancelled.\n");
                return;
            }

            for (i = i; i < totalBooks - 1; i++) {
                books[i] = books[i + 1];
            }

            totalBooks--;
            printf("\n  Book removed successfully!\n");
            printf("  Total books remaining: %d\n", totalBooks);
            saveBooks();
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\n  Book ID %d not found.\n", searchID);
    }
}

/* -------------------------------------------------------
 * updateQuantity()
 * Finds a book by ID and updates its quantity
 * ------------------------------------------------------- */
void updateQuantity(void) {

    int searchID;
    int newQty;
    int i;
    int found = 0;

    printf("\n========================================\n");
    printf("        UPDATE BOOK QUANTITY\n");
    printf("========================================\n");
    printf("  Enter Book ID to update: ");
    scanf("%d", &searchID);

    for (i = 0; i < totalBooks; i++) {
        if (books[i].bookID == searchID) {

            printf("\n  Book found!\n");
            printf("  Title    : %s\n", books[i].title);
            printf("  Author   : %s\n", books[i].author);
            printf("  Current Quantity: %d\n", books[i].quantity);
            printf("\n  Enter new quantity: ");
            scanf("%d", &newQty);

            if (newQty < 0) {
                printf("\n  Invalid quantity. Must be 0 or more.\n");
                return;
            }

            books[i].quantity = newQty;

            if (books[i].quantity > 0) {
                strcpy(books[i].status, "Available");
            } else {
                strcpy(books[i].status, "Unavailable");
            }

            printf("\n  Quantity updated successfully!\n");
            printf("  New Quantity : %d\n", books[i].quantity);
            printf("  New Status   : %s\n", books[i].status);
            saveBooks();
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\n  Book ID %d not found.\n", searchID);
    }
}

/* -------------------------------------------------------
 * generateReport()
 * Writes full inventory report to inventory_report.txt
 * ------------------------------------------------------- */
void generateReport(void) {

    FILE *outFile;
    int   i;

    extern struct BorrowRecord borrows[];
    extern int totalMembers;
    extern int totalBorrows;

    outFile = fopen("inventory_report.txt", "w");
    if (outFile == NULL) {
        printf("\n  Error: Could not create inventory_report.txt\n");
        return;
    }

    fprintf(outFile, "================================================\n");
    fprintf(outFile, "         LIBRARY INVENTORY REPORT\n");
    fprintf(outFile, "================================================\n");
    fprintf(outFile, "Total Books in System: %d\n", totalBooks);
    fprintf(outFile, "Total Members        : %d\n", totalMembers);
    fprintf(outFile, "Total Borrow Records : %d\n", totalBorrows);
    fprintf(outFile, "================================================\n\n");

    for (i = 0; i < totalBooks; i++) {
        fprintf(outFile, "BookID           : %d\n",  books[i].bookID);
        fprintf(outFile, "Title            : %s\n",  books[i].title);
        fprintf(outFile, "Author           : %s\n",  books[i].author);
        fprintf(outFile, "Genre            : %s\n",  books[i].genre);
        fprintf(outFile, "Year Published   : %d\n",  books[i].yearPublished);
        fprintf(outFile, "Quantity         : %d\n",  books[i].quantity);
        fprintf(outFile, "Availability     : %s\n",  books[i].status);
        fprintf(outFile, "----------------------------\n");
    }

    fprintf(outFile, "\n================================================\n");
    fprintf(outFile, "         BORROWING SUMMARY\n");
    fprintf(outFile, "================================================\n");

    for (i = 0; i < totalBorrows; i++) {
        fprintf(outFile, "Borrow ID        : %d\n",  borrows[i].borrowID);
        fprintf(outFile, "Book             : %s\n",  borrows[i].bookTitle);
        fprintf(outFile, "Member           : %s\n",  borrows[i].memberName);
        fprintf(outFile, "Borrow Date      : %s\n",  borrows[i].borrowDate);
        fprintf(outFile, "Return Date      : %s\n",  borrows[i].returnDate);
        fprintf(outFile, "Status           : %s\n",  borrows[i].status);
        fprintf(outFile, "----------------------------\n");
    }

    fprintf(outFile, "\n================================================\n");
    fprintf(outFile, "             END OF REPORT\n");
    fprintf(outFile, "================================================\n");

    fclose(outFile);
    printf("\n  Report generated successfully!\n");
    printf("  Saved to: data/inventory_report.txt\n");
}