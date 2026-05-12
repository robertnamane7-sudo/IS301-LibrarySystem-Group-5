/*
 * auth.h  -  Authentication Header File
 * IS301 Library Management System
 *
 * Description:
 * Defines constants and function prototypes for
 * user authentication and system access control.
 */

#ifndef AUTH_H
#define AUTH_H

/* =================================================
   LOGIN CONFIGURATION
   ================================================= */

/* Default administrator credentials */
#define ADMIN_USERNAME       "admin"
#define ADMIN_PASSWORD       "lib123"

/* Maximum number of login attempts allowed */
#define MAX_LOGIN_ATTEMPTS   3


/* =================================================
   INPUT BUFFER SIZES
   ================================================= */

/* Maximum length for username and password */
#define MAX_USERNAME         50
#define MAX_PASSWORD         50


/* =================================================
   FUNCTION PROTOTYPES
   ================================================= */

/*
 * Function: displayWelcomeBanner
 * Purpose : Displays system welcome banner
 */
void displayWelcomeBanner(void);


/*
 * Function: login
 * Purpose : Prompts user for credentials and
 *           validates login access
 * Returns : 1 if successful, 0 if failed
 */
int login(void);

#endif /* AUTH_H */