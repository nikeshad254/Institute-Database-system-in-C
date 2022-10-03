#include "dB.h"



void main(){
	int opt, chance;			//options declarations
	int i, j;			// loop vars			
	int admin_pass, prov_pass;		//password holder
	do{
		printf("\tWelcome to Institute Database\n...............................................\n");
		printf("Who are you?\n1. User\n2. Admin\n3. Exit\n===> ");
		scanf("%d",&opt);
		switch(opt){
			case 1: // for user
			
			break;
			
			case 2: //for admin
				admin_pass = fetch_passcode();
				chance = 0;
				
				do{//loop for admin code verification only
					printf("admin is required to provide pass code:- ");
					scanf("%d",&prov_pass);
					
					if(prov_pass==admin_pass){
						
						printf("admin login sucessfull!!");
						break;	//ends password loop!!
						
					}else{
						
						chance++;
						if(chance==3){
							printf("\n no more tries -- Seems you are not admin!! \n\n BYE.......\n");
							exit(0);
						}else{
							printf("\nincorrect admin pass code, try again(%d)\n\n", chance);	
						}
					}
					
				}while(true);
				
				// only runs if passcode is verified as admin
				
				do{
					printf("\tWelcome to admin panel\n....................................\n");
					printf("Choose task to perform: \n\t1. Access Institute\n\t2. Create Institute\n\t3. Delete Institute\n\t4. Exit \n===> ");
					scanf("%d",&opt);
					switch(opt){
						case 1:
							// acess
						break;
						
						case 2:
							//create
						break;
						
						case 3:
							//delete
						break;
						
						case 4:
							//exit
							printf("\nexiting now....");
							Sleep(2000);
							exit(0);
						break;
						
						default:
							printf("this is a invalid input!! try again\n");
							Sleep(500);
							system("cls");
							
					}
					
				}while(opt!=4);
				
				
				
				
				
				
			break;
			
			case 3:	//for exit
				printf("exiting.....");
				Sleep(500);
			break;
			
			default:	//invalid input
				printf("this is a invalid input!! try again\n");
				Sleep(500);
				system("cls");
			
		}
	}while(opt!=3);
	
}
