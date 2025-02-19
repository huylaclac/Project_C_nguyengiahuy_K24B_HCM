// user.c chua dinh nghia ham

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "user.h"
#include "admin.h"

User loggedUser;

// MENU chuc nang nguoi dung 
void UserMENU() {
    int choice;
    if(logUser()) {
        printf("Error: Login failed.\n");
        return;
    }
    do{
        userInfor();
        printf("\n=== User Management ===\n");
        printf("1. Edit Information\n");
        printf("2. changePassword\n"); 
        printf("3. Return.\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: printf("Editing information.\n"); editUserInfor(); break;
            case 2: printf("changepassword.\n"); changePassword();
            case 3: printf("Exiting User Management.\n"); return;
            default: system("cls"); printf("\033[31m Invalid choice. Please try again! \033[0m\n"); }
        
    }while(choice != 3);
}

// dang nhap nguoi dung  
int logUser() {
    FILE *file;
    char inputId[13], inputPhone[16];
    User user;

    if((file = fopen("Userinfor.bin", "rb")) == NULL) {
        printf("\033[31m No user data found. \033[0m\n");
        return 0; }

    while(1) {    
        rewind(file); 
        printf("\n=== User Login ===\n");
        printf("Enter ID: ");
        scanf(" %12[^\n]", inputId);
        printf("Enter password (phone number): ");
        getPassword(inputPhone);        

        while(fread(&user, sizeof(User), 1, file)) {  
            if (strcmp(user.id, inputId) == 0 && strcmp(user.phone, inputPhone) == 0) {  
                if(strcmp(user.status, "locked") == 0) {  
                    printf("\033[31m Your account is locked.\033[0m\n");
                    fclose(file);
                    return 1;
                }

                printf("Login successful! Welcome, %s.\n", user.name);
                loggedUser = user;  // gán thong tin nguoi dung vao bien toan cuc  
                fclose(file);
                return 0; 
            }
        }
        printf("\033[31m Incorrect ID or phone number. Try again! \033[0m\n");
    }

    fclose(file);
    return 0;
}

// ham hien thong tin nguoi dung  
void userInfor() {
    printf("\n==================================================================================================\n");
    printf("|%-15s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
    printf("==================================================================================================\n");
    printf("|%-15s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", loggedUser.id, loggedUser.name, loggedUser.gender == 1 ? "Male" : "Female", loggedUser.email, loggedUser.phone, loggedUser.status);
    printf("--------------------------------------------------------------------------------------------------\n");
}

// ham chinh sua thong tin nguoi dung 
void editUserInfor() {
    FILE *file = fopen("Userinfor.bin", "rb+"); 
    if(file == NULL) {
        printf("\033[31m Cannot open user data file! \033[0m\n");
        return;
    }
    User user;
    int found = 0;
    while(fread(&user, sizeof(User), 1, file)) {
        if(strcmp(user.id, loggedUser.id) == 0) { 
            found = 1;

            printf("\n=== Current Information ===\n");
            printf("ID: %s\n", user.id);
            printf("Name: %s\n", user.name);
            printf("Gender: %s\n", (user.gender == 1) ? "Male" : "Female");
            printf("Email: %s\n", user.email);
            printf("Phone: %s\n", user.phone);
            printf("Status: %s\n", user.status);
           
            do {
                printf("\nEnter new name: ");
                scanf(" %[^\n]", user.name);
                if (strlen(user.name) == 0) {
                    printf("\033[31m Name cannot be empty! Please enter again. \033[0m\n");
                }
            } while (strlen(user.name) == 0);
                   
            printf("Enter new email: ");
            scanf(" %[^\n]", user.email);

          
            printf("Enter new phone number: ");
            scanf(" %[^\n]", user.phone);
            
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file); 
            fflush(file); 
           
            loggedUser = user;

            printf("\033[32m Information updated successfully! \033[0m\n");
            break;
        }
    }

    if (!found) {
        printf("\033[31m User not found. \033[0m\n");
    }

    fclose(file);
}

// ham thay doi mat khau  
void changePassword() {
	readUserFromFile(); 
    FILE *file = fopen("Userinfor.bin", "rb+"); 
    if(file == NULL) {
       printf("\033[31m Cannot open user data file! \033[0m\n");
       return;
    }
    User user;
    int found = 0;
    char oldPassword[16], newPassword[16], confirmPassword[16];
    do{
        printf("\nEnter your current password (phone number): ");
        getPassword(oldPassword); 
        while(fread(&user, sizeof(User), 1, file)) {
            if (strcmp(user.id, loggedUser.id) == 0) { 
                found = 1;
                if (strcmp(user.phone, oldPassword) != 0) {
                    printf("\033[31m Incorrect current password! Please try again.\033[0m\n");
                    break;
                }
                break;
            }
        }
        if(!found) {
            printf("\033[31m User not found! \033[0m\n");
            break;
        }
    }while(strcmp(user.phone, oldPassword) != 0);  
    if(found) {
        do{
            printf("Enter new password: ");
            getPassword(newPassword);
            printf("Confirm new password: ");
            getPassword(confirmPassword);          
            if(strcmp(newPassword, confirmPassword) != 0) {
                printf("\033[31m The passwords do not match! Please try again.\033[0m\n");
            }
        }while(strcmp(newPassword, confirmPassword) != 0);  
            
        strcpy(user.phone, newPassword); 
        fseek(file, -sizeof(User), SEEK_CUR);
        fwrite(&user, sizeof(User), 1, file);
        loggedUser = user; 
        printf("\033[32m Password updated successfully! \033[0m\n");
    }
    fclose(file);
    
}
// ham quay tro lai menu truoc hoac thoat chuong trinh  

