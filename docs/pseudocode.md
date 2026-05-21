# Pseudocode – Library Management System (Group 5)

This file describes the core logic of the Library Management System in plain English.
All functions are grouped by module.

---

## 1. Main Program Flow (`main.c`)
BEGIN
// ----- Login -----
CALL displayWelcomeBanner()
attempts = 0
WHILE attempts < 3 DO
PROMPT "Username: "
READ username
PROMPT "Password: "
READ password (hidden with asterisks)

IF username == "admin" AND password == "lib123" THEN
PRINT "Login successful! Welcome, admin."
BREAK
ENDIF

attempts = attempts + 1
IF attempts < 3 THEN
PRINT "Incorrect credentials. Attempts remaining: ", (3 - attempts)
ENDIF
ENDWHILE

IF attempts == 3 THEN
PRINT "Too many failed attempts. Exiting system."
EXIT
ENDIF

// ----- Load data from files -----
CALL loadBooks()
CALL loadMembers()
CALL loadBorrows()

// ----- Main menu loop -----
LOOP
CALL displayMenu()
choice = CALL getValidChoice(0, 8)

SWITCH choice
CASE 1: CALL displayAllBooks()
CASE 2: CALL searchBook()
CASE 3: CALL addBook()
CASE 4: CALL updateBookQuantity()
CASE 5: CALL generateReport()
CASE 6: CALL memberManagementMenu() // sub‑menu
CASE 7: CALL borrowingMenu() // sub‑menu
CASE 8: CALL removeBook()
CASE 0: BREAK out of loop
ENDSWITCH

IF choice != 0 THEN
CALL pauseScreen() // wait for Enter before showing menu again
ENDIF
ENDLOOP

PRINT "Goodbye!"
END

---

## 2. Authentication Module (`auth.c`)
FUNCTION displayWelcomeBanner()
PRINT banner with "Divine Word University – Madang"
PRINT "ADMIN LOGIN ONLY!!!"
END

FUNCTION login()
// implemented directly in main flow (see above)
// returns 1 if successful, 0 otherwise
END

---

## 3. Book Management Module (`books.c`)

### 3.1 Display All Books
FUNCTION displayAllBooks()
IF totalBooks == 0 THEN
PRINT "No books in the inventory."
RETURN
ENDIF

FOR i = 0 TO totalBooks - 1 DO
PRINT "Book ", (i+1), " of ", totalBooks
PRINT "ID : ", books[i].bookID
PRINT "Title : ", books[i].title
PRINT "Author : ", books[i].author
PRINT "Genre : ", books[i].genre
PRINT "Year : ", books[i].yearPublished
PRINT "Qty : ", books[i].quantity
PRINT "Status : ", (books[i].available > 0 ? "Available" : "Checked Out")
PRINT a separator line
ENDFOR

PRINT "Total books in inventory: ", totalBooks
END

### 3.2 Search Book
FUNCTION searchBook()
PROMPT "Enter title or author to search: "
READ keyword

found = 0
FOR each book in books DO
IF book.title contains keyword OR book.author contains keyword THEN
PRINT book details (same format as display)
found = found + 1
ENDIF
ENDFOR

IF found == 0 THEN
PRINT "No books found matching '", keyword, "'."
ELSE
PRINT found, " match(es) found."
ENDIF
END

### 3.3 Add a New Book
FUNCTION addBook()
PROMPT "Enter Book ID : "
READ newID

IF book with newID already exists THEN
PRINT "A book with this ID already exists."
RETURN
ENDIF

PROMPT "Enter Title : " → READ title
PROMPT "Enter Author : " → READ author
PROMPT "Enter Genre : " → READ genre
PROMPT "Enter Year : " → READ year
PROMPT "Enter Quantity : " → READ qty

books[totalBooks].bookID = newID
books[totalBooks].title = title
books[totalBooks].author = author
books[totalBooks].genre = genre
books[totalBooks].yearPublished = year
books[totalBooks].quantity = qty
books[totalBooks].available = qty

