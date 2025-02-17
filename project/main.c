#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "user.h"
#include "datatype.h" 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
    readUserFromFile();
	MainMenu(); 
	readUserFromFile();
	return 0;
}
