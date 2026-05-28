# IS301 Library Management System – User Manual

**Divine Word University – Madang Campus**  
**Group 5 – K.B Warriors**

---

## Table of Contents
1. System Requirements
2. Installation & Running the Program
3. Login
4. Main Menu Overview
5. Feature Walkthroughs
   - 5.1 Display All Books
   - 5.2 Search for a Book
   - 5.3 Add a New Book
   - 5.4 Update Book Quantity
   - 5.5 Generate Inventory Report
   - 5.6 Members Management
   - 5.7 Borrowing Records
   - 5.8 Remove Book
6. Data Files
7. Troubleshooting
8. Exiting the System

---

## 1. System Requirements

| Requirement | Details |
|-------------|---------|
| Operating System | Windows 10 / 11 |
| Compiler (if building from source) | MinGW‑GCC 6.3.0 or similar |
| Executable (if available) | `library.exe` – no compiler needed |
| Other files | `books.txt`, `members.txt` must be in the same folder |

---

## 2. Installation & Running the Program

### Using the ready‑to‑run executable
- Double‑click `library.exe` **or** open a terminal in the program folder and type:

.\library.exe

### Compiling from source
1. Open a terminal in the folder containing all `.c` and `.h` files.
2. Run the command:

gcc -o library.exe *.c

3. If no errors appear, start the program:

.\library.exe

---

## 3. Login

When the program starts, a welcome banner is shown.  
Log in with the built‑in administrator account:

| Username | Password |
|----------|----------|
| `admin`  | `lib123` |

- When typing the password, `******` is displayed instead of the actual characters.
- You have **3 attempts**. After three incorrect tries the system closes automatically.

---

## 4. Main Menu Overview

After logging in, the main menu appears:

===== LIBRARY MANAGEMENT SYSTEM =====

Display Books

Search Book

Add Book

Update Quantity

Generate Report

Members Management

Borrowing

Remove Book

Exit
Choice:


- Type a number (0‑8) and press **Enter**.
- After most actions, press **Enter** to return to the menu.
- Only numbers in the range 0‑8 are accepted; invalid input shows an error.

---

## 5. Feature Walkthroughs

### 5.1 Display All Books (Option 1)
Shows every book in the inventory with its:
- ID, Title, Author, Genre, Year, Quantity, and Availability Status (`Available` / `Checked Out`).

### 5.2 Search for a Book (Option 2)
1. Type a keyword (part of the title or author’s name).
2. All matching books are displayed with full details.

**Note:** The search is **case‑sensitive** – `John` works, `john` does not.  
If no books match, the message *“No books found matching …”* appears.

### 5.3 Add a New Book (Option 3)
1. Enter a **unique** Book ID (number).
2. Provide the Title, Author, Genre, Year, and Quantity when asked.
3. A confirmation message appears, and the new book is saved to `books.txt`.

**Note:** If the Book ID already exists, the addition is cancelled with a warning.

### 5.4 Update Book Quantity (Option 4)
1. Enter the Book ID you want to change.
2. Type the new total quantity.
3. The system updates both the total and available copies.  
   If the ID is not found, *“Book not found.”* is displayed.

### 5.5 Generate Inventory Report (Option 5)
- Creates a file named `inventory_report.txt` in the program folder.
- A confirmation message appears on screen. Press **Enter** to continue.
- Open the file with any text editor to see the complete report, including book details and borrowing summary.

### 5.6 Members Management (Option 6)
Press **6** to open the Members sub‑menu:

--- MEMBERS MANAGEMENT ---

View Details

Register New Member

Update Information

Back


- **1. View Details** – Enter a Member ID to see the member’s name, email, and phone number.
- **2. Register New Member** – Enter a new Member ID, Name, Email, and Phone. The member is saved immediately to `members.txt`.
- **3. Update Information** – Enter a Member ID. You can change the email and/or phone number. (Press **Enter** to keep a current value.) The member’s name stays unchanged.
- **4. Back** – Returns to the main menu.

### 5.7 Borrowing Records (Option 7)
Press **7** to open the Borrowing sub‑menu:

--- BORROWING ---

Issue

Return

History

Back


- **1. Issue** – Enter the Member ID and the Book ID. The book’s available quantity decreases by 1.  
  *“Unavailable”* is shown if the book is out of stock, and *“Member not found”* if the member ID doesn’t exist.
- **2. Return** – Enter the **Record ID** (get it from the History). The book’s quantity increases by 1.  
  If the record is not found or already returned, *“Record not found or already returned.”* appears.
- **3. History** – Displays all borrowing records, including Book Title, Member ID, Borrow Date, Return Date, and Status.
- **4. Back** – Returns to the main menu.

### 5.8 Remove a Book (Option 8)
1. Enter the Book ID to delete.
2. Confirm with `y` (yes) or cancel with `n`.
3. On confirmation, the book is permanently removed and a message shows the new total.

---

## 6. Data Files

The system uses these files, all stored next to the executable:

| File | Purpose | Format |
|------|---------|--------|
| `books.txt` | Book inventory | `BookID,Title,Author,Genre,YearPublished,Quantity` (no header) |
| `members.txt` | Member records | Header row: `MembersID,MembersName,MembersEmail,MembersPhone`, then one line per member |
| `borrows.txt` | Borrowing records | Header row: `RecordID,MemberID,BookID,BorrowDate,ReturnDate,Status`, then one line per record |
| `inventory_report.txt` | Generated report | Human‑readable; created when you choose Option 5 |

- Do **not** edit these files while the program is running.
- `borrows.txt` is created automatically when you first issue a book.

---

## 7. Troubleshooting

| Problem | Solution |
|---------|----------|
| Menu options missing (e.g. no Remove Book) | Re‑compile or get the latest version of the program. |
| Search finds nothing even though the book exists | The search is case‑sensitive – use correct capitalisation (e.g., `John`, not `john`). |
| “A book with this ID already exists” when adding | Choose a different Book ID. |
| “Book not found” when updating or removing | Check the book list (Option 1) for the correct ID. |
| “Unavailable” when issuing a book | The book is out of stock – pick another one. |
| “Member not found” when issuing | Use Members Management → View Details to find a valid Member ID. |
| “Record not found or already returned” when returning | Check the borrowing history for the correct Record ID. |
| Report file is empty or says “No books in inventory” | Add books first, then generate the report again. |
| Program crashes after typing letters instead of numbers | Restart and only enter digits when IDs, years, or quantities are asked. |

---

## 8. Exiting the System

- Choose **0. Exit** from the main menu.
- A goodbye message is displayed, and the program closes.
- **Do not** close the console window with the × button; always use **Exit** to make sure all changes are saved.

---

*For more details on design, testing, and implementation, please refer to the Project Report.*
