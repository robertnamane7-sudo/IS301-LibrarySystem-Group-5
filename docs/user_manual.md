# IS301 Library Management System – User Manual

**Divine Word University – Madang Campus**  
**Group 5 – K.B Warriors**

---

## Table of Contents
1. Introduction
2. System Requirements
3. Installation / Compilation
4. Starting the System (Login)
5. Main Menu Overview
6. Feature Walkthroughs
    - 6.1 Display All Books
    - 6.2 Search for a Book
    - 6.3 Add a New Book
    - 6.4 Update Book Quantity
    - 6.5 Generate Inventory Report
    - 6.6 Members Management
    - 6.7 Borrowing Records
    - 6.8 Remove Book
7. Data Files
8. Error Handling & Troubleshooting
9. Exiting the System

---

## 1. Introduction

The Library Management System is a console-based application developed in the C programming language. It is designed to help library administrators manage books, members, and borrowing records efficiently from a simple text-based interface. This user manual provides step-by-step instructions for installing/compiling, running, and using all **eight (8)** features of the system.

### 1.1 Purpose
The system allows administrators to:
- Manage a collection of books including adding, removing, searching, and updating
- Register, view, and update library members
- Issue and return books with full borrowing history
- Generate a complete inventory report saved to a text file

### 1.2 System Features

| Menu | Feature | Description |
|------|---------|-------------|
| 1 | Display All Books | Lists all books with full details |
| 2 | Search for a Book | Search by title or author keyword |
| 3 | Add a New Book | Add a new book to the inventory |
| 4 | Update Book Quantity | Change the quantity of any book |
| 5 | Generate Inventory Report | Writes full report to `inventory_report.txt` |
| 6 | Members Management | View details, register new members, update contact info |
| 7 | Borrowing Records | Issue, return, and view borrowing history |
| 8 | Remove Book | Remove a book from the inventory permanently |
| 0 | Exit | Safely exit the system |

---

## 2. System Requirements

Before running the Library Management System, ensure your computer meets the following requirements:

| Requirement | Details |
|-------------|---------|
| Operating System | Windows 10/11 (or any system capable of running C console programs) |
| Required Software | **If using the provided executable:** No additional software needed.<br>**If compiling from source:** A C compiler such as MinGW‑GCC 6.3.0. |
| Optional Software | A text editor (e.g., Notepad) to view or edit the data files. |
| Data Files | The following files must be present in the same folder as the program:<br>`books.txt`, `members.txt`<br>`borrows.txt` will be created automatically when needed. |
| Storage | Minimal – less than 1 MB for the program and data files. |
| Dependencies | None – the program uses only libraries that come with MinGW‑GCC (standard C library + `conio.h` for password masking). |

---

## 3. Installation / Compilation

### 3.1 Folder Structure
LibraryManagementSystem/
├── docs/ user_manual.md, pseudocode.md, & flowchart
├── auth.c
├── auth.h
├── books.c
├── books.h
├── books.txt
├── borrowing.c
├── borrowing.h
├── borrows.txt (generated at first borrow)
├── filehandling.c
├── filehandling.h
├── inventory_report.txt (generated when report is requested)
├── library.h
├── main.c
├── members.c
├── members.h
├── members.txt
├── menu.c
└── menu.h

### 3.2 Compiling the Program
1. Open a terminal/command prompt in the folder containing all `.c` and `.h` files.
2. Run:  
   `gcc -o library.exe *.c`
3. Press **Enter**. No errors should appear.

### 3.3 Running the Program
After compilation, run the program by:
- Double‑clicking `library.exe`, **or**
- Typing `.\library.exe` in the terminal and pressing **Enter**.

---

## 4. Starting the System (Login)

When the program starts, a welcome banner is displayed showing:
**"Divine Word University – Madang"** and **"ADMIN LOGIN ONLY!!!"**

You will then be prompted to enter your administrator credentials.

| Field | Value |
|-------|-------|
| Username | `admin` |
| Password | `lib123` |
| Max attempts | 3 attempts before system exits |

