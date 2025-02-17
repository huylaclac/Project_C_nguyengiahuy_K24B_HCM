
#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"
// menu chinh gom cac chuc nang chinh va cac chuc nang phu 

void adminlog();int loginAdmin();void createAdminAccount();



void MainMenu();
void displayAdminMenu();

void displayUserInfor();

void addUser();
int isValidInput(const char *input, int type);

void searchMenu();
void searchUserByID(); 
void searchUserByName();
int isDuplicateUser(User *newUser);

void sortUserMenu();
void sortUser();

void lockUnlockUser();


void readUserFromFile(); 


void UserMENU();

void end();

#endif

