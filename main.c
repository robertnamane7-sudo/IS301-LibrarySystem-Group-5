#include <stdio.h>
#include "auth.h"
#include "books.h"
#include "members.h"
#include "borrowing.h"
#include "filehandling.h"

int main() {
    int choice;

    if (!login()) {
        printf("Access denied.\n");
        return 0;
    }

    loadBooksFromFile("books.txt");
    loadMembersFromFile("members.txt");

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayAllBooks(); break;
            case 2: searchBook(); break;
            case 3: addBook(); break;
            case 4: updateQuantity(); break;
            case 5: registerMember(); break;
            case 6: viewMembers(); break;
            case 7: issueBook(); break;
            case 8: returnBook(); break;
            case 9: generateInventoryReport("inventory_report.txt"); break;
        }

    } while (choice != 10);

    return 0;
}
