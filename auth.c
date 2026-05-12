/*
 * auth.c  -  Authentication Module
 * IS301 Library Management System
 *
 * Description:
 * Handles administrator login and displays
 * the system welcome banner.
 */

#include <stdio.h>
#include <string.h>
#include <conio.h> //for getch()
#include "auth.h"

/* =================================================
   FUNCTION: displayWelcomeBanner
   Purpose : Displays system title banner
   ================================================= */
void displayWelcomeBanner(void) {
    printf("\n");
    printf("  ================================================\n");
    printf("       DIVINE WORD UNIVERSITY - MADANG\n");
    printf("       LIBRARY MANAGEMENT SYSTEM\n");
    printf("       ADMIN LOGIN ONLY!!!\n");
    printf("  ================================================\n\n");
}

/* =================================================
   FUNCTION: clearInputBuffer
   Purpose : Clears leftover input from buffer
   ================================================= */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* =================================================
   FUNCTION: readPassword
   Purpose : Reads a password without echoing
            characters to the screen.
   ================================================= */
void readPassword(char *buffer, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = getch();          // read a character without echo
        if (ch == '\r' || ch == '\n') {
            break;             // Enter key pressed
        } else if (ch == '\b') {  // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // erase the last '*'
            }
        } else {
            buffer[i++] = ch;
            printf("*");       // show an asterisk
        }
    }
    buffer[i] = '\0';
    printf("\n");
}

/* =================================================
   FUNCTION: login
   Purpose : Authenticates user credentials
   Returns : 1 = success, 0 = failure
   ================================================= */
int login(void) {

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int attempts = 0;

    displayWelcomeBanner();
    printf("  Enter Admin Credentials!\n");

    while (attempts < MAX_LOGIN_ATTEMPTS) {

        printf("\n  Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("  Password: ");
        readPassword(password, MAX_PASSWORD);

        if (strcmp(username, ADMIN_USERNAME) == 0 &&
            strcmp(password, ADMIN_PASSWORD) == 0) {

            printf("\n  Login successful! Welcome, %s.\n", username);
            return 1;
        }

        attempts++;

        if (attempts < MAX_LOGIN_ATTEMPTS) {
            printf("\n  Incorrect credentials. Attempts remaining: %d\n",
                   MAX_LOGIN_ATTEMPTS - attempts);
        }
    }

    printf("\n  Too many failed attempts. Exiting system.\n");
    return 0;
}