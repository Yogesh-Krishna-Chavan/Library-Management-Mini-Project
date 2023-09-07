#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 10
#define MAX_USERTYPE_SIZE 10
#define MAX_USERS 3
#define MAX_EMAIL_LENGTH 10
#define MAX_RACKS 2
#define MAX_BOOKS_PER_RACK 10
#define MAX_COPIES_PER_BOOK 2

// typedef struct Date {
//     int day;
//     int month;
//     int year;
// };

typedef struct {
    int memberId;
    char username[MAX_NAME_LENGTH];
    char email[15];
    char password[MAX_PASSWORD_LENGTH];
    // struct Date joinDate;
    int isPaidUser;
    float fineAmount;
    char userType[MAX_USERTYPE_SIZE]; // Owner/Librarian/Member
    // struct Node *issuedBooks; // Linked list to store issued books
} User;

typedef struct Copy {
    int copyId;
    int isAvailable;
    time_t dueDate;
}Copy;


typedef struct Book{
    int bookId;
    char bookName[100];
    char authorName[50];
    char subject[50];
    float bookPrice;
    int isbn;
    struct Copy copies[10];
    int copyCount;
}Book;


typedef struct Rack {
    struct Book books[MAX_BOOKS_PER_RACK];
    int bookCountInRack;
    struct Rack *next;
    // struct Copy copies[MAX_COPIES_PER_BOOK];
    // int copyCount;
};

typedef struct  {
    // struct Rack racks[MAX_RACKS];
    struct Rack *racks;
    int rackCount;
}Library;

typedef struct  {
    User* currentUser;
    int isLoggedIn;
}Session;

typedef struct IssueBookNode {
    Book *book;
    struct IssueBookNode *next;
} IssueBookNode;

typedef struct Node {
    struct Book bookData;
    User userData;
    IssueBookNode issuedBooks;
    struct Node * prev;
    struct Node * next;
}node_t;

typedef struct {
     node_t * head;
     node_t * tail;
}list_t;



User users[MAX_USERS];
int userCount = 0;
Library library;

void initializeLibrary() {
    library.racks = NULL;
    library.rackCount = 0;
}


void addlast(list_t *list, User user) {
    node_t * newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->userData = user;
    newNode->next = NULL;

    if(list->head == NULL) {
        newNode->prev = NULL;
        list->head = newNode;
        return;
    }
    struct Node *current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    
}

void printUserList(list_t *list) {
    if (list == NULL) {
        printf("Invalid list.\n");
        return;
    }
    node_t *current = list->head;
    while (current != NULL) {
         printf("User ID: %d\n", current->userData.memberId);
        printf("UserName: %s\n", current->userData.username);
        printf("Password: %s\n", current->userData.password);
        printf("User Type: %s\n", current->userData.userType);
        // printf("Book Subject: %s\n", current->bookData.subject);
        // printf("Book Price: %.2f\n", current->bookData.bookPrice);
        // printf("Book Copy Number: %d\n", current->bookData.copyCount);
        // printf("Book %d %d\n", current->bookData.copies->copyId, current->bookData.copies->isAvailable);
        printf("---------------------------\n");
        current = current->next;
    }
}

