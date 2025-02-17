#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 
#include "admin.h"
#include "user.h"



User users[MAX_USERS];          // users la mot mang chua nhieu nguoi dung (kieu user) toi da max_user
int userCount = 0;              // day la mot bien toan cuc dung de biet so luong nguoi dung hien co 



// Menu chinh cua chuong trinh  
void MainMenu() {
    int choice;
    do {
        printf("*** %s ***\n\n", "Bank management system using C");
        printf("%20s\n", "CHOOSE YOUR ROLE");
        printf("%s\n","========================");
        printf("|%-22s|\n", "[1] Admin.");
        printf("|%-22s|\n", "[2] User.");
        printf("|%-22s|\n", "[3] Exit the program.");
        printf("%s\n", "========================");
        printf("%s", "Choose an option: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
        	
            case 1:
            	system("cls");
                adminlog() ;
                break;
                
            case 2:
               	system("cls");
            	UserMENU();
                break;
                
            case 3:
                end();
                break;
            default:
            	system("cls"); 
                printf("\033[31m Invalid choice. Please try again! \033[0m\n");
        }
    } while (choice != 3);
}



void displayAdminMenu() {
    int choice;
    do {
        printf("\n=== ADMIN Management ===\n");
        printf("-----------------------\n");
        printf("|%-21s|\n", "1. Display user list");
        printf("|%-21s|\n", "2. Add a user");
        printf("|%-21s|\n", "3. Sort user list");
        printf("|%-21s|\n", "4. Search for a user");
        printf("|%-21s|\n", "5. user unlock/lock");
        printf("|%-21s|\n", "7. Exit");
        printf("-----------------------\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
            	system("cls") ;
                displayUserInfor();
                break;
            case 2:
            	system("cls") ;
            	addUser(); 
                break;
            case 3:
            	system("cls") ;
            	sortUserMenu();
            	break;
            case 4:
            	system("cls") ;
            	searchMenu(); 
				break; 
			case 5: 
		    	system("cls") ;
			    lockUnlockUser();
				break;
			case 7:
				system("cls") ;
				printf("return MainMenu");
				return ; 
            default:
                printf(" \033[31m Invalid choice. Please try again! \033[0m\n");
        }
    } while (choice != 7);
}

void displayUserInfor() {
    readUserFromFile();      // goi lai ham doc file de cap nhat lai so nguoi dung tranh trg hop doc du lieu cu  

    if (userCount == 0) {
        printf("\033[31m No users found. \033[0m\n");
        return;
    }

    printf("\n================================================================================================\n");
    printf("|%-12s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
    printf("================================================================================================\n");

    for (int i = 0; i < userCount; i++) {
        printf("|%-12s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", users[i].id, users[i].name, users[i].gender == 1 ? "Male" : "Female", users[i].email, users[i].phone, users[i].status);
        printf("------------------------------------------------------------------------------------------------\n");
    }
}



void readUserFromFile() {
    FILE *file = fopen("Userinfor.bin", "rb");
    if (file == NULL) return;

    userCount = 0;
    while (fread(&users[userCount], sizeof(User), 1, file)) {
        userCount++;
    }
    fclose(file);
}

int isDuplicateUser(User *newUser) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, newUser->id) == 0 ||
            strcmp(users[i].email, newUser->email) == 0 ||
            strcmp(users[i].phone, newUser->phone) == 0 ||
            strcmp(users[i].name, newUser->name) == 0) {
            return 1;
        }
    }
    return 0;
}

int isValidInput(const char *input, int type) {
    if (strlen(input) == 0) return 0;

    switch (type) {
        case 1: 
        case 2: 
            for (int i = 0; input[i] != '\0'; i++)
                if (!isdigit(input[i])) return 0;
            break;
        case 3: 
            for (int i = 0; input[i] != '\0'; i++)
                if (!isalpha(input[i]) && input[i] != ' ') return 0;
            break;
        case 4: 
            if (strlen(input) < 11 || strcmp(input + strlen(input) - 10, "@gmail.com") != 0) return 0;
            break;
    }
    return 1;
}


