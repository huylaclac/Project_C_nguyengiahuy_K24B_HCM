#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
#include "admin.h"
#include "user.h"


void UserMENU(){
	   int choice;
    do {
        printf("\n=== User Management ===\n");
        printf("1. displayUserinfor\n");
        printf("2. \n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
    switch(choice){
    	case 1:
    	displayUserInfor();
    	break;
    	
    	case 2:
    	break;
    	
    	case 3:
    	system("cls") ;
		printf("return MainMenu");
		system("color 09");
    	return ;
    	default:
    	system("cls"); 
		printf("\033[31m Invalid choice. Please try again! \033[0m\n"); 
	}
   }while(choice!=3);
}
