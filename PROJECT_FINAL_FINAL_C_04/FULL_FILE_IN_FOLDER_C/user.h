// user.h chua nguyen mau ham  

#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

extern int userCount;          // dung ke bien toan cuc tu  
extern User users[MAX_USERS];           // 

int logUser();                 // dang nhap tai khoang nguoi dung                   
void userMENU();               // menu chuc nang  nguoi dung  

void userInfor();              // hien thong tin nguoi dung  
void editUserInfor();          // chinh sua thong tin nguoi dung  
void changePassword();         // thay doi mat khau nguoi dung 


#endif
