// admin.c chua dinh nghia ham  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h> 

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
            case 1: system("cls"); if(loginAdmin())  {system("cls"); displayAdminMenu();} break;    // neu dieu kien tra ve cua ham logAmin la dung thi hien menu admin 
            case 2: system("cls"); UserMENU();        break; 
            case 3: end(); break;
            default: system("cls"); 
            printf("\033[31m Invalid choice. Please try again! \033[0m\n");
        }
        
    }while(choice != 3);}
  
        

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
        printf("|%-21s|\n", "6. Return: ");
        printf("-----------------------\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: system("cls"); displayUserInfor(); break;
            case 2: system("cls"); addUser(); break;
            case 3: system("cls"); sortUserMenu(); break;
            case 4: system("cls"); searchMenu(); break; 
			case 5: system("cls"); lockUnlockUser(); break;
			case 6: system("cls"); printf("return MainMenu\n"); MainMenu; return; 
            default:
            printf(" \033[31m Invalid choice. Please try again! \033[0m\n");
        }
        
    }while(choice != 6); }


void displayUserInfor() {
    readUserFromFile();      // goi lai ham doc file de cap nhat lai so nguoi dung tranh trg hop doc du lieu cu  
    
    if (userCount == 0) {   // kiem tra neu khong co bat ki nguoi dung nao  
    printf("\033[31m No users found. \033[0m\n");
    return; }
    printf("\n====================================================================================================\n");
    printf("|%-15s|%-20s|%-10s|%-25s|%-13s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
    printf("====================================================================================================\n");
    for(int i = 0; i < userCount; i++) {
    printf("|%-15s|%-20s|%-10s|%-25s|%-13s|%-10s|\n", users[i].id, users[i].name, users[i].gender == 1 ? "Male" : "Female", users[i].email, users[i].phone, users[i].status);
    printf("----------------------------------------------------------------------------------------------------\n"); }
}

// them nguoi dung  
void addUser() {
    readUserFromFile();
    FILE *file = fopen("Userinfor.bin", "ab");   // mo file ghi vao cuoi chu khong de file  
    if (file == NULL) {
      printf("Error: Cannot open file!\n");
      return; }                                  // mo khong thanh cong thoat khoi ham  
    User newUser;                                // bien luu nguoi dung moi nhap vao voi kieu du lieu user(struct) 

    // nhap id  
    do {
        while (1) {
        fflush(stdin); 
        printf("\nEnter ID: ");
        scanf("%[^\n]", newUser.id);         // doc tat ca cac ki tu ngoai tru \n (^ o day nghia la ngoai tru ) 
            if (strlen(newUser.id) != 0) {       // kiem tra chui rong  
            break; }     
        }
        
        if(strlen(newUser.id) != 12) {
          printf("\033[31m Error: ID must be a 12-digit CIC number. Please enter again. \033[0m\n");
          continue; 
        } else {
        	                                                 // kiem tra xem nguoi dung co nhap so hay khong  
        int validId = 1;                                 // bien gia su ban dau la hop le  
        for (int i = 0; newUser.id[i] != '\0'; i++) {    // vong lap den khi ket thuc chui ki tu(\0) 
            if (!isdigit(newUser.id[i])) {               // ham (isdigit) kiem tra xem trong chui id co chu khac ngoai number hay khong 
                validId = 0;                             // tra ve 0 vi sai  
                break; }
            }
            
        if(!validId) {
            printf("\033[31m Invalid ID. Please enter again. \033[0m\n");
            continue; }
        }
        
    } while (strlen(newUser.id) != 12 );        // dieu kien dung  

    // nhap name  
    do{ 
        fflush(stdin); 
        printf("\nEnter NAME: ");
        scanf("%[^\n]", newUser.name);
        if(strlen(newUser.name) == 0) {                                  // kiem tra neu do dai chui rong                                             
            printf("\033[31m Name cannot be empty! Please enter again. \033[0m\n");
        }else{
            int validName = 1;
            for (int i = 0; newUser.name[i] != '\0'; i++) {                  
                if (!(isalpha(newUser.name[i]) || newUser.name[i] == ' ')) { // isalpha la ham kiem tra xem cac ki tu nhap vao co phai chu cai hay khong  
                    validName = 0;                                     
                    break;
                }
            }
            if (!validName) {
                printf("\033[31m Invalid name. Please enter again. \033[0m\n");
            }
        }
} while(strlen(newUser.name) == 0 || !isalpha(newUser.name[0]));

    // nhap gioi tinh 1 or 2 
    do{
        printf("\nEnter gender (1 for Male, 2 for Female): ");
        int result = scanf("%d", &newUser.gender);
        if(result != 1) {   
            while (getchar() != '\n');  
            printf("\033[31m Invalid input. Please enter a number (1 or 2). \033[0m\n");
        }
        else if(newUser.gender != 1 && newUser.gender != 2) {
            printf("\033[31m Invalid gender. Please enter again. \033[0m\n");
        }
        else{
            break;  // thoat vong lap neu dung  
        }
    } while (1);  // tiep tuc vong lap neu sai 
    
    // nhap email  
    do{
        fflush(stdin);
        printf("\nEnter email (must end with @gmail.com): ");
        scanf(" %[^\n]", newUser.email);      
        if (strlen(newUser.email) < 11 || strcmp(newUser.email + strlen(newUser.email) - 10, "@gmail.com") != 0) {
            printf("\033[31m Invalid email. Please enter again. \033[0m\n");
        }
} while(strlen(newUser.email) < 11 || strcmp(newUser.email + strlen(newUser.email) - 10, "@gmail.com") != 0);
    
    // nhap sdt 
    do{
        while(1){
            fflush(stdin); 
            printf("\nEnter phone number (numbers only): ");
            scanf("%[^\n]", newUser.phone);
            if (strlen(newUser.phone) != 0) {
                break; 
            }
        }
        if(strlen(newUser.phone) !=10) {
            printf("\033[31m Invalid phone number. Please enter again. \033[0m\n");
            continue; 
        }else{
            int validPhone = 1;
            for (int i = 0; newUser.phone[i] != '\0'; i++) {
                if(!isdigit(newUser.phone[i])) {
                    validPhone = 0;
                    break;
                }
            }
        if(!validPhone) {
            printf("\033[31m Invalid phone number. Please enter again. \033[0m\n");
            continue; 
            }
        }
}while (strlen(newUser.phone) !=10 );

    // kiem tra trung lap thong tin nguoi dung  
    int isDuplicate = 1;
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].id, newUser.id) == 0 ||
            strcmp(users[i].email, newUser.email) ==0 ||
            strcmp(users[i].phone, newUser.phone) == 0 ||
            strcmp(users[i].name, newUser.name) ==0) {
            isDuplicate = 0;
            break; // co trung thi dung  
        }
    }

    if(!isDuplicate) {
        printf("\n\033[31m Error: Duplicate user information. Please enter again. \033[0m\n");
        fclose(file);
        return;
    }

    strcpy(newUser.status, "open");             // mac dinh tai khoang la open  
    fwrite(&newUser, sizeof(User), 1, file);    // luu vao file  
    fclose(file);
    printf("\nUser added successfully and saved to file.\n");
}