void addUser() {
    readUserFromFile();
    FILE *file = fopen("Userinfor.bin", "ab");
    if (file == NULL) {
        printf("Cannot open file to save user.\n");
        return;
    }

    User newUser;

    do {
        while(1){
        	fflush(stdin); 
       		printf("\nEnter ID (numbers only, max 12 digits): ");
	        scanf("%[^\n]", newUser.id);
			if(strlen(newUser.id) != 0)
			{
				break;		
			}		
    	}
        if (!isValidInput(newUser.id, 1) || strlen(newUser.id) != 12)
            printf("\033[31m Invalid ID. Please enter again. \033[0m\n");
    } while (!isValidInput(newUser.id, 1) || strlen(newUser.id) != 12);

   do {
        while(1){
        	fflush(stdin); 
       		printf("\nEnter NAME: ");
	        scanf("%[^\n]", newUser.name);
			if(strlen(newUser.name) != 0)
			{
				break;		
			}		
    	}
        if (!isValidInput(newUser.name, 3) || strlen(newUser.name) > 12)
            printf("\033[31m Invalid ID. Please enter again. \033[0m\n");
    } while (!isValidInput(newUser.name, 3) || strlen(newUser.name) > 12);


    do {
        printf("\nEnter gender (1 for Male, 2 for Female): ");
        scanf("%d", &newUser.gender);
		
        if (newUser.gender != 1 && newUser.gender != 2)
            printf("\033[31m Invalid gender. Please enter again. \033[0m\n");
    } while (newUser.gender != 1 && newUser.gender != 2);

    do {
        printf("\nEnter email (must end with @gmail.com, max 30 chars): ");
        scanf("%s", newUser.email);
        if (!isValidInput(newUser.email, 4) || strlen(newUser.email) > 30)
            printf("\033[31m Invalid email. Please enter again. \033[0m\n");
    } while (!isValidInput(newUser.email, 4) || strlen(newUser.email) > 30);

    do {
        printf("\nEnter phone number (numbers only, max 15 digits): ");
        scanf("%s", newUser.phone);
        if (!isValidInput(newUser.phone, 2) || strlen(newUser.phone) > 15)
            printf("\033[31m Invalid phone number. Please enter again. \033[0m\n");
    } while (!isValidInput(newUser.phone, 2) || strlen(newUser.phone) > 15);

    strcpy(newUser.status, "open");

    if (isDuplicateUser(&newUser)) {
        printf("\n\033[31m Error: Duplicate user information. Please enter again. \033[0m\n");
        fclose(file);
        return;
    }

    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);
    printf("\nUser added successfully and saved to file.\n");
}


void searchMenu() {
    int choice;
    
    printf("\n%-32s\n", "***** SEARCH USER MENU *****");
    printf("==================================\n");
    printf("|%-32s|\n", "1. Search by ID");
    printf("|%-32s|\n", "2. Search by Name");
    printf("|%-32s|\n", "3. Exit");
    printf("==================================\n");
    printf("Choose an option: ");

    scanf("%d", &choice);
    getchar(); 

    switch (choice) {
        case 1:  
            searchUserByID(); 
            break;
        
        case 2:  
            searchUserByName(); 
            break; 

        case 3:
            printf("Exiting search...\n");
            return;

        default:
            printf("\033[31m Invalid choice! Please try again. \033[0m\n");
    }
}

void searchUserByID() {
    FILE *file = fopen("Userinfor.bin", "rb");
    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }

    char searchID[13];  
    printf("Enter User ID to search: ");
    scanf("%s", searchID);

    User user;
    int found = 0;

    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.id, searchID) == 0) {
            printf("\n================================================================================================\n");
            printf("|%-12s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
            printf("================================================================================================\n");
            printf("|%-12s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", user.id, user.name, user.gender == 1 ? "Male" : "Female", user.email, user.phone, user.status);
            printf("------------------------------------------------------------------------------------------------\n");
            found = 1;
            break;  
        }
    }

    if (!found) {
        printf("\033[31m User with ID '%s' not found. \033[0m\n", searchID);
    }

    fclose(file);
}


