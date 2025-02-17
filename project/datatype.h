#ifndef DATATYPE_H
#define DATATYPE_H

#define MAX_USERS 100
#include <stdbool.h>



typedef struct{
	char id[12];
	char name[30];
	bool gender;
	char phone[15];
	char email[40];
	char status[10];
	char password[40];
} User;


typedef struct{
	char adname[20];
	char password[30]; 
} Admin;



#endif


