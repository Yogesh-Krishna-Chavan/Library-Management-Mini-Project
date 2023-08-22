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
    struct Date joinDate;
    int isPaidUser;
    float fineAmount;
};

struct Owner {
    char ownerName[100];
    char email[50];
};

struct Librarian {
    char librarianName[100];
    char email[50];
};

struct Book {
    int bookId;
    char bookName[100];
    char author[100];
    int totalCopies;
    int availableCopies;
    int bookPrice; 
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
void editProfileOwner(struct Owner *profile);
void changePassword(struct User *user);
void editProfileLibrarian(struct Librarian *profile);
void addBook();
void addBookCopy();
void editProfileMember(struct Member *profile);

// Global variables
struct User currentUser;
struct Book books[100]; // You can adjust the size as needed
int numBooks = 0;

//SignUp
void signUp() {
    int userTypeChoice;

    printf("Select the user type:\n");
    printf("1. Member\n");
    printf("2. Owner\n");
    printf("3. Librarian\n");
    printf("Enter your choice: ");
    scanf("%d", &userTypeChoice);

    printf("Enter a email: ");
    scanf("%s", currentUser.email);
    printf("Enter a password: ");
    scanf("%s", currentUser.password);

    switch (userTypeChoice) {
        case 1:
            strcpy(currentUser.userType, "Member");
            break;
        case 2:
            strcpy(currentUser.userType, "Owner");
            break;
        case 3:
            strcpy(currentUser.userType, "Librarian");
            break;
        default:
            printf("Invalid user type selection.\n");
            return;
    }
    printf("User signed up successfully!\n");
}

//SignIn
void signIn(struct User *user) {
    char enteredEmail[50]; // Temporary storage for entered email
    char enteredPassword[50]; // Temporary storage for entered password

    printf("Enter your email: ");
    scanf("%s", enteredEmail); // Store entered email in temporary variable
    printf("Enter your password: ");
    scanf("%s", enteredPassword); // Store entered password in temporary variable

    // Validate user and set user type
    if (strcmp(enteredEmail, user->email) == 0 && strcmp(enteredPassword, user->password) == 0) {

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
    return;
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
            printf("Signing out...\n");
            break;
        case 2:
            // Edit Profile
            editProfileOwner(&ownerProfile);
            break;
        case 3:
            // Change Password
            changePassword(&currentUser);
            break;
        case 4:
            // Appoint Librarian
            printf("Appointing librarian...\n");
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
            printf("Displaying available books...\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }
}

// Function to edit the owner's profile
void editProfileOwner(struct Owner *profile) {
    printf("Editing profile...\n");

    printf("Enter your name: ");
    scanf("%s", profile->ownerName);
    
    printf("Enter your email: ");
    scanf("%s", profile->email);

    printf("Profile Updated Successfully.\n");

}

// Function to change the password For Owner/Member/Librarian
void changePassword(struct User *user) {
    char newPassword[50];
    printf("Enter your new password: ");
    scanf("%s", newPassword);
    strcpy(user->password, newPassword);
    printf("Password changed successfully!\n");
}


//LibrarianMenu
void librarianMenu() {
    struct Librarian librarianProfile;
    int choice;

    printf("Librarian Menu:\n");
    printf("1. Sign Out\n");
    printf("2. Edit Profile\n");
    printf("3. Change Password\n");
    printf("4. Sign In\n");
    printf("5. Return Copy\n");
    printf("6. Issue Copy\n");
    printf("7. Find Book\n");
    printf("8. Edit Book\n");
    printf("9. Add New Book\n");
    printf("10. Check Availability\n");
    printf("11. Add New Copy\n");
    printf("12. Change Rack\n");
    printf("13. Add New Member\n");
    printf("14. Take Payment\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sign out
            printf("Signing out...\n");
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
            // Sign In
            printf("Signing in...\n");
            break;
        case 5:
            // Return Copy
            printf("Returning a copy...\n");
            break;
        case 6:
            // Issue Copy
            printf("Issuing a copy...\n");
            break;
        case 7:
            // Find Book
            findBook();
            break;
        case 8:
            // Edit Book
            printf("Editing a book...\n");
            break;
        case 9:
            // Add New Book
            addBook();
            break;
        case 10:
            // Check Availability
            printf("Checking book availability...\n");
            break;
        case 11:
            // Add New Copy
            addBookCopy();
            break;
        case 12:
            // Change Rack
            printf("Changing rack...\n");
            break;
        case 13:
            // Add New Member
            printf("Adding a new member...\n");
            break;
        case 14:
            // Take Payment
            printf("Taking payment...\n");
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

}

// Function to add a new book
void addBook() {
    printf("Enter Book Details:\n");
    printf("Book ID: ");
    scanf("%d", &books[numBooks].bookId);
    printf("Book Name: ");
    scanf(" %[^\n]", books[numBooks].bookName); // Read the whole line
    printf("Author: ");
    scanf(" %[^\n]", books[numBooks].author); // Read the whole line
    printf("Total Copies: ");
    scanf("%d", &books[numBooks].totalCopies);
    printf("Available Copies: ");
    scanf("%d", &books[numBooks].availableCopies);
    printf("Book Price: ");
    scanf("%d", &books[numBooks].bookPrice);

    numBooks++; // Increment the number of books
    printf("Book added successfully!\n");
}

// Function to find a book by name
void findBook() {
    char searchName[100];
    printf("Enter the book name to search for: ");
    scanf(" %[^\n]", searchName); // Read the whole line

    int found = 0; // Flag to indicate if book is found

    // Search for the book
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(searchName, books[i].bookName) == 0) {
            printf("Book found:\n");
            printf("Book ID: %d\n", books[i].bookId);
            printf("Book Name: %s\n", books[i].bookName);
            printf("Author: %s\n", books[i].author);
            printf("Total Copies: %d\n", books[i].totalCopies);
            printf("Available Copies: %d\n", books[i].availableCopies);
            printf("Book Price: %d\n", books[i].bookPrice);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void addBookCopy() {
    int bookId, numCopies;

    printf("Enter the Book ID to add copies: ");
    scanf("%d", &bookId);

    // Find the book by its ID
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

    printf("Enter the number of copies to add: ");
    scanf("%d", &numCopies);

    // Update the available copies
    books[foundIndex].totalCopies += numCopies;
    books[foundIndex].availableCopies += numCopies;

    printf("%d copies added to the book \"%s\".\n", numCopies, books[foundIndex].bookName);
}

//MemberMenu
void memberMenu() {
    struct Member memberProfile; // Create an instance of OwnerProfile
    int choice;

    printf("Member Menu:\n");
    printf("1. Sign Out\n");
    printf("2. Sign Up\n");
    printf("3. Edit Profile\n");
    printf("4. Change Password\n");
    printf("5. Find Book\n");
    printf("6. Check Availability\n");
    printf("Enter your choice: ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sign out
            printf("Signing out...\n");
            break;
        case 2:
            // Sign Up
            printf("Signing up...\n");
            break;
        case 3:
            // Edit Profile
            editProfileMember(&memberProfile);
            break;
        case 4:
            // Change Password
            changePassword(&currentUser);
            break;
        case 5:
            // Find Book
            printf("Finding a book...\n");
            break;
        case 6:
            // Check Availability
            printf("Checking book availability...\n");
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