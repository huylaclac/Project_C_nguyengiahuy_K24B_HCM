// user.c chua dinh nghia ham

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "user.h"
#include "admin.h"

User loggedUser;             // bien toan cuc cho biet nguoi dung hine tai  

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
    char inputId[13], inputPhone[16];                          // khai bao 2 mang kieu ki tu luu tru thong tin nguoi dung nhap vao  
    User user;                                                 // bien kieu User dung de doc du lieu tu tep  

    if((file = fopen("Userinfor.bin", "rb")) == NULL) {
        printf("\033[31m No user data found. \033[0m\n");
        return 0; }

    while(1) {    
        rewind(file);                                          // dua con tro file ve dau  
        printf("\n=== User Login ===\n");
        printf("Enter ID: ");
        scanf(" %12[^\n]", inputId);                           // doc toi da 12 ki tu ( tranh tran bo nho ) 
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
    int count= userCount;
    FILE *file= fopen("Userinfor.bin", "rb");
    if(file == NULL) {
        printf("\033[31m Cannot open user data file! \033[0m\n");
        return;
    }
    fclose(file);
    
    int found = 0;
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].id, loggedUser.id) == 0) {        // de bt vi tri nguoi dung hien tai de chinh sua  
            found = 1;

            printf("\n=== Current Information ===\n");
            printf("ID: %s\n", users[i].id);
            printf("Name: %s\n", users[i].name);
            printf("Gender: %s\n", (users[i].gender == 1) ? "Male" : "Female");
            printf("Email: %s\n", users[i].email);
            printf("Phone: %s\n", users[i].phone);
            printf("Status: %s\n", users[i].status);
            
            printf("\nEnter new name: ");
            scanf(" %[^\n]", users[i].name);
            printf("Enter new email: ");
            scanf(" %[^\n]", users[i].email);
            printf("Enter new phone number: ");
            scanf(" %[^\n]", users[i].phone);
            loggedUser = users[i];                                       // luu thong tin nguoi dung hien tai vao loggedUser 
            
            break;
        }
    }

    if(!found) {
        printf("\033[31m User not found. \033[0m\n");
        return;
    }

    file =fopen("Userinfor.bin", "wb");
    if(file == NULL) {
        printf("\033[31m Eror!! \033[0m\n");
        return;
    }
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    printf("\033[32m Information updated successfully! \033[0m\n");
}

// ham thay doi mat khau  
void changePassword() {
    int found = 0;
    char oldPassword[16], newPassword[16], confirmPassword[16];         // khoi tao 3 bien mat khau cu, mat khau moi, va mat khau mmoi 2   
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].id, loggedUser.id)== 0) {
            found = 1;
            do{
                printf("\nEnter your current password (phone number): "); 
                scanf("%s", oldPassword);
                getchar();

                if(strcmp(users[i].phone, oldPassword) != 0) {
                    printf("\033[31m Incorrect current password! Please try again.\033[0m\n");
                }
            }while(strcmp(users[i].phone, oldPassword) != 0);          

            do{
                printf("Enter new password: "); 
                scanf(" %s", newPassword);
                getchar();
                printf("Confirm new password: ");
                scanf(" %s", confirmPassword);
                getchar();
              
                if(strcmp(newPassword,confirmPassword) != 0) {
                    printf("\033[31m The passwords do not match! Please try again.\033[0m\n");
            }
            }while(strcmp(newPassword, confirmPassword) != 0);
            strcpy(users[i].phone, newPassword);
            loggedUser = users[i];
            
            break;
    }
    }

    if(!found) {
        printf("\033[31m User not found! \033[0m\n");
        return;}
        
    FILE *file= fopen("Userinfor.bin", "wb");
    if(file == NULL) {
        printf("\033[31m Cannot write to user data file! \033[0m\n");
        return; }
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);

    printf("\033[32m Password updated successfully! \033[0m\n");
}

// ham quay tro lai menu truoc hoac thoat chuong trinh  