void searchUserByName() {
	FILE *file = fopen("Userinfor.bin", "rb"); 
    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }
    
    char searchName[50];
    printf("Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);        // nhap vao  
    searchName[strcspn(searchName, "\n")] = 0;           // xoa ki tu xuong dong cua ham fgets de lai 
    int found = 0;                                       // bien found kiem tra tiem thay hay chua, gia su khong tim thay  
    printf("\n================================================================================================\n");
    printf("|%-12s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
    printf("================================================================================================\n");
    for (int i = 0; i < userCount; i++) {                        
        if (strstr(users[i].name, searchName) != NULL) {               // ham strstr kiem tra chuoi con trong chuoi cha   
            found = 1;
        printf("|%-12s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", users[i].id, users[i].name, users[i].gender == 1 ? "Male" : "Female", users[i].email, users[i].phone, users[i].status);
        printf("------------------------------------------------------------------------------------------------\n");
        }
    }
}

void sortUserMenu() {
    int choice;
    printf("\n=== Sort Users ===\n");
    printf("1. Sort A-Z\n");
    printf("2. Sort Z-A\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();
    switch(choice){
    case 1:
        sortUser(1);
        break;
    case 2:
        sortUser(0);
        break;
}
}

void sortUser(int ascending) {
    readUserFromFile();
    if (userCount == 0) {
        printf("\033[31m No users to sort.\n");
        return;
    }

    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            char firstChar1 = tolower(users[i].name[0]);
            char firstChar2 = tolower(users[j].name[0]);

            if ((ascending && firstChar1 > firstChar2) || (!ascending && firstChar1 < firstChar2)) {
                User temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    FILE *file = fopen("Userinfor.bin", "wb");
    if (!file) {
        printf("Error: Cannot open file to save sorted users.\n");
        return;
    }
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);

    printf("User list sorted and saved successfully!\n");
}


// 5. khoa mo khoa nguoi dung 
void lockUnlockUser() {
    int choice;
    char searchID[15];
// mo file ra ghi 
FILE *file = fopen("Userinfor.bin", "wb");
if (!file) {
    printf("Error: Cannot open file to save changes.\n");
    return;
}
size_t written = fwrite(users, sizeof(User), userCount, file);
fclose(file);
            printf("Enter User ID: ");
            scanf("%s", searchID);
            getchar();

            int found = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(users[i].id, searchID) == 0) {
                    found = 1;
                    if (strcmp(users[i].status, "open") == 0) {
                        printf("User is currently OPEN. Confirm to LOCK? (Y/N): ");
                        char confirm = getchar();
                        getchar();
                        if (confirm == 'Y' || confirm == 'y') {
                            strcpy(users[i].status, "locked");
                            printf("User has been locked successfully!\n");
                        } else {
                            printf("Action cancelled.\n");
                        }
                    } else if ( strcmp(users[i].status, "locked") == 0) {
                        printf("User is currently LOCKED. Confirm to UNLOCK? (Y/N): ");
                        char confirm = getchar();
                        getchar();
                        if (confirm == 'Y' || confirm == 'y') {
                            strcpy(users[i].status, "open");
                            printf("User has been unlocked successfully!\n");
                        } else {
                            printf("Action cancelled.\n");
                        }
                    } else {
                        printf("\033[31m User is already in the selected status. \033[0m\n");
                    }
                    break;
                }
            }

            if (!found) {
                printf("User ID not found! \033[0m\n");
            } else {
                FILE *file = fopen("Userinfor.bin", "wb");
                if (!file) {
                    printf("Error: Cannot open file to save changes.\n");
                    return;
                }
                fwrite(users, sizeof(User), userCount, file);
                fclose(file);
                printf("Changes saved successfully!\n");
            }
         
    readUserFromFile();  // ham doc lai file 
}

void end() {
    printf("\n%10s %5s %10s\n", "=========", "Thank you", "=========");
    printf("%10s %5s %10s\n", "=========", "See you soon", "=========");
    printf("--------------------------------\n");
}

void createAdminAccount() {
    FILE *file = fopen("Adminacc.txt", "r");
    if (file != NULL) { 
        fclose(file);
        printf("\033[31m Admin account already exists. Cannot create another.  \033[0m\n");
        return;
    }

    char username[50], password[50];

    printf("\n=== Create Admin Account ===\n");
    printf("Enter username: ");
    scanf(" %49[^\n]", username);

    printf("Enter password: ");
    scanf(" %49[^\n]", password);

    file = fopen("Adminacc.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot create admin account file.\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("Admin account created successfully!\n");
}


int loginAdmin() {
    FILE *file = fopen("Adminacc.txt", "r");
    if (file == NULL) {
        printf("\033[31m No admin account found. Please create an account first. \033[0m\n");
        return 0;
    }

    char storedUsername[50], storedPassword[50];
    char inputUsername[50], inputPassword[50];

    fscanf(file, "%s %s", storedUsername, storedPassword);
    fclose(file);

    printf("\n=== Admin Login ===\n");
    
    printf("Enter username: ");
    scanf(" %49[^\n]", inputUsername);

    printf("Enter password: ");
    scanf(" %49[^\n]", inputPassword);

    if (strcmp(storedUsername, inputUsername) == 0 && strcmp(storedPassword, inputPassword) == 0) {
        printf("Login successful! Welcome, Admin.\n");
        return 1;
    } else {
        printf("\033[31m Incorrect username or password. \033[0m\n");
        return 0;
    }
}


void adminlog() {
    int choice;
    do {
        printf("\n%20s\n", "=== Admin Account Management ===");
        printf("+-------------------------+\n"); 
        printf("|%-25s|\n", "1. Login");
        printf("|%-25s|\n", "2. Create Admin Account");
        printf("|%-25s|\n", "3. Exit");
        printf("+-------------------------+\n"); 
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                if (loginAdmin()) {
                system("cls"); 
                displayAdminMenu();
                return;
                }
                break;
            case 2:
            	system("cls"); 
                createAdminAccount();
                break;
            case 3:
                printf("Return...\n");
                return;
            default:
            	
                printf("\033[31m Invalid option. Please try again. \033[0m\n");
        }
    } while (choice != 3);
}
