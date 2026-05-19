#include <stdio.h>
#include <string.h>
#include "library.h"
#include "books.h"
#include "filehandling.h"

int findBookIndexByID(int id) {
    for (int i = 0; i < totalBooks; i++)
        if (books[i].bookID == id) return i;
    return -1;
}

/* =================================================
   FUNCTION: displayAllBooks
   Purpose : Lists all books with full details
            in a block format.
   ================================================= */
void displayAllBooks(void) {
    if (totalBooks == 0) {
        printf("\n  No books in the inventory.\n");
        return;
    }

    for (int i = 0; i < totalBooks; i++) {
        printf("\n  Book %d of %d\n", i + 1, totalBooks);
        printf("  ID     : %d\n",   books[i].bookID);
        printf("  Title  : %s\n",   books[i].title);
        printf("  Author : %s\n",   books[i].author);
        printf("  Genre  : %s\n",   books[i].genre);
        printf("  Year   : %d\n",   books[i].yearPublished);
        printf("  Qty    : %d\n",   books[i].quantity);
        printf("  Status : %s\n",   (books[i].available > 0) ? "Available" : "Checked Out");
        printf("  ..............................\n");
    }

    printf("\n  Total books in inventory: %d\n", totalBooks);
}

/* =================================================
   FUNCTION: searchBook
   Purpose : Search for books by title or author
            keyword. Displays full details for
            each match in a block format.
   ================================================= */
void searchBook(void) {
    char key[100];
    int found = 0;

    printf("  Enter title or author to search: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("\n  Search results for: \"%s\"\n", key);
    printf("  ..............................\n");

    for (int i = 0; i < totalBooks; i++) {
        if (strstr(books[i].title, key) || strstr(books[i].author, key)) {
            found++;
            printf("  ID     : %d\n",   books[i].bookID);
            printf("  Title  : %s\n",   books[i].title);
            printf("  Author : %s\n",   books[i].author);
            printf("  Genre  : %s\n",   books[i].genre);
            printf("  Year   : %d\n",   books[i].yearPublished);
            printf("  Qty    : %d\n",   books[i].quantity);
            printf("  Status : %s\n",   (books[i].available > 0) ? "Available" : "Checked Out");
            printf("  ..............................\n");
        }
    }

    if (found == 0)
        printf("\n  No books found matching \"%s\".\n", key);
    else
        printf("\n  %d match(es) found.\n", found);
}

/* =================================================
   FUNCTION: addBook
   Purpose : Adds a new book to the inventory,
            saves to file, and prints a clean
            success message with updated count.
   ================================================= */
void addBook(void) {
    Book b;

    printf("\n  ---- Add New Book ----\n");
    printf("  Enter Book ID     : ");
    scanf("%d", &b.bookID);
getchar();   // consume newline immediately

if (findBookIndexByID(b.bookID) != -1) {
    printf("\n  A book with this ID already exists.\n");
    return;
}

    printf("  Enter Title       : ");
    fgets(b.title, MAX_TITLE, stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("  Enter Author      : ");
    fgets(b.author, MAX_AUTHOR, stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    printf("  Enter Genre       : ");
    fgets(b.genre, MAX_GENRE, stdin);
    b.genre[strcspn(b.genre, "\n")] = 0;

    printf("  Enter Year        : ");
    scanf("%d", &b.yearPublished);

    printf("  Enter Quantity    : ");
    scanf("%d", &b.quantity);
    getchar();

    b.available = b.quantity;
    books[totalBooks++] = b;
    saveBooks();

    printf("\n  Book added successfully!\n");
    printf("  Total books in system: %d\n", totalBooks);
    printf("  Books saved successfully!\n");
}

void updateBookQuantity(void) {
    int id, qty;
    printf("Book ID: ");
    scanf("%d", &id);
    printf("New Qty: ");
    scanf("%d", &qty);
    getchar();

    int idx = findBookIndexByID(id);
    if (idx != -1) {
        books[idx].quantity = qty;
        books[idx].available = qty;
        saveBooks();
        printf("\n  Quantity updated successfully for '%s'.\n", books[idx].title);
    } else {
        printf("\n  Book not found.\n");
    }
}

void removeBook(void) {
    int id;
    printf("  Enter Book ID to remove: ");
    scanf("%d", &id);
    getchar();

    int idx = findBookIndexByID(id);
    if (idx == -1) {
        printf("\n  Book not found.\n");
        return;
    }

    // Confirm deletion
    char confirm;
    printf("  Are you sure you want to delete '%s'? (y/n): ", books[idx].title);
    scanf("%c", &confirm);
    getchar();

    if (confirm == 'y' || confirm == 'Y') {
        // Shift all subsequent books left
        for (int i = idx; i < totalBooks - 1; i++) {
            books[i] = books[i + 1];
        }
        totalBooks--;
        saveBooks();
        printf("\n  Book removed successfully.\n");
        printf("  Total books in system: %d\n", totalBooks);
    } else {
        printf("\n  Deletion cancelled.\n");
    }
}