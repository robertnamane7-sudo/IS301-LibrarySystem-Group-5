/* =====================================================
 * menu.c
 * Menu display and input validation functions
 * Member 5: Jasmine
 * ===================================================== */

#include <stdio.h>
#include "menu.h"

/* -------------------------------------------------------
 * displayMenu()
 * Shows the main menu options on screen
 * ------------------------------------------------------- */
void displayMenu(void) {

    printf("\n========================================\n");
    printf("     LIBRARY MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("  1. Display All Books\n");
    printf("  2. Search for a Book\n");
    printf("  3. Add a New Book\n");
    printf("  4. Update Book Quantity\n");
    printf("  5. Generate Inventory Report\n");
    printf("  6. Manage Members\n");
    printf("  7. Borrowing Records\n");
    printf("  0. Exit\n");
    printf("========================================\n");
    printf("  Enter your choice: ");
}

/* -------------------------------------------------------
 * getValidChoice()
 * Validates user input - only accepts numbers in range
 * ------------------------------------------------------- */
int getValidChoice(int min, int max) {

    int choice;
    int valid;

    do {
        valid = scanf("%d", &choice);

        if (valid != 1) {
            while (getchar() != '\n');
            printf("  Invalid input. Please enter a number: ");
        }
        else if (choice < min || choice > max) {
            printf("  Please enter a number between %d and %d: ", min, max);
        }

    } while (valid != 1 || choice < min || choice > max);

    return choice;
}