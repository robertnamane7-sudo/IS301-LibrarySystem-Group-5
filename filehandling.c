#include <stdio.h>
#include <string.h>
#include <time.h>
#include "library.h"
#include "filehandling.h"

void loadBooks(void){
    FILE *f=fopen(BOOKS_FILE,"r");
    if(!f) return;
    while(fscanf(f,"%d,%99[^,],%59[^,],%29[^,],%d,%d\n",
        &books[totalBooks].bookID,
        books[totalBooks].title,
        books[totalBooks].author,
        books[totalBooks].genre,
        &books[totalBooks].yearPublished,
        &books[totalBooks].quantity)==6){
        books[totalBooks].available=books[totalBooks].quantity;
        totalBooks++;
    }
    fclose(f);
}

void saveBooks(void){
    FILE *f=fopen(BOOKS_FILE,"w");
    for(int i=0;i<totalBooks;i++){
        fprintf(f,"%d,%s,%s,%s,%d,%d\n",
        books[i].bookID,books[i].title,books[i].author,
        books[i].genre,books[i].yearPublished,books[i].quantity);
    }
    fclose(f);
}

void loadMembers(void) {
    FILE *f = fopen(MEMBERS_FILE, "r");
    if (!f) return;

    char buffer[256];

    // Skip the header line (first line)
    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        fclose(f);
        return;   // empty file
    }

    // Now read the actual member data
    while (fscanf(f, "%d,%59[^,],%59[^,],%19[^\n]\n",
                  &members[totalMembers].memberID,
                  members[totalMembers].name,
                  members[totalMembers].email,
                  members[totalMembers].phone) == 4) {
        totalMembers++;
        if (totalMembers >= MAX_MEMBERS) break;
    }
    fclose(f);
}

void saveMembers(void) {
    FILE *f = fopen(MEMBERS_FILE, "w");
    if (!f) return;

    // Write the header
    fprintf(f, "MembersID,MembersName,MembersEmail,MembersPhone\n");

    // Write each member record
    for (int i = 0; i < totalMembers; i++) {
        fprintf(f, "%d,%s,%s,%s\n",
                members[i].memberID,
                members[i].name,
                members[i].email,
                members[i].phone);
    }
    fclose(f);
}

void loadBorrows(void) {
    FILE *f = fopen(BORROWS_FILE, "r");
    if (!f) return;

    char buffer[256];
    // skip header line
    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        fclose(f);
        return;
    }

    while (fscanf(f, "%d,%d,%d,%19[^,],%19[^,],%19[^\n]\n",
                  &borrows[totalBorrows].recordID,
                  &borrows[totalBorrows].memberID,
                  &borrows[totalBorrows].bookID,
                  borrows[totalBorrows].borrowDate,
                  borrows[totalBorrows].returnDate,
                  borrows[totalBorrows].status) == 6) {
        totalBorrows++;
        if (totalBorrows >= MAX_BORROWS) break;
    }
    fclose(f);
}

void saveBorrows(void) {
    FILE *f = fopen(BORROWS_FILE, "w");
    if (!f) return;

    fprintf(f, "RecordID,MemberID,BookID,BorrowDate,ReturnDate,Status\n");
    for (int i = 0; i < totalBorrows; i++) {
        fprintf(f, "%d,%d,%d,%s,%s,%s\n",
                borrows[i].recordID,
                borrows[i].memberID,
                borrows[i].bookID,
                borrows[i].borrowDate,
                borrows[i].returnDate,
                borrows[i].status);
    }
    fclose(f);
}

void generateReport(void) {
    FILE *f = fopen(REPORT_FILE, "w");
    if (f == NULL) {
        printf("\n  Error: Could not create report file.\n");
        return;
    }

    // Get current date and time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char datetime[50];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", t);

    // ---- Report Header ----
    fprintf(f, "================================================\n");
    fprintf(f, "         LIBRARY INVENTORY REPORT\n");
    fprintf(f, "         Generated: %s\n", datetime);
    fprintf(f, "================================================\n");
    fprintf(f, "Total Books           : %d\n", totalBooks);
    fprintf(f, "Total Members         : %d\n", totalMembers);
    fprintf(f, "Total Borrow Records  : %d\n", totalBorrows);
    fprintf(f, "================================================\n\n");

    // ---- Book Details Section ----
    fprintf(f, "-- BOOK DETAILS --\n\n");
    if (totalBooks == 0) {
        fprintf(f, "No books in inventory.\n\n");
    } else {
        for (int i = 0; i < totalBooks; i++) {
            // Exactly as the spec requires: no extra spaces, BookID zero-padded
            fprintf(f, "BookID: %03d\n", books[i].bookID);
            fprintf(f, "Title: %s\n", books[i].title);
            fprintf(f, "Author: %s\n", books[i].author);
            fprintf(f, "Genre: %s\n", books[i].genre);
            fprintf(f, "Year Published: %d\n", books[i].yearPublished);
            fprintf(f, "Quantity: %d\n", books[i].quantity);
            fprintf(f, "Availability Status: %s\n",
                    (books[i].available > 0) ? "Available" : "Checked Out");
            fprintf(f, "----------------------------\n");
        }
    }

    // ---- Borrowing Summary Section ----
    fprintf(f, "\n================================================\n");
    fprintf(f, "         BORROWING SUMMARY\n");
    fprintf(f, "================================================\n");

    if (totalBorrows == 0) {
        fprintf(f, "No borrowing records found.\n");
    } else {
        for (int i = 0; i < totalBorrows; i++) {
            // Safely copy book title
            char bookTitle[MAX_TITLE];
            strncpy(bookTitle, "Unknown", MAX_TITLE - 1);
            bookTitle[MAX_TITLE - 1] = '\0';
            for (int j = 0; j < totalBooks; j++) {
                if (books[j].bookID == borrows[i].bookID) {
                    strncpy(bookTitle, books[j].title, MAX_TITLE - 1);
                    bookTitle[MAX_TITLE - 1] = '\0';
                    break;
                }
            }

            // Safely copy member name
            char memberName[MAX_NAME];
            strncpy(memberName, "Unknown", MAX_NAME - 1);
            memberName[MAX_NAME - 1] = '\0';
            for (int j = 0; j < totalMembers; j++) {
                if (members[j].memberID == borrows[i].memberID) {
                    strncpy(memberName, members[j].name, MAX_NAME - 1);
                    memberName[MAX_NAME - 1] = '\0';
                    break;
                }
            }

            fprintf(f, "Borrow ID          : %d\n", borrows[i].recordID);
            fprintf(f, "Book ID            : %d\n", borrows[i].bookID);
            fprintf(f, "Book Title         : %s\n", bookTitle);
            fprintf(f, "Member ID          : %d\n", borrows[i].memberID);
            fprintf(f, "Member Name        : %s\n", memberName);
            fprintf(f, "Borrow Date        : %s\n", borrows[i].borrowDate);
            fprintf(f, "Return Date        : %s\n",
                    strlen(borrows[i].returnDate) > 0 ? borrows[i].returnDate : "N/A");
            fprintf(f, "Status             : %s\n", borrows[i].status);
            fprintf(f, "----------------------------\n");
        }
    }

    fprintf(f, "\n================================================\n");
    fprintf(f, "             END OF REPORT\n");
    fprintf(f, "================================================\n");

    fclose(f);

    // On‑screen confirmation (single, reliable pause)
    printf("\n  Inventory report generated successfully!\n");
    printf("  File: %s\n", REPORT_FILE);
    printf("  Press Enter to continue...");
    while (getchar() != '\n');
}