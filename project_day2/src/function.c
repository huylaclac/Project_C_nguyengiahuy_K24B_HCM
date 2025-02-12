#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "function.h"
#include "datatype.h"


User users[MAX_USERS];          // users la mot mang chua nhieu nguoi dung (kieu user) toi da max_user
int userCount = 0;              // day la mot bien toan cuc dung de biet so luong nguoi dung hien co 

// Menu chinh cua chuong trinh 
void MainMenu() {
    int choice;
    do {
        printf("*** %s ***\n\n", "Bank management system using C");
        printf("%20s\n", "CHOOSE YOUR ROLE");
        printf("%s\n", "========================");
        printf("%s\n", "[1] Admin.");
        printf("%s\n", "[2] User.");
        printf("%s\n", "[3] Exit the program.");
        printf("%s\n", "========================");
        printf("%s", "Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                displayAdminMenu();
                break;
            case 2:
                break;
            case 3:
                end();
                break;
            default:
                printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 3);
}

void end() {
    printf("\n%10s %5s %10s\n", "=========", "Thank you", "=========");
    printf("%10s %5s %10s\n", "=========", "See you soon", "=========");
    printf("--------------------------------\n");
}

//ham hien Menu danh cho admin
void displayAdminMenu() {
    int choice;
    do {
        printf("\n=== User Management ===\n");
        printf("-----------------------\n");
        printf("|%-21s|\n", "1. Display user list");
        printf("|%-21s|\n", "2. Add a user");
        printf("|%-21s|\n", "3. Sort user list");
        printf("|%-21s|\n", "4. Search for a user");
        printf("|%-21s|\n", "5. Exit");
        printf("-----------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                displayUserInfor();
                break;
            case 2:
            	addUser(); 
                break;
            case 4:
            	searchUser();
				break; 
			case 5:
				printf("return MainMenu");
				return ; 
            default:
                printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 5);
}

//ham doc du lieu tu file de biet so luong nguoi dung dang co 
void readUsersFromFile() {
    FILE *file = fopen("Userinfor.bin", "rb"); 
    if (file == NULL) {
        printf("Cannot open file Userinfor.bin\n");
        return;
    }

    userCount = fread(users, sizeof(User), MAX_USERS, file); 
    fclose(file); 

    printf("Read %d users from Userinfor.bin file.\n", userCount);
}

// hien thong tin nguoi dung  
void displayUserInfor() {
    FILE *file = fopen("Userinfor.bin", "rb");  
    if (file == NULL) {
        printf("Cannot open file Userinfor.bin\n");
        return;
    }

    User tempUser;
    printf("\n");
    printf("==========================================================================================\n");
    printf("| %-12s | %-20s | %-25s | %-12s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("==========================================================================================\n");

    while (fread(&tempUser, sizeof(User), 1, file)) {
        printf("| %-12s | %-20s | %-25s | %-12s | %-5s |\n",
               tempUser.id, tempUser.name, tempUser.email, tempUser.phone, tempUser.status);
        printf("------------------------------------------------------------------------------------------\n");
    }

    fclose(file);
}

void readUserFromFile() {
    FILE *file = fopen("Userinfor.bin", "rb");
    if (file == NULL) {
        printf("File not found. Starting with an empty user list.\n");
        return;
    }

    userCount = fread(users, sizeof(User), MAX_USERS, file);
    fclose(file);

    printf("Loaded %d users from file.\n", userCount);
}

void saveAllUsersToFile() {
    FILE *file = fopen("Userinfor.bin", "wb"); 
    if (file == NULL) {
        printf("Error: Cannot open file to save users.\n");
        return;
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    printf("All users saved to file.\n");
}

void addUser() {
    FILE *file = fopen("Userinfor.bin", "ab"); 
    if (file == NULL) {
        printf("Error: Cannot open file to save user.\n");
        return;
    }

    User newUser;
    int isValid;

    do {
        isValid = 1;

        printf("Enter ID (max 20 chars): ");
        scanf("%s", newUser.id);

        printf("Enter phone number (max 15 chars): ");
        scanf("%s", newUser.phone);

        printf("Enter full name (max 50 chars): ");
        scanf(" %[^\n]s", newUser.name);

        printf("Enter email (must end with @gmail.com, max 30 chars): ");
        scanf("%s", newUser.email);

        printf("Enter password (max 20 chars): ");
        scanf("%s", newUser.password);

        strcpy(newUser.status, "open");

        if (strlen(newUser.id) == 0 || strlen(newUser.id) > 20 ||
            strlen(newUser.phone) == 0 || strlen(newUser.phone) > 15 ||
            strlen(newUser.name) == 0 || strlen(newUser.name) > 50 ||
            strlen(newUser.email) == 0 || strlen(newUser.email) > 30 ||
            strlen(newUser.password) == 0 || strlen(newUser.password) > 20) {
            printf("Error: Invalid input. Please enter again.\n");
            isValid = 0;
        }

        int len = strlen(newUser.email);
        if (len < 11 || strcmp(newUser.email + len - 10, "@gmail.com") != 0) {
            printf("Error: Email must end with @gmail.com. Please enter again.\n");
            isValid = 0;
        }

    } while (isValid == 0);

    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);

    printf("User added successfully and saved to file.\n");
}

void searchUser() {
	FILE *file = fopen("Userinfor.bin", "rb"); 
    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }
    
    char searchName[50];
    printf("Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0; 
    int found = 0;
    printf("\n==========================================================================================\n");
    printf("| %-12s | %-20s | %-25s | %-12s | %-5s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("==========================================================================================\n");
    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, searchName) != NULL) { 
            found = 1;
            printf("| %-12s | %-20s | %-25s | %-12s | %-5s |\n",
                   users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
            printf("------------------------------------------------------------------------------------------\n");
        }
    }
}

