#include "dB.h"


void main(){
	int opt, chance, data_no, verify;			//options declarations
	int i, j;			// loop vars			
	int admin_pass, prov_pass;		//password holder
	struct institute temp;			//temporary data holder of institute
	struct institute insta;			//data of one institute holder
	struct student tstu;			//temporary student.
	char name[300];
	
	do{
		Sleep(500);
		system("cls");
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
						
						printf("admin login sucessfull!!\n");
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
					
				}while(chance<=3);
				
				// only runs if passcode is verified as admin
				
				do{
					Sleep(1000);
					system("cls");
					printf("\tWelcome to admin panel\n....................................\n");
					printf("Choose task to perform: \n\t1. Create Institute\n\t2. Access Institute\n\t3. Delete Institute\n\t4. Exit \n===> ");
					scanf("%d",&opt);
					switch(opt){
						case 1:
							// create company
							printf("\n please give your company first name\n===> ");
							scanf("%s",temp.name);
							
							printf("\n provide a strong password(no space)\n===> ");
							scanf("%s",temp.pass);
							
							temp.inst_id = create_institute(temp.name, temp.pass);
							Sleep(500);
							printf("\ndon't forget , \nyour company id is ==>  %d", temp.inst_id);
							Sleep(2000);
						break;
						
						case 2:
							//access company
							chance = 0;
							do{
								Sleep(500);
								system("cls");
								
								printf("..................Accessing Company..................\n\n");
								printf("Enter your company id ==> ");
								scanf("%d",&temp.inst_id);
								printf("Enter password ==> ");
								scanf("%s",temp.pass);
								
								int result = check_institute(temp.inst_id, temp.pass);
								
								if(result != 0){	//access company validity
									access_one_institute(&insta, temp.inst_id);

									do{
										Sleep(500);
										system("cls");
										printf("............ %s Institute............\n\n", insta.name);
										
										printf("What do you want to do?\n1. Add Student Data\n2. Fetch Data\n3. View Latest Result\n4. Modify Data\n5. Exit\n====> ");
										scanf("%d",&opt);
										
										switch(opt){
											
											case 1:
												//add student data
												do{
													//fetching data.
													generate_path(temp.inst_id, PERS, name);
													data_no = data_count(name);

													struct student arr[data_no];
													fetch_stupers(temp.inst_id, arr);
													
													Sleep(500);
													system("cls");
													printf("Choose one from below:\n 1. New Student \t2. Old Student Marks\t3. Back\n==> ");
													scanf("%d",&opt);
													switch(opt){
														case 1:
															// new student
															printf("Adding New Data....\n");
															printf("First Name: ");
															scanf("%s",tstu.fname);
															printf("Last Name: ");
															scanf("%s",tstu.lname);
															
															do{
																opt = 101;
																printf("Roll no: ");
																scanf("%d",&tstu.roll_no);
																for(i=0; i<data_no; i++){
																	if(tstu.roll_no == arr[i].roll_no){
																		printf("\nThis roll number exists already.\n");
																		opt = 1;
																		break;
																	}
																}
															}while(opt != 101);
															printf("Gender(1 for male , 2 for female): ");
															scanf("%d",&tstu.gender);
															printf("Date of Birth (YYYY-MM-DD): ");
															scanf("%s",tstu.dob);
															printf("Phone: ");
															scanf("%s",tstu.phone);
															printf("Email: ");
															scanf("%s",tstu.email);
															
															printf("\n...Temporary Address...\nProvince: ");
															scanf("%s",tstu.address.temp_prov);
															printf("District: ");
															scanf("%s",tstu.address.temp_dist);
															printf("Street/Village: ");
															scanf("%s",tstu.address.temp_street);
															
															printf("\n...Permanent Address...\nProvince: ");
															scanf("%s",tstu.address.per_prov);
															printf("District: ");
															scanf("%s",tstu.address.per_dist);
															printf("Street/Village: ");
															scanf("%s",tstu.address.per_street);
															
															//id auto done from dB
															//password auto done from dB
															verify = add_stupers(temp.inst_id, tstu);
															printf("\n\nstudent id is ==> %d",verify);
															Sleep(2000);
															
															
															
														break;
														
														case 2:
															//old student marks
														break;
														
														case 3:
															printf("\ngetting back!!...........\n");
															Sleep(500);
														break;
														default:
															printf("\n this is invalid case. \n");
														
													}
												}while(opt!=3);
												
												
											break;
											
											case 2:
												//fetch data
											break;
											
											case 3:
												//view latest result
											break;
											
											case 4:
												//modify data
											break;
											
											case 5:
												//exit
												printf("\nExiting Now ..... \n");
												Sleep(1000);
												exit(0);
											break;
											
										}
										
									}while(opt!=5);
									
								}
								else{		//not valid password
									printf("\n.....INVALID PASSWORD OR ID.....\n");
									Sleep(500);
									chance++;
								}
								
							}while(chance<3);
							
							
						break;
						
						case 3:
							//delete company
							system("cls");
							printf("Provide company id to delete => ");
							scanf("%d",&temp.inst_id);
							printf("Password => ");
							scanf("%s",temp.pass);
							
							int result = check_institute(temp.inst_id, temp.pass);
							if(result != 0){
								
								do{
									system("cls");
									printf("Are you sure to delete?\n 1. Yes \t 2. No\n==> ");
									scanf("%d",&opt);
									
									if(opt == 1){
										result = delete_institute(temp.inst_id);
										if(result == 1){
											printf("\ndeletion sucessfull!!\n");
										}
										else{
											printf("\nfailed to delete!!\n");
										}
										break;
									}
									else if(opt == 2){
										printf("\ndeletion cancelled!! \n");
									}
									else{
										printf("\ninvalid response!!\t try again!!!!!!\n");
										Sleep(500);
									}
									
								}while(opt!=2);
							}
							
							else{
								printf("\nid or password invalid!!\n");
								Sleep(500);
							}
							
						break;
						
						case 4:
							//exit company
							printf("\nexiting now....");
							Sleep(500);
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
			
		}
	}while(opt!=3);
	
}
