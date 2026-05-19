#include <stdio.h>
#include <string.h>
#include "library.h"
#include "members.h"
#include "filehandling.h"

int findMemberIndexByID(int id) {
    for (int i = 0; i < totalMembers; i++)
        if (members[i].memberID == id)
            return i;
    return -1;
}

void displayAllMembers(void) {
    if (totalMembers == 0) {
        printf("\n  No members registered.\n");
        return;
    }

    printf("\n  --- All Members ---\n");
    for (int i = 0; i < totalMembers; i++) {
        printf("  %d | %s | %s | %s\n",
               members[i].memberID,
               members[i].name,
               members[i].email,
               members[i].phone);
    }
    printf("  Total: %d member(s)\n", totalMembers);
}

void registerMember(void) {
    if (totalMembers >= MAX_MEMBERS) {
        printf("\n  Cannot add member – system is full.\n");
        return;
    }

    Member m;

    printf("\n  ---- Register New Member ----\n");
    printf("  Enter Member ID : ");
    scanf("%d", &m.memberID);
    getchar();

    printf("  Enter Name      : ");
    fgets(m.name, MAX_NAME, stdin);
    m.name[strcspn(m.name, "\n")] = '\0';

    printf("  Enter Email     : ");
    fgets(m.email, MAX_EMAIL, stdin);
    m.email[strcspn(m.email, "\n")] = '\0';

    printf("  Enter Phone     : ");
    fgets(m.phone, MAX_PHONE, stdin);
    m.phone[strcspn(m.phone, "\n")] = '\0';

    members[totalMembers] = m;
    totalMembers++;

    saveMembers();

    printf("\n  Member registered successfully! (ID: %d)\n", m.memberID);
}

void viewMemberDetails(void) {
    int id;
    printf("ID: ");
    scanf("%d", &id);
    getchar();

    int idx = findMemberIndexByID(id);
    if (idx != -1) {
        printf("\n  Name  : %s\n", members[idx].name);
        printf("  Email : %s\n", members[idx].email);
        printf("  Phone : %s\n", members[idx].phone);
    } else {
        printf("\n  Member not found.\n");
    }
}

void updateMemberInfo(void) {
    int id;
    printf("Enter Member ID: ");
    scanf("%d", &id);
    getchar();

    int idx = findMemberIndexByID(id);
    if (idx == -1) {
        printf("\n  Member not found.\n");
        return;
    }

    // Show current details (name is permanent, so we only show it)
    printf("\n  Updating contact details for: %s\n", members[idx].name);
    printf("  Current email : %s\n", members[idx].email);
    printf("  Current phone : %s\n", members[idx].phone);

    // Update email (press Enter to keep current)
    char input[MAX_EMAIL];   // MAX_EMAIL is larger than MAX_PHONE, safe to reuse
    printf("\n  New Email (press Enter to keep current): ");
    fgets(input, MAX_EMAIL, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        strcpy(members[idx].email, input);
    }

    // Update phone (press Enter to keep current)
    printf("  New Phone (press Enter to keep current): ");
    fgets(input, MAX_PHONE, stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) > 0) {
        strcpy(members[idx].phone, input);
    }

    saveMembers();
    printf("\n  Contact information updated successfully.\n");
}