void writeUsersToFile(list_t *list) {
    FILE* file = fopen("UserDetails.dat", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    node_t *current = list->head;
    while (current != NULL) {
        fwrite(&(current->userData),sizeof(User),1,file);
        current = current->next;
    }
    fclose(file);
     printf("User data written to UserDetails\n");
}

void readUsersFromFile(list_t *list) {
    FILE* file = fopen("UserDetails.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    User user;
    while(fread(&user,sizeof(User),1,file)!=0) {
            addlast(list, user);
    } 
    fclose(file);
    printf("Book data read from UserDetails\n");
}

void editBookDetails(list_t *list, int bookId) {
    node_t *current = list->head;
    while (current != NULL) {
        if (current->bookData.bookId == bookId) {
            // Book found, allow editing
            printf("Editing Book Details for Book ID: %d\n", bookId);
            printf("Enter updated book Name: ");
            scanf("%s", current->bookData.bookName);
            printf("Enter updated author Name: ");
            scanf("%s", current->bookData.authorName);
            printf("Enter updated Subject: ");
            scanf("%s", current->bookData.subject);
            printf("Enter updated book Price: ");
            scanf("%f", &current->bookData.bookPrice);
            printf("Book details updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Book with ID %d not found.\n", bookId);
}


void addCopyToBook(list_t *list, int bookId, int copyId) {
    node_t *current = list->head;
    while (current != NULL) {
        if (current->bookData.bookId == bookId) {
            if (current->bookData.copyCount < MAX_COPIES_PER_BOOK) {
                if (current->bookData.copyCount < MAX_RACKS * MAX_BOOKS_PER_RACK) {
                    Copy newCopy;
                    newCopy.copyId = copyId;
                    newCopy.isAvailable = 1; // Assuming the copy is available initially
                    current->bookData.copies[current->bookData.copyCount] = newCopy;
                    current->bookData.copyCount++;
                    printf("Copy added to the book.\n");
                    return;
                } else {
                    printf("Maximum copies per rack reached for this book.\n");
                    return;
                }
            } else {
                printf("Maximum copies reached for this book.\n");
                return;
            }
        }
        current = current->next;
    }
    printf("Book with ID %d not found.\n", bookId);
}


void addlastBook(list_t *list, Book book) {
    node_t * newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->bookData = book;
    newNode->next = NULL;

    if(list->head == NULL) {
        newNode->prev = NULL;
        list->head = newNode;
        return;
    }
    struct Node *current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    
}

void printBookList(list_t *list) {
    if (list == NULL) {
        printf("Invalid list.\n");
        return;
    }
    node_t *current = list->head;
    while (current != NULL) {
        printf("Book ID: %d\n", current->bookData.bookId);
        printf("Book Name: %s\n", current->bookData.bookName);
        printf("Book Author Name: %s\n", current->bookData.authorName);
        printf("Book Subject: %s\n", current->bookData.subject);
        printf("Book Price: %.2f\n", current->bookData.bookPrice);
        printf("Book Copy Number: %d\n", current->bookData.copyCount);
        // printf("Book %d %d\n", current->bookData.copies->copyId, current->bookData.copies->isAvailable);
        printf("---------------------------\n");
        current = current->next;
    }
}

void writeBooksToFile(list_t *list) {
    FILE* file = fopen("BookDetails.dat", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    node_t *current = list->head;
    while (current != NULL) {
        fwrite(&(current->bookData),sizeof(Book),1,file);
        // fprintf(file, "\n");
        current = current->next;
    }
    fclose(file);
     printf("Book data written to BookDetails\n");
}

void readBooksFromFile(list_t *list) {
    FILE* file = fopen("BookDetails.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    Book book;
    while(fread(&book,sizeof(Book),1,file)!=0) {
            addlastBook(list, book);
       } 
    fclose(file);
    printf("Book data read from BookDetails\n");
}
void librarianMenu() {
    // printf(username);
    // Implement librarian menu
    list_t mainbooklist;
    mainbooklist.head=NULL;
    mainbooklist.tail=NULL;
    Book newBook;
    int choice;
    int bookId, copyId;

    printf("*******************\n");
    printf("Librarian Menu\n");
    printf("*******************\n");
    do {
        printf("0. Exit\n");
        printf("1. Add New Book\n");
        printf("2. Find All Books \n");
        printf("3. Add Copy To Book\n");
        printf("4. Edit book details\n");
        
        printf("Enter Your Choice : \n");
        scanf("%d",&choice);
        printf("*******************\n");
        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            break;    
        case 1:
             printf("Enter book Id: \n");
             scanf("%d", &newBook.bookId);
             printf("Enter book Name: \n");
             scanf("%s", newBook.bookName);
             printf("Enter book authorName: \n");
             scanf("%s", newBook.authorName);
             printf("Enter Subject Name: \n");
             scanf("%s", newBook.subject);
             printf("Enter book Price: \n");
             scanf("%f", &newBook.bookPrice);
             printf("Enter book ISBN: \n");
             scanf("%d", &newBook.isbn);
             printf("Enter book copyId: \n");
             scanf("%d", &newBook.copies->copyId);
             printf("Enter book copy count: \n");
             scanf("%d", &newBook.copyCount);
             addlastBook(&mainbooklist,newBook);
            break;
        case 2:
            readBooksFromFile(&mainbooklist);
            printBookList(&mainbooklist);
            break;
        case 3:
            printf("Enter the book ID: ");
            scanf("%d", &bookId);
            printf("Enter the copy ID: ");
            scanf("%d", &copyId);
            addCopyToBook(&mainbooklist, bookId, copyId);
            break;
        case 4:
            printf("Enter the book ID to edit: ");
            scanf("%d", &bookId);
            editBookDetails(&mainbooklist, bookId);
            break;
        case 5:
            break;      
        default:
            break;
        }
    }while (choice != 0);
    writeBooksToFile(&mainbooklist);
}


User *findUserById(list_t *userlist, int userId) {
    printf("findUserById********\n");
    node_t *current = userlist->head;
    printf("ok1\n");
    printf("User email %s",current->userData.email);
    printf("ok2\n");
    while (current != NULL) 
    {
        printf("findUserById\n");
        if (current->userData.memberId == userId) {
            return &(current->userData); // Return a pointer to the user if found
        }
        current = current->next;
    }
    return NULL; // Return NULL if user is not found
}

void issueBook(list_t *userlist, list_t *mainbooklist, int userId, int bookId, int copyId) {
    printf("userId %d\n",userId);
    User *user = findUserById(userlist, userId);
    printf("&&&&&&&&&&&");
    if (user == NULL) {
        printf("User with ID %d not found.\n", userId);
        return;
    }else {
        printf("User is found");
    }
}


void memberMenu() {
    // printf(username);
    // Implement librarian menu
    list_t mainbooklist;
    mainbooklist.head=NULL;
    mainbooklist.tail=NULL;
    list_t userlist;
    userlist.head = NULL;
    userlist.tail = NULL;
    Book newBook;
    int choice;
    int bookId, copyId, userId;

    printf("*******************\n");
    printf("Member Menu\n");
    printf("*******************\n");
    do {
        printf("0. Exit\n");
        printf("1. Find All Books\n");
        printf("2. Issue Book \n");
        printf("3. \n");
        printf("4. \n");
        
        printf("Enter Your Choice : \n");
        scanf("%d",&choice);
        printf("*******************\n");
        switch (choice)
        {
        case 0:
            printf("Exiting...\n");
            break;    
        case 1:
            readBooksFromFile(&mainbooklist);
            printBookList(&mainbooklist);
            break;
        case 2:
            printf("Enter the user ID: ");
            scanf("%d", &userId);
            printf("Enter the book ID: ");
            scanf("%d", &bookId);
            printf("Enter the copy ID: ");
            scanf("%d", &copyId);
            
            issueBook(&userlist, &mainbooklist, userId, bookId, copyId);
            break;
        case 3:
            break;
        case 4:
            break;      
        default:
            break;
        }
    }while (choice != 0);
    writeBooksToFile(&mainbooklist);
}




int signUp(list_t *list) {
    printf("inside sign-up function\n");
    if (userCount >= MAX_USERS) {
        printf("Maximum user limit reached.\n");
        return 0;
    }
    User newUser;
    // int memberId = 1;
    printf("Enter a username: \n");
    scanf("%s", newUser.username);

    // Check if the username already exists
    node_t *current = list->head;
    while (current != NULL) {
        if (strcmp(newUser.username, current->userData.username) == 0) {
            printf("Username already exists.\n");
            return 0;
        }
        current = current->next;
    }
    
    // newUser.memberId = memberId;
    printf("Enter member ID: \n");
    scanf("%d", &newUser.memberId);

    printf("Enter 1 if user is paid: \n");
    scanf("%d", &newUser.isPaidUser);

    printf("Enter a password: \n");
    scanf("%s", newUser.password);

    printf("Enter a Email: \n");
    scanf("%s", newUser.email);

    // printf("Enter a Date: \n");
    // scanf("%s", newUser.joinDate);


    int userTypeChoice;

    printf("Select the user type:\n");
    printf("1. Member\n");
    printf("2. Owner\n");
    printf("3. Librarian\n");
    printf("Enter your choice: ");
    scanf("%d", &userTypeChoice);
    
    switch (userTypeChoice) {
        case 1:
            strcpy(newUser.userType, "Member");
            break;
        case 2:
            strcpy(newUser.userType, "Owner");
            break;
        case 3:
            strcpy(newUser.userType, "Librarian");
            break;
        default:
            printf("Invalid user type selection.\n");
            return 0;
    }

    users[userCount++] = newUser;
    addlast(list, newUser); 
    printf("*******************\n");
    printf("Sign-up successful!\n");
    printf("*******************\n");

    return 1;
}

struct User *signIn(list_t *userlist, int userCount, Session *session) {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    node_t *current = userlist->head;
    while (current != NULL) {
        if (strcmp(current->userData.username, username) == 0 && strcmp(current->userData.password, password) == 0) {
            session->currentUser = &(current->userData);
            session->isLoggedIn = 1;
            printf("Welcome, %s!\n", session->currentUser);

            // Validate user and set user type
            if (strcmp(session->currentUser->userType, "Owner") == 0) {
                //  printf("ownerMenu.\n");
                // ownerMenu();
                return session->currentUser;
            } else if (strcmp(session->currentUser->userType, "Librarian") == 0) {
                //  printf("librarianMenu.\n");
                librarianMenu();
                return session->currentUser;
            } else if (strcmp(session->currentUser->userType, "Member") == 0) {
                printf("memberMenu.\n");
                memberMenu();
                return session->currentUser;
            } else {
                printf("Invalid user type.\n");
            }

            return session->currentUser;

    }
        current = current->next;
    }

    printf("Invalid username or password.\n");
    return NULL;
}

void logOut(Session *session) {
    session->currentUser = NULL;
    session->isLoggedIn = 0;
    printf("Log Out Successfully...");
}

int main () {
    Session session;
    session.currentUser = NULL;
    session.isLoggedIn = 0;
    list_t userlist;
    userlist.head = NULL;
    userlist.tail = NULL;
    int choice;
    do {
        printf("0. Exit\n");
        printf("1. Sign In\n");
        printf("2. Sign Up\n");
        printf("3. Show all User\n");
        // printf("4. add days in given date\n");
        // printf("5. Show All Users\n");
        // printf("6. Edit User Profile\n");
        printf("7. LogOut\n");
        printf("Enter Your Choice\n : ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 0:
             printf("Exiting....");
             break;    
        case 1:
            if (!session.isLoggedIn) {
                signIn(&userlist, userCount, &session);
            } else {
                printf("You are already signed in.\n");
            }
                break;

        case 2:
            signUp(&userlist);
            break;
        case 3:
            readUsersFromFile(&userlist);
            printUserList(&userlist);
           break;  
        case 4:
            break;
        case 5:
            break;
        case 6:
            if(session.isLoggedIn) {
                    // editUserProfile(session.currentUser);
            } else {
                    printf("You need to be signed in to edit your profile.\n");
            }
                break;
        case 7:
            if (session.isLoggedIn) {
                    logOut(&session);
            } else {
                    printf("You are not signed in.\n");
            }  
            break; 
        case 8:
            
        break;
        default:
             printf("Invalid Choice...Enter Valid choice");
            break;
        }
    }while (choice != 0);
    
    writeUsersToFile(&userlist);
    
}


