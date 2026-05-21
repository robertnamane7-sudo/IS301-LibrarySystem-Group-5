/* =====================================================
 * main.c
 * Main entry point for Library Management System
 * Group Leader: Robert
 * IS301 Structured Programming in C
 * Divine Word University — 2026
 * ===================================================== */

#include <stdio.h>
#include <string.h>
#include "library.h"
#include "auth.h"
#include "menu.h"
#include "filehandling.h"
#include "books.h"
#include "members.h"
#include "borrowing.h"

/* -------------------------------------------------------
 * Global arrays — shared across all modules
 * ------------------------------------------------------- */
struct Book        books[MAX_BOOKS];
struct Member      members[MAX_MEMBERS];
struct BorrowRecord borrows[MAX_BORROWS];

int totalBooks   = 0;
int totalMembers = 0;
int totalBorrows = 0;

/* -------------------------------------------------------
 * main()
 * Entry point - login, load data, run menu loop
 * ------------------------------------------------------- */
int main(void) {

    int choice;

    /* Step 1 - Login */
    if (login() == 0) {
        return 1;
    }

    /* Step 2 - Load all data from files */
    printf("\n  Loading library data...\n");
    loadBooks();
    loadMembers();
    loadBorrows();

    /* Step 3 - Main menu loop */
    do {

        displayMenu();
        choice = getValidChoice(0, 7);

        switch (choice) {
            case 1:
                displayAllBooks();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                addBook();
                break;
            case 4:
                updateQuantity();
                break;
            case 5:
                generateReport();
                break;
            case 6:
                printf("\n========================================\n");
                printf("       MEMBER MANAGEMENT\n");
                printf("========================================\n");
                printf("  1. View All Members\n");
                printf("  2. Register New Member\n");
                printf("========================================\n");
                printf("  Enter choice: ");
                int memberChoice = getValidChoice(1, 2);
                if (memberChoice == 1) {
                    displayAllMembers();
                } else {
                    registerMember();
                }
                break;
            case 7:
                printf("\n========================================\n");
                printf("       BORROWING RECORDS\n");
                printf("========================================\n");
                printf("  1. Issue a Book\n");
                printf("  2. Return a Book\n");
                printf("  3. View Borrow History\n");
                printf("========================================\n");
                printf("  Enter choice: ");
                int borrowChoice = getValidChoice(1, 3);
                if (borrowChoice == 1) {
                    issueBook();
                } else if (borrowChoice == 2) {
                    returnBook();
                } else {
                    viewBorrowHistory();
                }
                break;
            case 0:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}