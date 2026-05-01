/* =====================================================
 * members.c
 * Member management functions
 * Member 3: Eau / Member 4: Ruhama
 * ===================================================== */

#include <stdio.h>
#include <string.h>
#include "members.h"
#include "filehandling.h"

/* -------------------------------------------------------
 * displayAllMembers()
 * Prints all members currently loaded in memory
 * ------------------------------------------------------- */
void displayAllMembers(void) {

    int i;

    if (totalMembers == 0) {
        printf("\n  No members found in the system.\n");
        return;
    }

    printf("\n========================================\n");
    printf("           ALL MEMBERS\n");
    printf("========================================\n");

    for (i = 0; i < totalMembers; i++) {
        printf("\n  Member %d of %d\n", i + 1, totalMembers);
        printf("  ID     : %d\n",  members[i].memberID);
        printf("  Name   : %s\n",  members[i].name);
        printf("  Email  : %s\n",  members[i].email);
        printf("  Phone  : %s\n",  members[i].phone);
        printf("  Status : %s\n",  members[i].status);
        printf("  ..............................\n");
    }
}

/* -------------------------------------------------------
 * registerMember()
 * Accepts input and adds a new member to the system
 * ------------------------------------------------------- */
void registerMember(void) {

    if (totalMembers >= MAX_MEMBERS) {
        printf("\n  System is full. Cannot add more members.\n");
        return;
    }

    while (getchar() != '\n');

    printf("\n========================================\n");
    printf("         REGISTER NEW MEMBER\n");
    printf("========================================\n");

    printf("  Enter Member ID  : ");
    scanf("%d", &members[totalMembers].memberID);
    while (getchar() != '\n');

    printf("  Enter Name       : ");
    fgets(members[totalMembers].name, 50, stdin);
    members[totalMembers].name[strcspn(members[totalMembers].name, "\n")] = 0;

    printf("  Enter Email      : ");
    fgets(members[totalMembers].email, 50, stdin);
    members[totalMembers].email[strcspn(members[totalMembers].email, "\n")] = 0;

    printf("  Enter Phone      : ");
    fgets(members[totalMembers].phone, 20, stdin);
    members[totalMembers].phone[strcspn(members[totalMembers].phone, "\n")] = 0;

    strcpy(members[totalMembers].status, "Active");
    totalMembers++;

    printf("\n  Member registered successfully!\n");
    printf("  Total members in system: %d\n", totalMembers);
    saveMembers();
}