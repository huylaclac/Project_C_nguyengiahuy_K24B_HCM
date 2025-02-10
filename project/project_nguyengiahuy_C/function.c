#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

User users[MAX_USERS];
int userCount = 0;

void MainMENU() {
    int choice;
    do {
        printf("*** %s ***\n\n", "Bank management system using C");
        printf("%25s\n", "CHOOSE YOUR ROLE");
        printf("%30s\n", "========================");
        printf("%16s\n", "[1] Admin.");
        printf("%15s\n", "[2] User.");
        printf("%27s\n", "[3] Exit the program.");
        printf("%30s\n", "========================");
        printf("%24s", "Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                displayUserMenu();
                break;
            case 2:
                printf("User menu is under development.\n");
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

void displayUserMenu() {
    int choice;
    do {
        printf("\n=== User Management ===\n");
        printf("1. Display user list\n");
        printf("2. Add a user\n");
        printf("3. Lock/Unlock user\n");
        printf("4. View user details\n");
        printf("5. Sort user list\n");
        printf("6. Search for a user\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                displayUsers();
                break;
            case 2:
                addUser();
                break;
            case 3:
                lockUnlockUser();
                break;
            case 4:
                viewUserDetails();
                break;
            case 5:
                sortUsers();
                break;
            case 6:
                searchUser();
                break;
            case 0:
                saveUsersToFile();
                printf("Exiting user management.\n");
                break;
            default:
                printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 0);
}

void displayUsers() {
    printf("\nUser List:\n");
    printf("%-20s %-30s %-15s %-10s\n", "ID", "Name", "Phone", "Status");
    for(int i = 0;i < userCount; i++) {
        printf("%-20s %-30s %-15s %-10s\n", users[i].id, users[i].name, users[i].phone, users[i].status);
    }
}

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("Cannot add more users.\n");
        return;
    }
    User newUser;
    printf("Enter ID: ");
    scanf("%s", newUser.id);
    printf("Enter name: ");
    scanf("%s", newUser.name);
    printf("Enter phone number: ");
    scanf("%s", newUser.phone);
    printf("Enter email: ");
    scanf("%s", newUser.email);
    printf("Enter username: ");
    scanf("%s", newUser.username);
    strcpy(newUser.password, newUser.phone);
    strcpy(newUser.status, "open");

    users[userCount++] = newUser;
    printf("User added successfully.\n");
}

