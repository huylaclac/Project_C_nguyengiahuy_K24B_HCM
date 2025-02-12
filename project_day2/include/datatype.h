#ifndef DATATYPE_H
#define DATATYPE_H

#define MAX_USERS 100
#include <stdbool.h>



typedef struct{
	char id[10];
	char name[30];
	bool gender;
	char phone[15];
	char email[40];
	char status[10];
	char password[40];
} User;

#endif