totalBooks = totalBooks + 1
CALL saveBooks()
PRINT "Book added successfully!"
PRINT "Total books in system: ", totalBooks
END

### 3.4 Update Book Quantity
FUNCTION updateBookQuantity()
PROMPT "Book ID: " → READ id
PROMPT "New Qty: " → READ newQty

FIND index of book with given ID
IF index == -1 THEN
PRINT "Book not found."
RETURN
ENDIF

books[index].quantity = newQty
books[index].available = newQty
CALL saveBooks()
PRINT "Quantity updated successfully for '", books[index].title, "'."
END

### 3.5 Remove a Book
FUNCTION removeBook()
PROMPT "Enter Book ID to remove: " → READ id

FIND index of book
IF index == -1 THEN
PRINT "Book not found."
RETURN
ENDIF

PRINT "Are you sure you want to delete '", books[index].title, "'? (y/n): "
READ confirm

IF confirm == 'y' OR confirm == 'Y' THEN
SHIFT all books from index+1 to totalBooks-1 one position left
totalBooks = totalBooks - 1
CALL saveBooks()
PRINT "Book removed successfully."
PRINT "Total books in system: ", totalBooks
ELSE
PRINT "Deletion cancelled."
ENDIF
END

---

## 4. Member Management Module (`members.c`)

### 4.1 Register a New Member
FUNCTION registerMember()
IF totalMembers >= MAX_MEMBERS THEN
PRINT "Cannot add member – system is full."
RETURN
ENDIF

PROMPT "Enter Member ID : " → READ id
PROMPT "Enter Name : " → READ name
PROMPT "Enter Email : " → READ email
PROMPT "Enter Phone : " → READ phone

// (ID is assumed unique; check for duplicates could be added)

members[totalMembers].memberID = id
members[totalMembers].name = name
members[totalMembers].email = email
members[totalMembers].phone = phone

totalMembers = totalMembers + 1
CALL saveMembers()
PRINT "Member registered successfully! (ID: ", id, ")"
END

### 4.2 View Member Details
FUNCTION viewMemberDetails()
PROMPT "ID: " → READ id

FIND index of member
IF index == -1 THEN
PRINT "Member not found."
RETURN
ENDIF

PRINT "Name : ", members[index].name
PRINT "Email : ", members[index].email
PRINT "Phone : ", members[index].phone
END

### 4.3 Update Member Information (email & phone)
FUNCTION updateMemberInfo()
PROMPT "Enter Member ID: " → READ id

FIND index of member
IF index == -1 THEN
PRINT "Member not found."
RETURN
ENDIF

PRINT "Current email : ", members[index].email
PROMPT "New Email (press Enter to keep current): " → READ newEmail
IF newEmail is not empty THEN
members[index].email = newEmail
ENDIF

PRINT "Current phone : ", members[index].phone
PROMPT "New Phone (press Enter to keep current): " → READ newPhone
IF newPhone is not empty THEN
members[index].phone = newPhone
ENDIF

CALL saveMembers()
PRINT "Contact information updated successfully."
END

---

## 5. Borrowing Module (`borrowing.c`)

### 5.1 Issue a Book
FUNCTION issueBook()
PROMPT "Member ID: " → READ memberID
PROMPT "Book ID: " → READ bookID

FIND book index
IF book not found OR book.available <= 0 THEN
PRINT "Unavailable"
RETURN
ENDIF

FIND member index
IF member not found THEN
PRINT "Member not found"
RETURN
ENDIF

borrows[totalBorrows].recordID = totalBorrows + 1
borrows[totalBorrows].memberID = memberID
borrows[totalBorrows].bookID = bookID

// Get today's date as YYYY-MM-DD
borrows[totalBorrows].borrowDate = current date string
borrows[totalBorrows].returnDate = "" // empty
borrows[totalBorrows].status = "Borrowed"

totalBorrows = totalBorrows + 1
book.available = book.available - 1

