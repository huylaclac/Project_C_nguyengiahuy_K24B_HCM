// admin.h chua nguyen mau ham

#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"
// menu chinh gom cac chuc nang chinh va cac chuc nang phu 

int loginAdmin();            // ham dang nhap tai khoang admin

void MainMenu();             // hien menu chinh  
void displayAdminMenu();     // hien admin menu

void displayUserInfor();     // hien tat ca thong tin nguoi dung 

void addUser();              // them nguoi dung 


void searchMenu();           // hien menu tiem kiem nguoi dung 
void searchUserByID();       // tiem kiem theo id
void searchUserByName();     // tiem kiem theo ten

void sortUserMenu();         // menu sap xep nguoi dung 
void sortUserAscending();    // sap xep tu A > Z
void sortUserDescending();   // sap xep tu z > A


void lockUnlockUser();       // khoa/mo khoa tai khoang 


void readUserFromFile();     // doc nguoi dung tu file 
              
void getPassword();          // khi nhap chuyen ki tu thanh ****

void end();                  // tam biet ket thuc



#endif