When typing the password, asterisks (`******`) will appear instead of the actual characters, keeping your password hidden.

After three incorrect attempts the system will display:  
**"Too many failed attempts. Exiting system."**  
and close automatically for security.

---

## 5. Main Menu Overview

After a successful login, the main menu appears. It stays on screen after every action until you press **0** to exit.

**NOTE:** Only numbers **0 through 8** are accepted. Letters or numbers outside this range will show an error message and ask again.

| Option | Description |
|--------|-------------|
| 1. Display Books | Shows all books with full details |
| 2. Search Book | Search by title or author keyword |
| 3. Add Book | Enter details to add a new book |
| 4. Update Quantity | Change the total quantity of a book by ID |
| 5. Generate Report | Creates `inventory_report.txt` with full inventory and borrowing summary |
| 6. Members Management | Opens the Member Management sub‑menu |
| 7. Borrowing | Opens the Borrowing sub‑menu (issue, return, history) |
| 8. Remove Book | Remove a book from the inventory permanently |
| 0. Exit | Saves all data and closes the program |

---

## 6. Feature Walkthroughs

### 6.1 Display All Books (Option 1)
1. From the main menu, press **1** and **Enter**.
2. All books are displayed one by one with full details (ID, title, author, genre, year, quantity, availability).
3. Press **Enter** to return to the main menu.

**NOTE:** Status shows **Available** when quantity is greater than 0, and **Checked Out** when quantity is 0.

### 6.2 Search for a Book (Option 2)
1. Press **2** from the main menu.
2. Type a keyword – this can be part of a title or part of an author name.
3. Press **Enter** to see all matching results.

**NOTE:** The search is case‑sensitive. Type `John` not `john` for best results. If no books match, the message **"No books found matching …"** appears.

### 6.3 Add a New Book (Option 3)
1. Press **3** from the main menu.
2. Enter a **unique** Book ID.
3. Enter the Title, Author, Genre, Year, and Quantity as prompted.
4. A confirmation message shows the new total, and the book is saved to `books.txt`.

**NOTE:** If the Book ID already exists, the message **"A book with this ID already exists."** appears and the addition is cancelled.

### 6.4 Update Book Quantity (Option 4)
1. Press **4** from the main menu.
2. Enter the Book ID you wish to update.
3. Enter the new total quantity.
4. The system updates the quantity and availability. If the ID does not exist, the message **"Book not found."** appears.

**NOTE:** Setting the quantity to 0 changes the status to **Checked Out**. Setting it above 0 changes it back to **Available**.

### 6.5 Generate Inventory Report (Option 5)
1. Press **5** from the main menu.
2. The report is generated as `inventory_report.txt` in the same folder.
3. A confirmation message appears on the screen. Press **Enter** to continue.
4. Open `inventory_report.txt` with any text editor to view the full report, which includes:
   - Total number of books, members and borrow records
   - Full details of every book in the inventory
   - A complete borrowing summary with dates and status

### 6.6 Members Management (Option 6)
When you press **6** from the main menu, a sub‑menu appears:
--- MEMBERS MANAGEMENT ---

1.View Details

2.Register New Member

3.Update Information

4.Back


- **1. View Details** – Enter a Member ID to see the member’s name, email, and phone.
- **2. Register New Member** – Enter a new member’s ID, name, email, and phone. The member is saved automatically to `members.txt`.
- **3. Update Information** – Enter a Member ID. You can change the email and/or phone (press **Enter** to keep the current value). The member’s name remains unchanged.
- **4. Back** – Returns to the main menu.

### 6.7 Borrowing Records (Option 7)
Press **7** from the main menu to access the borrowing sub‑menu:
--- BORROWING ---

1.Issue

2.Return

3.History

4.Back