//4. MENU tim kiem 
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

    switch(choice) {
        case 1: searchUserByID(); break;
        case 2: searchUserByName(); break; 
        case 3: printf("Exiting search...\n"); return;
        
        default:
        printf("\033[31m Invalid choice! Please try again. \033[0m\n");
    }
}

void searchUserByID() {
    FILE *file = fopen("Userinfor.bin", "rb");
    if(file == NULL) {
        printf("\033[31m Error: Cannot open file. \033[0m\\n");
        return;
    }

    char searchID[13];  
    printf("Enter User ID to search: ");
    scanf("%s", searchID);
    User user;
    int found = 0;

    while(fread(&user, sizeof(User), 1, file)) {
        if(strcmp(user.id, searchID) == 0) {
            printf("\n===================================================================================================\n");
            printf("|%-15s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
            printf("===================================================================================================\n");
            printf("|%-15s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", user.id, user.name, user.gender == 1 ? "Male" : "Female", user.email, user.phone, user.status);
            printf("---------------------------------------------------------------------------------------------------\n");
            found = 1;
            break;  
        }
    }

    if(!found) {
        printf("\033[31m User with ID '%s' not found. \033[0m\n", searchID);
    }
    fclose(file);
}


void searchUserByName() {
	FILE *file = fopen("Userinfor.bin", "rb"); 
    if (file == NULL) {
        printf("\033[31m Error: Cannot open file. \033[0m\\n");
         return;
    }
    
    char searchName[50];
    printf("Enter name to search: ");
    fgets(searchName, sizeof(searchName), stdin);        // nhap vao  
    searchName[strcspn(searchName, "\n")] = 0;           // xoa ki tu xuong dong cua ham fgets de lai 
    int found = 0;                                       // bien found kiem tra tiem thay hay chua, gia su khong tim thay  
    printf("\n===================================================================================================\n");
    printf("|%-15s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", "ID", "Name", "Gender", "Email", "Phone", "Status");
    printf("===================================================================================================\n");
    for(int i = 0; i < userCount; i++) {                        
        if (strstr(users[i].name, searchName) != NULL) {               // ham strstr kiem tra chuoi con trong chuoi cha   
        found = 1;
        printf("|%-15s|%-20s|%-10s|%-25s|%-12s|%-10s|\n", users[i].id, users[i].name, users[i].gender == 1 ? "Male" : "Female", users[i].email, users[i].phone, users[i].status);
        printf("---------------------------------------------------------------------------------------------------\n");
        }
    }
}
//.

//3. MENU sap xep thoe 2 kieu a > z, z > a 
void sortUserMenu() {
    int choice;
    printf("\n=== Sort Users ===\n");
    printf("1. Sort A-Z\n");
    printf("2. Sort Z-A\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();
    switch(choice){
    case 1: sortUserAscending() ; break;
    case 2: sortUserDescending() ; break;
    
    default:
    printf("\033[31m Invalid option. Please try again. \033[0m\n");
}
}
// tiem kiem tang dan A > Z  
void sortUserAscending() {
    readUserFromFile();
	if(userCount ==0){
		printf("\033[31m No users to sort.\n"); 
		return ; 
	} 
	for( int i =0;i< userCount;i++){                        // vong lap ngoai di qua tat ca cac phan tu   
		for(int j =i+1; j< userCount-1; i++){               // vong lap trong so sanh tung cap phan tu  
			char firstchar1 = tolower(users[i].name[0]);    // ham tolower chuyen chu dau tien cua name[0] thanh chu thuong 
			char firstchar2 = tolower(users[j].name[0]);    // tuong tu tren 
			if(firstchar1 < firstchar2 ){                   // so sanh ki tu trong bang ma aski2 
				User temp = users[i];                       //khai tao bien tam luu tru thong tin co kieu du lieu User(struct) 
				users[i] =  users[j];                      
				users[j] =  temp ;
			}  
		} 
		FILE *file = fopen("Userinfor.bin", "wb");
		if(!file){
		printf("\033[31m Error: Cannot open file. \033[0m\n");
		return ;
		fwrite(users, sizeof(User), userCount,file);
		fclose(file);
		printf("users list sort (A > Z) and save successfully!"); 
		} 
	} 

	
    }
// giam dam Z > A 
void sortUserDescending() {
    readUserFromFile();
    if(userCount == 0) {
        printf("\033[31m No users to sort.\n");
        return;
    }

    for(int i =0; i< userCount -1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            char firstChar1 = tolower(users[i].name[0]);
            char firstChar2 = tolower(users[j].name[0]);
            
            if(firstChar1 < firstChar2) {
                User temp =users[i];
                users[i] = users[j];
                users[j]= temp;
            }
        }
    }

    FILE *file =fopen("Userinfor.bin", "wb");
    if (!file) {
        printf("\033[31m Error: Cannot open file. \033[0m\n");
        return;
    }
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);

    printf("User list sorted (Z-A) and saved successfully!\n");
}
//.

