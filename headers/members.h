/* =====================================================
 * members.h
 * Header for member management functions
 * Member 3: Eau / Member 4: Ruhama
 * ===================================================== */

#ifndef MEMBERS_H
#define MEMBERS_H

#include "library.h"

extern struct Member members[];
extern int totalMembers;

/* Function declarations */
void displayAllMembers(void);
void registerMember(void);

#endif