#include "dB.h"

void main(){
	int opt;			//options declarations
	int i, j;			// loop vars
	do{
		printf("\tWelcome to Institute Database\n...............................................\n");
		printf("Who are you?\n1. User\n2. Admin\n3. Exit\n===> ");
		scanf("%d",&opt);
		switch(opt){
			case 1: // for user
			
			break;
			
			case 2: //for admin
			
			break;
			
			case 3:	//for exit
				printf("exiting.....");
				Sleep(500);
			break;
			
			default:	//invalid input
				printf("this is a invalid input!! try again\n");
				Sleep(500);
				system("cls");
				continue;
		}
	}while(opt!=3);
	
}