// 5. khoa mo khoa nguoi dung 
void lockUnlockUser() {
    char searchID[15];
    printf("Enter User ID: ");
    scanf("%s", searchID);
    int found = 0;
    readUserFromFile(); 
    
    for(int i =0; i< userCount; i++) {
        if(strcmp(users[i].id, searchID)== 0) {
            found= 1;
            printf("User is currently %s. Confirm to %s? (Y/N): ", users[i].status, strcmp(users[i].status, "open") == 0 ? "LOCK" : "UNLOCK");

            char confirm;
            scanf(" %c", &confirm);
            
            if(confirm == 'Y' || confirm =='y') {
              strcpy(users[i].status, strcmp(users[i].status, "open") == 0 ? "locked" : "open");
              printf("User has been %s successfully!\n", users[i].status);
            }else {
              printf("Action cancelled.\n");
            }
        break;    
        }
    }
    // truong hop khong tim thay  
    if(!found) {
        printf("\033[31m User ID not found! \033[0m\n");
    }else {
    // tiem thay thi ghi lai vao file  
        FILE *file = fopen("Userinfor.bin", "wb");
        if(!file) {
            printf("\033[31m Error: Cannot open file. \033[0m\n");
            return;
        }
        fwrite(users, sizeof(User), userCount, file);
        fclose(file);
        printf("Changes saved successfully!\n");
    }
}



