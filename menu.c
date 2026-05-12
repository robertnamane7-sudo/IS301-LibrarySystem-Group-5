#include <stdio.h>
#include "menu.h"
#include "books.h"
#include "members.h"
#include "borrowing.h"
#include "library.h"

int getValidChoice(int min, int max) {
    int choice;
    while (scanf("%d", &choice) != 1 || choice < min || choice > max) {
        while (getchar() != '\n');
        printf("Enter valid choice: ");
    }
    getchar();
    return choice;
}

void displayMenu(void) {
    printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Display Books\n");
    printf("2. Search Book\n");
    printf("3. Add Book\n");
    printf("4. Update Quantity\n");
    printf("5. Generate Report\n");
    printf("6. Members Management\n");
    printf("7. Borrowing\n");
    printf("8. Remove Book\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

void memberManagementMenu(void) {
    int choice;
    do {
        printf("\n--- MEMBERS MANAGEMENT ---\n");
        printf("1. View Details\n");
        printf("2. Register New Member\n");
        printf("3. Update Information\n");
        printf("4. Back\n");
        printf("Choice: ");
        choice = getValidChoice(1, 4);

        switch (choice) {
            case 1: viewMemberDetails(); break;   // View details of a specific member
            case 2: registerMember();   break;   // Register a new member
            case 3: updateMemberInfo();  break;   // Update a member's details
            // case 4 simply exits the loop
        }
        if (choice != 4) {
            pauseScreen();
        }
    } while (choice != 4);
}

void borrowingMenu(void) {
    int choice;
    do {
        printf("\n--- BORROWING ---\n");
        printf("1. Issue\n2. Return\n3. History\n4. Back\n");
        printf("Choice: ");
        choice = getValidChoice(1, 4);

        switch (choice) {
            case 1: issueBook(); break;
            case 2: returnBook(); break;
            case 3: viewBorrowHistory(); break;
        }
        // Pause after any action except Back
        if (choice != 4) {
            pauseScreen();
        }
    } while (choice != 4);
}
