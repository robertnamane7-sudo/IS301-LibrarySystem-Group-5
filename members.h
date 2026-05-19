/*
 * members.h  -  Member Management Header File
 * IS301 Library Management System
 *
 * Description:
 * Contains function prototypes for managing library
 * members, including registration, display, update,
 * and search operations.
 */

#ifndef MEMBERS_H
#define MEMBERS_H

/* =================================================
   FUNCTION PROTOTYPES
   ================================================= */

/*
 * Function: displayAllMembers
 * Purpose : Displays all registered members
 */
void displayAllMembers(void);


/*
 * Function: registerMember
 * Purpose : Registers a new member in the system
 */
void registerMember(void);


/*
 * Function: viewMemberDetails
 * Purpose : Displays details of a specific member
 */
void viewMemberDetails(void);


/*
 * Function: updateMemberInfo
 * Purpose : Updates existing member information
 */
void updateMemberInfo(void);


/*
 * Function: findMemberIndexByID
 * Purpose : Finds a member's index using their ID
 * Parameter:
 *   id - Member ID (integer)
 * Returns:
 *   Index if found, otherwise -1
 */
int findMemberIndexByID(int id);

#endif /* MEMBERS_H */