int loginAdmin() {  
	FILE *file = fopen("Adminaccount1.bin", "rb");  
    if (file == NULL) {
        printf("\033[31m No admin account found. Please create an account first. \033[0m\n"); 
        return 0;
    }

    Admin storedAdmin;   
    fread(&storedAdmin, sizeof(Admin), 1, file);  
    fclose(file);
    char inputUsername[50], inputPassword[50];  
    while(1){
        printf("\n=== Admin Login ===\n");
        printf("Enter username: ");
        scanf(" %49[^\n]", inputUsername);   
        
        printf("Enter password: ");
        getPassword(inputPassword); 

        // So sánh username và password
        if(strcmp(storedAdmin.username, inputUsername) == 0 && strcmp(storedAdmin.password, inputPassword) == 0) {
            printf("Login successful! Welcome, Admin.\n");
            return 1;
        } else {
            printf("\033[31m Incorrect username or password. Please try again. \033[0m\n");
        }
    }
}

   
void getPassword(char* password) {
    char ch;
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13) {  
            password[i] = '\0';
            break;
        } else if (ch == 8) {  
            if (i > 0) {
                i--;
                printf("\b \b");  
            }
        } else if (ch >= 32 && ch <= 126) {  
            password[i] = ch;
            i++;
            printf("*");
        }
    }
    printf("\n");
}


// ham doc de biet so nguoi dung dang co thong qua mang users voi kieu du lieu User(struct) 
void readUserFromFile() {
    FILE *file = fopen("Userinfor.bin", "rb");
    if (file == NULL) return;
      userCount = 0;
      while (fread(&users[userCount], sizeof(User), 1, file)) { // fread doc file  
      userCount++;    
   }fclose(file); }
  
   
void end() {
    printf("\n%10s %5s %10s\n", "=========", "Thank you", "=========");
    printf("%10s %5s %10s\n", "=========", "See you soon", "=========");
    printf("--------------------------------\n");
}
