#include <stdio.h>
#include <time.h>
#include <string.h>

// Display the main menu
void displayMainMenu()
{
    printf("Menu:\n");
    printf("1. Sign Up\n");
    printf("2. Sign In\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

// Define structures
struct Date {
    int dd;
    int mm;
    int yy;
};

struct User {
    char email[50];
    char password[50];
    char userType[20]; // Owner/Librarian/Member
};

struct Member {
    int memberId;
    char memberName[100];
    char email[50];
    char password[50];
    struct Date joinDate;
    int isPaidUser;
    float fineAmount;
};

struct Owner {
    char ownerName[100];
    char email[50];
    char password[50];
    char librarianEmail[50];
};

struct Librarian {
    char librarianName[100];
    char email[50];
};

struct Book {
    int bookId;
    char bookName[100];
    char author[100];
    int rackNumber;
    int totalCopies;
    int availableCopies;
    int bookPrice; 
};

struct Book availableBooks[] = {
    {1, "Book 1", 4},
    {2, "Book 2", 5},
    // Add more book entries as needed
};

// Function prototypes
void signUp();
void signIn();
void inputDate(struct Date *date);
void displayDate(struct Date date);
void addDays(struct Date *date, int days);
int compareDates(struct Date date1, struct Date date2);
void ownerMenu();
void librarianMenu();
void memberMenu();
void editProfileOwner(struct Owner *profile, struct User *currentUser);
void changePassword(struct User *user);
void editProfileLibrarian(struct Librarian *profile);
void addBook();
void addBookCopy();
void editProfileMember(struct Member *profile);
void findBook();
void editBook();
void changeRack();
void signUpMember();
void signInMember(struct Member *member);
void appointLibrarian(struct Owner *ownerProfile);
void displayAvailableBooks();
void addNewMember();
void generateMemberId();
void changePasswordForMember();
void ownerSignIn();


// Global variables
struct User currentUser;
struct Book books[100]; // Adjust the size as needed
int numBooks = 0;
static int memberIdCounter = 1000;


//SignUp
void signUp() {
    struct User newUser;

    printf("Enter owner email & password\n");
    
    printf("Enter an email: ");
    scanf("%s", newUser.email);
    printf("Enter a password: ");
    scanf("%s", newUser.password);

    strcpy(newUser.userType, "Owner"); // Set the user type to "Owner"

    // Save user data to a file
    FILE *userFile = fopen("users.txt", "a"); // Open the file in append mode
    if (userFile == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(userFile, "%s %s %s\n", newUser.email, newUser.password, newUser.userType);
    fclose(userFile);

    printf("Owner signed up successfully!\n");
}


//SignIn
void signIn(struct User *user) {
    char enteredEmail[50];
    char enteredPassword[50];

    printf("Enter your email: ");
    scanf("%s", enteredEmail);
    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct User currentUser;
    int signInSuccessful = 0; // Flag to indicate successful sign-in
    while (fscanf(userFile, "%s %s %s", currentUser.email, currentUser.password, currentUser.userType) != EOF) {
        if (strcmp(enteredEmail, currentUser.email) == 0 && strcmp(enteredPassword, currentUser.password) == 0) {
            signInSuccessful = 1; // Set the sign-in flag
            strcpy(user->email, currentUser.email); // Copy user data to the passed user pointer
            strcpy(user->password, currentUser.password);
            strcpy(user->userType, currentUser.userType);
            break;
        }
    }

    fclose(userFile);

    if (signInSuccessful) {
        printf("SignIn successful\n");
        if (strcmp(user->userType, "Owner") == 0) {
            ownerMenu();
        } else if (strcmp(user->userType, "Librarian") == 0) {
            librarianMenu();
        } else if (strcmp(user->userType, "Member") == 0) {
            memberMenu();
        } else {
            printf("Invalid user type.\n");
        }
    } else {
        printf("Invalid email or password.\n");
    }
}


// Sign Out Function
void signOut(struct User *user) {
    // Save a log entry indicating the sign-out event
    FILE *logFile = fopen("logout_log.txt", "a"); // Open the log file in append mode
    if (logFile == NULL) {
        printf("Error opening log file for writing.\n");
        return;
    }

    time_t currentTime;
    time(&currentTime);
    struct tm *timeInfo = localtime(&currentTime);

    fprintf(logFile, "User %s signed out at %s", user->email, asctime(timeInfo));
    fclose(logFile);

    // Reset user data to simulate signing out
    strcpy(user->email, "");
    strcpy(user->password, "");
    
    printf("Signed out successfully.\n");
}


// Function to change the password For Owner/Member/Librarian
void changePassword(struct User *user) {
    char newPassword[50];
    printf("Enter your new password: ");
    scanf("%s", newPassword);
    strcpy(user->password, newPassword);
    printf("Password changed successfully!\n");

    // Save the updated password to the file
    FILE *userFile = fopen("users.txt", "r+"); // Open the file in read and write mode
    if (userFile == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    char email[50], password[50], userType[50];
    long int pos = 0;
    while (fscanf(userFile, "%s %s %s", email, password, userType) != EOF) {
        if (strcmp(email, user->email) == 0) {
            fseek(userFile, pos, SEEK_SET); // Move the cursor to the beginning of the line
            fprintf(userFile, "%s %s %s\n", email, newPassword, userType);
            break;
        }
        pos = ftell(userFile); // Store the current position
    }

    fclose(userFile);
}


//OwnerMenu
void ownerMenu() {
    struct Owner ownerProfile; // Create an instance of OwnerProfile
    int choice;
    
    printf("Owner Menu:\n");
    printf("1. Sign Out\n");
    printf("2. Edit Profile\n");
    printf("3. Change Password\n");
    printf("4. Appoint Librarian\n");
    printf("5. Fees Report\n");
    printf("6. Fine Report\n");
    printf("7. Books Categories\n");
    printf("8. Books Available\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sign out
            signOut(&currentUser);
            break;
        case 2:
            // Edit Profile
            editProfileOwner(&ownerProfile, &currentUser);
            break;
        case 3:
            // Change Password
            changePassword(&currentUser);
            break;
        case 4:
            // Appoint Librarian
            appointLibrarian(&ownerProfile);
            break;
        case 5:
            // Fees Report
            printf("Generating fees report...\n");
            break;
        case 6:
            // Fine Report
            printf("Generating fine report...\n");
            break;
        case 7:
            // Books Categories
            printf("Displaying book categories...\n");
            break;
        case 8:
            // Books Available
            displayAvailableBooks();
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

// Function to edit owner profile
void editProfileOwner(struct Owner *profile, struct User *currentUser) {
    printf("Editing profile...\n");

    // Ask for the original email and password
    char enteredEmail[50];
    char enteredPassword[50];
    printf("Enter your original email: ");
    scanf("%s", enteredEmail);
    printf("Enter your original password: ");
    scanf("%s", enteredPassword);

    // Compare the entered original email and password with the current user's email and password
    if (strcmp(currentUser->email, enteredEmail) != 0 || strcmp(currentUser->password, enteredPassword) != 0) {
        printf("Original email or password does not match. Profile update aborted.\n");
        return;
    }

    printf("Enter your name: ");
    scanf("%s", profile->ownerName);

    printf("Enter your new email: "); // Prompt for the new email
    scanf("%s", profile->email);

    printf("Enter your new password: "); // Prompt for the new password
    scanf("%s", profile->password);

    // Update the current user's email and password
    strcpy(currentUser->email, profile->email); // Update the email in user information
    strcpy(currentUser->password, profile->password); // Update the password in user information

    // Save the updated profile to the owner profile file
    FILE *ownerFile = fopen("owner_profile.txt", "w");
    if (ownerFile == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(ownerFile, "%s %s %s\n", profile->ownerName, profile->email, profile->password);
    fclose(ownerFile);

    printf("Profile Updated Successfully.\n");
}


// Function to handle librarian sign-up
void librarianSignUp() {
    // Librarian Sign Up
    struct User librarianUser;
    printf("Librarian Sign Up:\n");
    printf("Enter librarian's email: ");
    scanf("%s", librarianUser.email);
    printf("Enter librarian's password: ");
    scanf("%s", librarianUser.password);
    strcpy(librarianUser.userType, "Librarian");

    // Save the sign-up details to a file
    FILE *userDataFile = fopen("user_data.txt", "a");
    if (userDataFile == NULL) {
        printf("Error opening user data file for sign-up.\n");
        return;
    }

    fprintf(userDataFile, "%s %s %s\n", librarianUser.email, librarianUser.password, librarianUser.userType);
    fclose(userDataFile);

    printf("Librarian signed up successfully!\n");
    signIn(&librarianUser); // Automatically sign in after sign-up
}


// Function to handle librarian sign-in
void librarianSignIn() {
    struct User librarianUser;
    printf("Librarian Sign In:\n");

    // Input librarian's email
    printf("Enter your email: ");
    scanf("%s", librarianUser.email);

    // Input librarian's password
    printf("Enter your password: ");
    scanf("%s", librarianUser.password);

    // Validate the sign-in details by reading from the user data file
    FILE *userDataFile = fopen("user_data.txt", "r");
    if (userDataFile == NULL) {
        printf("Error opening user data file for sign-in.\n");
        return;
    }

    int validSignIn = 0; // Flag to indicate valid sign-in
    char email[50], password[50], userType[50];
    while (fscanf(userDataFile, "%s %s %s", email, password, userType) != EOF) {
        if (strcmp(email, librarianUser.email) == 0 && strcmp(password, librarianUser.password) == 0 && strcmp(userType, "Librarian") == 0) {
            validSignIn = 1;
            break;
        }
    }

    fclose(userDataFile);

    if (validSignIn) {
        printf("Sign In successful\n");
        librarianMenu();
    } else {
        printf("Invalid email, password, or user type.\n");
    }
}


// Function to appoint a librarian
void appointLibrarian(struct Owner *ownerProfile) {
    printf("Appoint Librarian:\n");

    int choice;
    printf("1. Librarian Sign Up\n");
    printf("2. Librarian Sign In\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            librarianSignUp();
            break;
        case 2:
            librarianSignIn();
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

// Function to display available books
void displayAvailableBooks() {
    printf("Available Books:\n");
    printf("ID\tBook Name\tAvailable Copies\n");
    
    int numBooks = sizeof(availableBooks) / sizeof(availableBooks[0]);
    for (int i = 0; i < numBooks; i++) {
        printf("%d\t%s\t%d\n", availableBooks[i].bookId, availableBooks[i].bookName, availableBooks[i].availableCopies);
    }
}

//ownerSignIn
void ownerSignIn() {
    struct User ownerUser;

    printf("Enter your email: ");
    scanf("%s", ownerUser.email);

    printf("Enter your password: ");
    scanf("%s", ownerUser.password);

    FILE *ownerFile = fopen("owner_profile.txt", "r");
    if (ownerFile == NULL) {
        printf("Error opening owner profile file for sign-in.\n");
        return;
    }

    int validSignIn = 0; // Flag to indicate valid sign-in
    char email[50], password[50], userType[50];
    while (fscanf(ownerFile, "%s %s %s", email, password, userType) != EOF) {
        if (strcmp(email, ownerUser.email) == 0 && strcmp(password, ownerUser.password) == 0 && strcmp(userType, "Owner") == 0) {
            validSignIn = 1;
            break;
        }
    }

    fclose(ownerFile);

    if (validSignIn) {
        printf("Sign In successful\n");
        ownerMenu(); // Call the ownerMenu function
    } else {
        printf("Invalid email, password, or user type.\n");
    }
}



//LibrarianMenu
void librarianMenu() {
    struct Librarian librarianProfile;
    int choice;

    printf("Librarian Menu:\n");
    printf("1. Sign Out\n");
    printf("2. Edit Profile\n");
    printf("3. Change Password\n");
    printf("4. Return Copy\n");
    printf("5. Issue Copy\n");
    printf("6. Find Book\n");
    printf("7. Edit Book\n");
    printf("8. Add New Book\n");
    printf("9. Check Availability\n");
    printf("10. Add New Copy\n");
    printf("11. Change Rack\n");
    printf("12. Add New Member\n");
    printf("13. Take Payment\n");
    printf("14. Owner Menu\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sign out
            signOut(&currentUser);
            break;
        case 2:
            // Edit Profile
            editProfileLibrarian(&librarianProfile);
            break;
        case 3:
            // Change Password
            changePassword(&currentUser);
            break;
        case 4:
            // Return Copy
            printf("Returning a copy...\n");
            break;
        case 5:
            // Issue Copy
            printf("Issuing a copy...\n");
            break;
        case 6:
            // Find Book
            findBook();
            break;
        case 7:
            // Edit Book
            editBook();
            break;
        case 8:
            // Add New Book
            addBook();
            break;
        case 9:
            // Check Availability
            printf("Checking book availability...\n");
            break;
        case 10:
            // Add New Copy
            addBookCopy();
            break;
        case 11:
            // Change Rack
            changeRack();
            break;
        case 12:
            // Add New Member -> signUp
            addNewMember();
            break;
        case 13:
            // Take Payment
            printf("Taking payment...\n");
            break;
        case 14:
            // Owner Menu
            ownerSignIn();
            break;    
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

// Function to edit the librarian's profile
void editProfileLibrarian(struct Librarian *profile) {
    printf("Editing profile...\n");

    printf("Enter your name: ");
    scanf("%s", profile->librarianName);
    
    printf("Enter your email: ");
    scanf("%s", profile->email);

    printf("Profile Updated Successfully.\n");

    // Update profile in the file
    FILE *librarianFile = fopen("librarian_profile.txt", "r+");
    if (librarianFile == NULL) {
        printf("Error opening librarian profile file for editing.\n");
        return;
    }

    struct Librarian tempProfile;
    while (fread(&tempProfile, sizeof(struct Librarian), 1, librarianFile) == 1) {
        if (strcmp(profile->email, tempProfile.email) == 0) {
            fseek(librarianFile, -sizeof(struct Librarian), SEEK_CUR);
            fwrite(profile, sizeof(struct Librarian), 1, librarianFile);
            break;
        }
    }

    fclose(librarianFile);
}

// Function to add a new book
void addBook() {
    printf("Enter Book Details:\n");
    struct Book newBook;

    printf("Book ID: ");
    scanf("%d", &newBook.bookId);
    printf("Book Name: ");
    scanf(" %[^\n]", newBook.bookName);
    printf("Author: ");
    scanf(" %[^\n]", newBook.author);
    printf("Total Copies: ");
    scanf("%d", &newBook.totalCopies);
    printf("Available Copies: ");
    scanf("%d", &newBook.availableCopies);
    printf("Book Price: ");
    scanf("%d", &newBook.bookPrice);

    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d;%s;%s;%d;%d;%d\n",
            newBook.bookId, newBook.bookName, newBook.author,
            newBook.totalCopies, newBook.availableCopies, newBook.bookPrice);

    fclose(file);

    numBooks++; // Increment the number of books
    printf("Book added successfully!\n");
}

// Function to find a book by name
void findBook() {
    char searchName[100];
    printf("Enter the book name to search for: ");
    scanf(" %[^\n]", searchName);

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int found = 0;
    struct Book book;

    while (fscanf(file, "%d;%[^;];%[^;];%d;%d;%d\n",
                  &book.bookId, book.bookName, book.author,
                  &book.totalCopies, &book.availableCopies, &book.bookPrice) != EOF) {
        if (strcmp(searchName, book.bookName) == 0) {
            printf("Book found:\n");
            printf("Book ID: %d\n", book.bookId);
            printf("Book Name: %s\n", book.bookName);
            printf("Author: %s\n", book.author);
            printf("Total Copies: %d\n", book.totalCopies);
            printf("Available Copies: %d\n", book.availableCopies);
            printf("Book Price: %d\n", book.bookPrice);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Book not found.\n");
    }
}

// Function to add Book Copy
void addBookCopy() {
    int bookId, numCopies;

    printf("Enter the Book ID to add copies: ");
    scanf("%d", &bookId);

    FILE *file = fopen("books.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int foundIndex = -1;
    struct Book book;

    while (fscanf(file, "%d;%[^;];%[^;];%d;%d;%d\n",
                  &book.bookId, book.bookName, book.author,
                  &book.totalCopies, &book.availableCopies, &book.bookPrice) != EOF) {
        if (book.bookId == bookId) {
            foundIndex = numBooks; // Use the current numBooks value as index
            break;
        }
        numBooks++; // Count the number of books read from the file
    }

    if (foundIndex == -1) {
        printf("Book with ID %d not found.\n", bookId);
        fclose(file);
        return;
    }

    printf("Enter the number of copies to add: ");
    scanf("%d", &numCopies);

    // Update the available copies
    book.totalCopies += numCopies;
    book.availableCopies += numCopies;

    // Go back to the beginning of the found book's line in the file
    fseek(file, foundIndex * (sizeof(book) + 1), SEEK_SET);

    // Update the data in the file
    fprintf(file, "%d;%s;%s;%d;%d;%d\n",
            book.bookId, book.bookName, book.author,
            book.totalCopies, book.availableCopies, book.bookPrice);

    fclose(file);

    printf("%d copies added to the book \"%s\".\n", numCopies, book.bookName);
}

void loadBooks(struct Book books[], int *numBooks) {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    *numBooks = 0;
    while (fscanf(file, "%d;%[^;];%[^;];%d;%d;%d\n",
                  &books[*numBooks].bookId, books[*numBooks].bookName,
                  books[*numBooks].author, &books[*numBooks].totalCopies,
                  &books[*numBooks].availableCopies, &books[*numBooks].bookPrice) != EOF) {
        (*numBooks)++;
    }

    fclose(file);
}

// Function to edit a book
void editBook() {
    int bookId;

    printf("Enter the Book ID to edit: ");
    scanf("%d", &bookId);

    struct Book books[100];
    int numBooks;
    loadBooks(books, &numBooks);

    int foundIndex = -1;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Book with ID %d not found.\n", bookId);
        return;
    }

    printf("Enter new Book Name: ");
    scanf(" %[^\n]", books[foundIndex].bookName);
    printf("Enter new Author: ");
    scanf(" %[^\n]", books[foundIndex].author);
    printf("Enter new Book Price: ");
    scanf("%d", &books[foundIndex].bookPrice);

    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%d;%s;%s;%d;%d;%d\n",
                books[i].bookId, books[i].bookName, books[i].author,
                books[i].totalCopies, books[i].availableCopies, books[i].bookPrice);
    }

    fclose(file);

    printf("Book details updated successfully!\n");
}

// Function to change the rack of a book
void changeRack() {
    int bookId, newRack;

    printf("Enter Book ID: ");
    scanf("%d", &bookId);

    struct Book books[100];
    int numBooks;
    loadBooks(books, &numBooks);

    int foundIndex = -1;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Book with ID %d not found.\n", bookId);
        return;
    }

    printf("Enter new Rack number: ");
    scanf("%d", &newRack);

    // Update the rack number
    // books[foundIndex].rackNumber = newRack; // Add rackNumber to struct Book

    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%d;%s;%s;%d;%d;%d\n",
                books[i].bookId, books[i].bookName, books[i].author,
                books[i].totalCopies, books[i].availableCopies, books[i].bookPrice);
    }

    fclose(file);

    printf("Rack number updated successfully!\n");
}

// Function to add a new member and sign in
void addNewMember() {
    struct Member newMember;

    printf("Enter member details:\n");
    printf("Enter member name: ");
    scanf(" %[^\n]", newMember.memberName);
    printf("Enter member email: ");
    scanf("%s", newMember.email);
    printf("Enter member password: ");
    scanf("%s", newMember.password);
    // ...

    generateMemberId(&newMember); // Generate member ID

    FILE *file = fopen("members.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s;%s;%s;%d\n", newMember.memberName, newMember.email, newMember.password, newMember.memberId);

    fclose(file);

    printf("Member signed up successfully!\n");

    // Now sign in as the new member
    printf("Sign In:\n");
    signInMember(&newMember);
}


// Function to sign in as a member
void signInMember(struct Member *member) {
    char enteredPassword[50]; // Temporary storage for entered password

    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    FILE *file = fopen("members.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char storedPassword[50];
    int storedMemberId;

    while (fscanf(file, "%*[^;];%*[^;];%[^;];%d\n", storedPassword, &storedMemberId) != EOF) {
        if (storedMemberId == member->memberId) {
            if (strcmp(enteredPassword, storedPassword) == 0) {
                printf("Sign In successful\n");

                // First-time sign-in: Prompt to change password
                if (strcmp(member->password, "default") == 0) {
                    printf("It's recommended to change your password.\n");
                    // Implement a function to change the password
                    changePasswordForMember(member);
                }

                // Redirect to the member menu
                memberMenu(member);
                fclose(file);
                return;
            } else {
                printf("Invalid password.\n");
                fclose(file);
                return;
            }
        }
    }

    printf("Member ID not found.\n");
    fclose(file);
}

void generateMemberId(struct Member *member) {
    member->memberId = memberIdCounter++;
}

// Function to change the password for a member
void changePasswordForMember(struct Member *member) {
    printf("Enter your new password: ");
    scanf("%s", member->password);
    printf("Password changed successfully!\n");

    FILE *file = fopen("members.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int storedMemberId;
    char storedPassword[50];
    long int position = 0;
    while (fscanf(file, "%*[^;];%*[^;];%[^;];%d\n", storedPassword, &storedMemberId) != EOF) {
        if (storedMemberId == member->memberId) {
            fseek(file, position, SEEK_SET); // Move to the beginning of the line
            fprintf(file, "%s;%s;%s;%d\n", member->memberName, member->email, member->password, member->memberId);
            break;
        }
        position = ftell(file);
    }

    fclose(file);
}


//MemberMenu
void memberMenu() {
    struct Member memberProfile; // Create an instance of OwnerProfile
    int choice;

    printf("Member Menu:\n");
    printf("1. Sign Out\n");
    printf("2. Edit Profile\n");
    printf("3. Change Password\n");
    printf("4. Find Book\n");
    printf("5. Check Availability\n");
    printf("6. Librarian Menu\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sign out
            signOut(&currentUser);
            break;
        case 2:
            // Edit Profile
            editProfileMember(&memberProfile);
            break;
        case 3:
            // Change Password
            changePassword(&currentUser);
            break;
        case 4:
            // Find Book
            findBook();
            break;
        case 5:
            // Check Availability
            printf("Checking book availability...\n");
            break;
        case 6:
            // Check Availability
            librarianSignIn();
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

// Function to edit the member's profile
void editProfileMember(struct Member *profile) {
    printf("Editing profile...\n");

    printf("Enter your name: ");
    scanf("%s", profile->memberName);
    
    printf("Enter your email: ");
    scanf("%s", profile->email);

    // Update the profile in the file
    FILE *file = fopen("members.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int storedMemberId;
    char storedPassword[50];
    long int position = 0;
    while (fscanf(file, "%*[^;];%*[^;];%[^;];%d\n", storedPassword, &storedMemberId) != EOF) {
        if (storedMemberId == profile->memberId) {
            fseek(file, position, SEEK_SET); // Move to the beginning of the line
            fprintf(file, "%s;%s;%s;%d\n", profile->memberName, profile->email, profile->password, profile->memberId);
            break;
        }
        position = ftell(file);
    }

    fclose(file);

    printf("Profile Updated Successfully.\n");
}

//Date1
void inputDate1(struct Date *date1) {
    printf("Enter day: ");
    scanf("%d", &date1->dd);
    printf("Enter month: ");
    scanf("%d", &date1->mm);
    printf("Enter year: ");
    scanf("%d", &date1->yy);
}

void displayDate1(struct Date date1) {
    printf("%02d/%02d/%04d", date1.dd, date1.mm, date1.yy);
}

//Date2
void inputDate2(struct Date *date2) {
    printf("Enter day: ");
    scanf("%d", &date2->dd);
    printf("Enter month: ");
    scanf("%d", &date2->mm);
    printf("Enter year: ");
    scanf("%d", &date2->yy);
}

void displayDate2(struct Date date2) {
    printf("%02d/%02d/%04d", date2.dd, date2.mm, date2.yy);
}

//Add Days
void addDays(struct Date *date, int days) {
    // Use <time.h> library
    struct tm timeinfo = {0}; // Create a struct tm variable for the given date

    // Set the components of timeinfo to match the provided date
    timeinfo.tm_year = date->yy - 1900; // Adjust the year (years since 1900)
    timeinfo.tm_mon = date->mm - 1;     // Adjust the month (0-based, so subtract 1)
    timeinfo.tm_mday = date->dd;        // Set the day of the month

    // Convert struct tm to time_t using mktime function
    time_t rawtime = mktime(&timeinfo); // Convert the given date to time_t

    // Add the specified number of days in seconds to rawtime
    rawtime += days * 24 * 60 * 60; // Convert days to seconds

    // Convert the modified time_t back to struct tm using localtime function
    struct tm *new_timeinfo = localtime(&rawtime);

    // Update the components of the original date using the modified struct tm
    date->dd = new_timeinfo->tm_mday;     // Update day
    date->mm = new_timeinfo->tm_mon + 1;   // Update month (add 1 to get 1-based)
    date->yy = new_timeinfo->tm_year + 1900; // Update year (add 1900 to get actual year)
}

//Compair Date and Find Difference
int compareDates(struct Date date1, struct Date date2) {
    // Calculate the difference in days between two dates
    struct tm timeinfo1 = {0}; // Create a struct tm variable for the first date
    struct tm timeinfo2 = {0}; // Create a struct tm variable for the second date
    
    // Set the components of timeinfo1 to match date1
    timeinfo1.tm_year = date1.yy - 1900; // Adjust year
    timeinfo1.tm_mon = date1.mm - 1;     // Adjust month (0-based)
    timeinfo1.tm_mday = date1.dd;        // Day of the month
    
    // Set the components of timeinfo2 to match date2
    timeinfo2.tm_year = date2.yy - 1900; // Adjust year
    timeinfo2.tm_mon = date2.mm - 1;     // Adjust month (0-based)
    timeinfo2.tm_mday = date2.dd;        // Day of the month
    
    // Convert struct tm variables to time_t using mktime
    time_t rawtime1 = mktime(&timeinfo1); // Convert first date to time_t
    time_t rawtime2 = mktime(&timeinfo2); // Convert second date to time_t
    
    // Calculate the difference in seconds using difftime
    double diff_seconds = difftime(rawtime2, rawtime1);
    
    // Convert the difference in seconds to days
    int diff_days = diff_seconds / (24 * 60 * 60);
    
    return diff_days; // Return the difference in days
}


// Main
int main() {
    int choice;
    //struct User currentUser;

    do
    {
    displayMainMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Sign up a new user
            printf("\nSign Up for a new user:\n");
            signUp();
            break;
    
        case 2:
            //Sign in for user
            printf("\nSign In for a new user:\n");
            signIn(&currentUser);
            break;

        case 0:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 0);

    // Display the user's information
    printf("New user information:\n");
    printf("email: %s\n", currentUser.email);
    printf("Password: %s\n", currentUser.password);
    printf("User Type: %s\n", currentUser.userType);

    //Add two dates
    struct Date date1, date2;
    printf("Please enter a date:\n");
    inputDate1(&date1);
    printf("Please enter a date:\n");
    inputDate2(&date2);
    printf("You entered the following date1: ");
    displayDate1(date1); // Call the displayDate function to display the entered date1
    printf("\n");

    printf("You entered the following date2: ");
    displayDate2(date2); // Call the displayDate function to display the entered date2
    printf("\n");

    int difference = compareDates(date1, date2);
    printf("The difference between the two dates is %d days.\n", difference);


    // Get the number of days to add from the user
    int daysToAdd;
    printf("Enter the number of days to add: ");
    scanf("%d", &daysToAdd);
    // Call the addDays function to modify the date
    addDays(&date1, daysToAdd);
    // Display the modified date
    printf("Original date: %02d/%02d/%04d\n", date1.dd, date1.mm, date1.yy);

}