- **1. Issue a Book** – Enter the Member ID and Book ID. The system confirms the issue and reduces the available quantity by 1. If the book is unavailable, the message **"Unavailable"** appears. If the member does not exist, **"Member not found"** is displayed.
- **2. Return a Book** – Enter the Borrow Record ID (found in the history). The system marks the record as returned and increases the available quantity by 1. If the record is not found or already returned, the message **"Record not found or already returned."** appears.
- **3. View Borrow History** – Displays all borrowing records in a block format showing Record ID, Book Title, Member ID, Borrowed Date, Return Date (or “Not yet”), and Status.
- **4. Back** – Returns to the main menu.

### 6.8 Remove Book (Option 8)
1. Press **8** from the main menu.
2. Enter the Book ID you wish to remove.
3. Confirm the deletion by typing **y** (yes) or cancel with **n** (no).
4. On confirmation, the book is permanently removed and the new total is displayed.

---

## 7. Data Files

The Library System uses the following data files, all located in the same folder as the program executable. They are updated automatically when you add, remove, or modify records.

| File name | Purpose | Format |
|-----------|---------|--------|
| `books.txt` | Book inventory | Each line: `BookID,Title,Author,Genre,YearPublished,Quantity` (no header). |
| `members.txt` | Registered members | First line: `MembersID,MembersName,MembersEmail,MembersPhone` (header), then one line per member: `MemberID,Name,Email,Phone`. |
| `borrows.txt` | Borrowing records | First line: `RecordID,MemberID,BookID,BorrowDate,ReturnDate,Status` (header), then one line per record. |
| `inventory_report.txt` | Generated inventory report | A formatted, human‑readable report. Created fresh each time you choose **5. Generate Report**. |

**Important:**
- Do **not** manually edit any data file while the system is running.
- The `borrows.txt` file is automatically created when you first issue a book. If you delete it, the system will regenerate it on the next borrowing action.
- Always exit the system using the **0. Exit** option to ensure all changes are saved properly.

---

## 8. Error Handling & Troubleshooting

If you encounter problems while using the Library Management System, refer to the table below.

| Problem | Probable cause | Solution |
|---------|----------------|----------|
| After login, the main menu is missing some options (e.g., no Remove Book). | You are running an older version of the program. | Re‑compile all files or obtain the latest executable. |
| Search returns “No books found” even though the book exists. | The search is case‑sensitive. | Type the keyword exactly as it appears (e.g., “John” works; “john” does not). |
| When adding a book, a message says “A book with this ID already exists.” | The Book ID you entered is already in use. | Choose a different, unique Book ID. |
| When updating a book quantity, nothing seems to happen. | The Book ID you entered does not exist. | Use Display Books (Option 1) to verify the correct ID. |
| When removing a book, nothing happens after entering the Book ID. | The Book ID was not found. | Use Display Books to confirm the ID exists. |
| The program crashes after entering letters where a number is expected. | Invalid input type. | Restart the program and enter only numbers for IDs, year, and quantity. |
| When borrowing a book, the message “Unavailable” appears. | The book’s available quantity is zero (all copies are borrowed). | Check availability using Display Books (Option 1) and try a different book. |
| When borrowing a book, the message “Member not found” appears. | The Member ID you entered does not exist. | Use Members Management (Option 6) → View Details to find a valid Member ID. |
| When returning a book, the message “Record not found or already returned.” appears. | The Record ID is incorrect, or the book has already been returned. | Check the Borrowing History (Borrowing → History) for the correct Record ID. |
| The `inventory_report.txt` file is empty or contains “No books in inventory.” | No books were present when the report was generated. | Add books first, then generate the report again. |
| Menus appear garbled or prompts are skipped. | Leftover characters in the input buffer (rare). | Restart the program. The current version of the system includes buffer clearing to prevent this. |

For any other issues, please consult the project report.

---

## 9. Exiting the System

To close the Library Management System safely:
1. From the main menu, type **0** and press **Enter**.
2. A goodbye message (“Goodbye!”) will appear, and the program will close.
3. Do **not** close the console window by clicking the × button while the system is running, as this may result in unsaved changes to the data files.
4. All data (books, members, borrowing records) is saved automatically after each operation, but using the **Exit** option ensures a clean shutdown.