CALL saveBorrows()
CALL saveBooks()
PRINT "Book issued successfully."
END

### 5.2 Return a Book
FUNCTION returnBook()
PROMPT "Record ID: " → READ recordID

FOR each record in borrows DO
IF record.recordID == recordID AND record.status == "Borrowed" THEN
record.status = "Returned"
record.returnDate = current date string

FIND book associated with record
IF book.available < book.quantity THEN
book.available = book.available + 1
ENDIF

CALL saveBorrows()
CALL saveBooks()
PRINT "Book returned successfully."
RETURN
ENDIF
ENDFOR

PRINT "Record not found or already returned."
END

### 5.3 View Borrowing History
FUNCTION viewBorrowHistory()
IF totalBorrows == 0 THEN
PRINT "No borrowing records."
RETURN
ENDIF

FOR each record in borrows DO
LOOKUP book title using record.bookID
PRINT "Record #", record.recordID
PRINT "Book : ", bookTitle, " (ID: ", record.bookID, ")"
PRINT "Member ID: ", record.memberID
PRINT "Borrowed : ", record.borrowDate
PRINT "Returned : ", (record.returnDate is empty ? "Not yet" : record.returnDate)
PRINT "Status : ", record.status
PRINT separator
ENDFOR

PRINT "Total: ", totalBorrows, " record(s)"
END

---

## 6. File Handling & Report Generation (`filehandling.c`)

### 6.1 Load / Save Functions (high‑level)
FUNCTION loadBooks()
OPEN "books.txt" for reading
IF file not found → RETURN

WHILE read a line successfully (ID, Title, Author, Genre, Year, Qty)
books[totalBooks].bookID = ID
books[totalBooks].title = Title
books[totalBooks].author = Author
books[totalBooks].genre = Genre
books[totalBooks].yearPublished = Year
books[totalBooks].quantity = Qty
books[totalBooks].available = Qty // all copies initially available
totalBooks = totalBooks + 1
ENDWHILE

CLOSE file
END

FUNCTION saveBooks()
OPEN "books.txt" for writing
FOR each book in books DO
WRITE ID, Title, Author, Genre, Year, Qty (comma‑separated, no header)
ENDFOR
CLOSE file
END

FUNCTION loadMembers()
OPEN "members.txt"
IF file not found → RETURN
SKIP first line (header)
WHILE read ID, Name, Email, Phone
members[totalMembers].memberID = ID
members[totalMembers].name = Name
members[totalMembers].email = Email
members[totalMembers].phone = Phone
totalMembers = totalMembers + 1
ENDWHILE
CLOSE file
END

FUNCTION saveMembers()
OPEN "members.txt" for writing
WRITE header line: "MembersID,MembersName,MembersEmail,MembersPhone"
FOR each member DO
WRITE ID, Name, Email, Phone
ENDFOR
CLOSE file
END

FUNCTION loadBorrows() ... saveBorrows() // similar to members, with their own header

### 6.2 Generate Inventory Report
FUNCTION generateReport()
OPEN "inventory_report.txt" for writing
IF file cannot be created THEN
PRINT error and RETURN
ENDIF

WRITE report header (title, timestamp)
WRITE total books, total members, total borrow records

WRITE "Book Details" section
FOR each book DO
WRITE "BookID: ", bookID
WRITE "Title: ", title
WRITE "Author: ", author
WRITE "Genre: ", genre
WRITE "Year Published: ", year
WRITE "Quantity: ", quantity
WRITE "Availability Status: ", (available > 0 ? "Available" : "Checked Out")
WRITE separator
ENDFOR

WRITE "Borrowing Summary" section
FOR each borrow record DO
FIND corresponding book title and member name
WRITE borrow ID, book ID, book title, member ID, member name, dates, status
WRITE separator
ENDFOR

WRITE "END OF REPORT"
CLOSE file

PRINT "Inventory report generated successfully!"
WAIT for Enter key
END

---

*All pseudocode matches the actual implementation of the IS301 Library Management System.*