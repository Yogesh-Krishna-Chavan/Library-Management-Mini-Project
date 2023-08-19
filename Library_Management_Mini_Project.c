#include <stdio.h>
#include <time.h>

// Define structures
struct Date {
    int dd;
    int mm;
    int yy;
};

struct User {
    char username[50];
    char password[50];
    char userType[20]; // Owner/Librarian/Member
};

struct Member {
    int memberId;
    char memberName[100];
    struct Date joinDate;
    int isPaidUser;
    float fineAmount;
};

// Function prototypes
void signUp();
void signIn();
void inputDate(struct Date *date);
void displayDate(struct Date date);
void addDays(struct Date *date, int days);
int compareDates(struct Date date1, struct Date date2);

// Global variables
struct User currentUser;

//SignUp
void signUp() {
    int userTypeChoice;

    printf("Select the user type:\n");
    printf("1. Member\n");
    printf("2. Owner\n");
    printf("3. Librarian\n");
    printf("Enter your choice: ");
    scanf("%d", &userTypeChoice);

    printf("Enter a username: ");
    scanf("%s", currentUser.username);
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
}

//SignIn
void signIn() {
    printf("Enter your username: ");
    scanf("%s", currentUser.username);
    printf("Enter your password: ");
    scanf("%s", currentUser.password);

    // Validate user and set user type
    if (strcmp(currentUser.userType, "Owner") == 0) {
        ownerMenu();
    } else if (strcmp(currentUser.userType, "Librarian") == 0) {
        librarianMenu();
    } else if (strcmp(currentUser.userType, "Member") == 0) {
        memberMenu();
    } else {
        printf("Invalid user type.\n");
    }
}

void ownerMenu() {
    // Implement owner menu
    printf("Owner Menu\n");
}

void librarianMenu() {
    // Implement librarian menu
    printf("Librarian Menu\n");
}

void memberMenu() {
    // Implement member menu
    printf("Member Menu\n");
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

void addDays(struct Date *date, int days) {
    // Use <time.h> library to manipulate dates
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

    // Sign up a new user
    printf("\nSign Up for a new user:\n");
    signUp();

    //Sign in for user
    printf("\nSign In for a new user:\n");
    signIn();

    // Display the user's information
    printf("New user information:\n");
    printf("Username: %s\n", currentUser.username);
    printf("Password: %s\n", currentUser.password);
    printf("User Type: %s\n", currentUser.userType);


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