#include <stdio.h>
#include "library.h"
#include "menu.h"
#include "books.h"
#include "members.h"
#include "borrowing.h"
#include "filehandling.h"
#include "auth.h"

/* Global data */
Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
BorrowRecord borrows[MAX_BORROWS];

int totalBooks = 0;
int totalMembers = 0;
int totalBorrows = 0;

/* Pause function – clears buffer then waits for Enter */
void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');   // clear any leftover newline
    getchar();                   // wait for Enter
}

int main() {
    if (!login()) return 0;

    loadBooks();
    loadMembers();
    loadBorrows();

    int choice;

    do {
        displayMenu();
        choice = getValidChoice(0, 8);   // now includes Remove Book

        switch (choice) {
            case 1:
                displayAllBooks();
                pauseScreen();
                break;
            case 2:
                searchBook();
                pauseScreen();
                break;
            case 3:
                addBook();
                pauseScreen();
                break;
            case 4:
                updateBookQuantity();
                pauseScreen();
                break;
            case 5:
                generateReport();   // already has its own internal pause
                break;
            case 6:
                memberManagementMenu();
                break;
            case 7:
                borrowingMenu();
                break;
            case 8:
                removeBook();
                pauseScreen();
                break;
        }
    } while (choice != 0);

    printf("\nGoodbye!\n");
    return 0;
}