#include "dB.h"


void main(){
	int opt, inopt, chance, data_no, verify, check, id;			//options declarations & frequent temp
	int i, j;			// loop vars			
	int admin_pass, prov_pass;		//password holder
	struct institute temp;			//temporary data holder of institute (through out(permanent) after verification),
	struct institute insta;			//data of one institute holder
	struct student tstu;			//temporary student.
	struct result tres;				//temporary result.
	char name[300];
	char gender[10];				//for gender confersion at displays.
	
	do{
		Sleep(500);
		system("cls");
		printf("\tWelcome to Institute Database\n...............................................\n");
		printf("Who are you?\n\t1. User\n\t2. Admin\n\t3. Exit\n===> ");
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
										
										printf("What do you want to do?\n\t1. Add Student Data\n\t2. Fetch Data\n\t3. View Latest Result\n\t4. Modify Data\n\t5. Exit\n====> ");
										scanf("%d",&opt);
										
										switch(opt){
											
											case 1:
												//add student data
												do{
													//fetching data.
													generate_path(temp.inst_id, PERS, name);
													data_no = data_count(name);
													
													
													struct student pers[data_no];
													fetch_stupers(temp.inst_id, pers);
													
													struct result acad[data_no];
													fetch_stuacad(temp.inst_id, acad);
													
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
																opt = 102;
																printf("Roll no: ");
																scanf("%d",&tstu.roll_no);
																for(i=0; i<data_no; i++){
																	if(tstu.roll_no == pers[i].roll_no){
																		printf("this roll no already exist try again!\n");
																		opt = 101;
																	}
																	
																}
															}while(opt == 101);
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
															printf("\n\nstudent id is ==> %d\n",verify);
															Sleep(2000);
															
															do{
																Sleep(500);
																system("cls");
																printf("Would you like to add marks?\n1. Yes\t2. No/Default(0)\n===> ");
																scanf("%d", &inopt);
																if(inopt == 1){
																	//add mark mannually
																		system("cls");
																		printf("Allocating marks.........\n");
																		tres.stu_id = verify;	//verify is id holder of student just added
																		printf("subject one: ");
																		scanf("%f",&tres.sub[0]);
																		printf("subject two: ");
																		scanf("%f",&tres.sub[1]);
																		printf("subject three: ");
																		scanf("%f",&tres.sub[2]);
																		printf("subject four: ");
																		scanf("%f",&tres.sub[3]);
																		printf("subject five: ");
																		scanf("%f",&tres.sub[4]);
																		add_stuacad(temp.inst_id, tres);
																		printf("Added data sucessfully!!\n");
																		Sleep(500);
																		
																		do{
																			system("cls");
																			printf("Would you like to update roll numbers?\n 1. Yes \n2. No/Exit \n\n==> ");
																			scanf("%d",&opt);
																			if(opt == 1){
																				update_rollno(temp.inst_id);
																				printf("\n Roll no Updated\n");
																				Sleep(500);
																				break;
																			}
																			else if(opt == 2){
																				printf("\nexiting..........\n");
																				
																				Sleep(500);
																				break;
																			}
																			else{
																				printf("\nInvalid case please try again!\n");
																				Sleep(500);
																			}
																			
																			
																		}while(1==1);
																		
																		
																		
																		break;
																}
																else if(inopt == 2){
																	//default case of all 0 marks and auto update roll no.
																	tres.stu_id = verify;
																	tres.sub[0] = 0;
																	tres.sub[1] = 0;
																	tres.sub[2] = 0;
																	tres.sub[3] = 0;
																	tres.sub[4] = 0;
																	
																	add_stuacad(temp.inst_id, tres);
																	
																	update_rollno(temp.inst_id);
																	printf("data added and roll updated!! ");
																	Sleep(500);
																	
																	break;
																	
																}
																else{
																	printf("\n Invalid case!! \n");
																}

															}while(inopt!=1 || inopt!=2);
																
															
															opt = 3; 	//direct back!
														break;
														
														case 2:
															//old student marks
															system("cls");
															printf("List of student id and marks are:- \n\n");
															printf("Student ID\tSubject One\t Subject Two\tSubject three\tSubject Four\tSubject Five\tPercentage\n");//acad has scope
															for(i=0; i<data_no; i++){
																printf("%d\t\t%f\t%f\t%f\t%f\t%f\t%f\n", acad[i].stu_id, acad[i].sub[0], acad[i].sub[1], acad[i].sub[2], acad[i].sub[3], acad[i].sub[4], acad[i].per);
																
															}
															do{
																printf("\n\nGive id to modify==> ");
																scanf("%d", &tres.stu_id);
																check = check_isdata(temp.inst_id, ACAD, tres.stu_id);
																if(check == 1){
																	system("cls");
																	printf("Student id found - %d\n",tres.stu_id);
																	break;
																}
																else{
																	printf("\ninvalid Such id not found!!");
																	
																}

															}while(1 == 1);
															
															delete_stuacad(temp.inst_id, tres.stu_id);
															printf("Subject One marks ==> ");
															scanf("%f",&tres.sub[0]);
															printf("Subject Two marks ==> ");
															scanf("%f",&tres.sub[1]);
															printf("Subject Three marks ==> ");
															scanf("%f",&tres.sub[2]);
															printf("Subject Four marks ==> ");
															scanf("%f",&tres.sub[3]);
															printf("Subject Five marks ==> ");
															scanf("%f",&tres.sub[4]);
															
															add_stuacad(temp.inst_id, tres);
															
															update_rollno(temp.inst_id);
															
															printf("\nData added and roll updated too!!\n");
															Sleep(500);
															opt = 3;

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
												do{
													Sleep(500);
													system("cls");
													generate_path(temp.inst_id, PERS, name);
													data_no = data_count(name);

													struct student pers[data_no];
													fetch_stupers(temp.inst_id, pers);
													
													struct result acad[data_no];
													fetch_stuacad(temp.inst_id, acad);
													
													
													printf("Fetching datas .................... \n");
													
													printf("What would you like to do \n\t 1. Fetch all Data\n\t 2. Fetch all Personal data\n\t 3. Fetch all Academic data\n\t 4. Fetch One Student data\n\t 5. Back\n ===> ");
													scanf("%d",&opt);
													switch(opt){
														case 1:
															//fetch all data
															system("cls");
															printf("\n\n----------------Persosnal Data-----------------\n");
															printf("ID\tRoll No\tGender\tDOB\t\tPhone\tEmail\t\tName\t\tPermanent Address\tTemporary Address\n");
															for(i=0; i<data_no; i++){
																if(pers[i].gender == 1){
																	strcpy(gender, "Male");
																}
																else if(pers[i].gender == 2){
																	strcpy(gender, "Female");
																}
																else{
																	strcpy(gender, "Not Found");
																}
																
																printf("%d\t%d\t%s\t%s\t%s\t%s",pers[i].stu_id, pers[i].roll_no, gender, pers[i].dob, pers[i].phone, pers[i].email);
																
																if(strlen(pers[i].email)<10){	//2 tab size.
																	printf("\t");
																}
																printf("\t%s %s", pers[i].fname, pers[i].lname);
																if(strlen(pers[i].lname) < 5){
																	printf("\t");
																}
																printf("\t%s,%s,%s", pers[i].address.per_prov, pers[i].address.per_dist, pers[i].address.per_street);
																
																if(strlen(pers[i].address.per_street) < 5){
																	printf("\t");
																}
																printf("\t %s,%s,%s", pers[i].address.temp_prov, pers[i].address.temp_dist, pers[i].address.temp_street);
																printf("\n");
																
															}
															
															
															printf("\n\n------------------Academic Data-------------------\n");
															printf("Student ID\tSubject One\t Subject Two\tSubject three\tSubject Four\tSubject Five\tPercentage\n");//acad has scope
															for(i=0; i<data_no; i++){
																printf("%d\t\t%f\t%f\t%f\t%f\t%f\t%f\n", acad[i].stu_id, acad[i].sub[0], acad[i].sub[1], acad[i].sub[2], acad[i].sub[3], acad[i].sub[4], acad[i].per);
															}
															printf("\n\npress 1 to exit!! data view mode ");
															do{
																printf("===> ");
																scanf("%d", &inopt);
																
																if(inopt == 1){
																	printf("\nexiting fetch all view ..........\n");
																	Sleep(500);
																}
																else{
																	printf("\ninvaild, try again ");
																}
															}while(inopt!=1);
															opt = 101;
															
															
														break;
														
														case 2:
															//fetch personal data
															system("cls");
															printf("\n----------------Persosnal Data-----------------\n\n");
															printf("ID\tRoll No\tGender\tDOB\t\tPhone\tEmail\t\tName\t\tPermanent Address\tTemporary Address\n");
															for(i=0; i<data_no; i++){
																if(pers[i].gender == 1){
																	strcpy(gender, "Male");
																}
																else if(pers[i].gender == 2){
																	strcpy(gender, "Female");
																}
																else{
																	strcpy(gender, "Not Found");
																}
																
																printf("%d\t%d\t%s\t%s\t%s\t%s",pers[i].stu_id, pers[i].roll_no, gender, pers[i].dob, pers[i].phone, pers[i].email);
																
																if(strlen(pers[i].email)<10){	//2 tab size.
																	printf("\t");
																}
																printf("\t%s %s", pers[i].fname, pers[i].lname);
																if(strlen(pers[i].lname) < 5){
																	printf("\t");
																}
																printf("\t%s,%s,%s", pers[i].address.per_prov, pers[i].address.per_dist, pers[i].address.per_street);
																
																if(strlen(pers[i].address.per_street) < 5){
																	printf("\t");
																}
																printf("\t %s,%s,%s", pers[i].address.temp_prov, pers[i].address.temp_dist, pers[i].address.temp_street);
																printf("\n");
																
															}
															
															printf("\n\npress 1 to exit!! data view mode ");
															do{
																printf("===> ");
																scanf("%d", &inopt);
																
																if(inopt == 1){
																	printf("\nexiting fetch all view ..........\n");
																	Sleep(500);
																}
																else{
																	printf("\ninvaild, try again ");
																}
															}while(inopt!=1);
															opt = 101;
															
														break;
															
														case 3:
															//fetch all academic
															system("cls");
															printf("\n------------------Academic Data-------------------\n\n");
															printf("Student ID\tSubject One\t Subject Two\tSubject three\tSubject Four\tSubject Five\tPercentage\n");//acad has scope
															for(i=0; i<data_no; i++){
																printf("%d\t\t%f\t%f\t%f\t%f\t%f\t%f\n", acad[i].stu_id, acad[i].sub[0], acad[i].sub[1], acad[i].sub[2], acad[i].sub[3], acad[i].sub[4], acad[i].per);
															}
															printf("\n\npress 1 to exit!! data view mode ");
															do{
																printf("===> ");
																scanf("%d", &inopt);
																
																if(inopt == 1){
																	printf("\nexiting fetch all view ..........\n");
																	Sleep(500);
																}
																else{
																	printf("\ninvaild, try again ");
																}
															}while(inopt!=1);
															opt = 101;
															
														break;
														
														case 4:
															//fetch of one person
															printf("Give student id to fetch data ==> ");
															scanf("%d", &id);
															
															check = check_isdata(temp.inst_id, PERS, id);
															
															if(check == 1){
																printf("\nvalid id....");
																Sleep(300);
																system("cls");
																
																printf("--------------Personal info--------------\n");
																fetch_one_stupers(temp.inst_id, id, &tstu);
																printf("Name: %s %s \nRoll No: %d \nStudent ID: %d\nPassword: %s\n", tstu.fname, tstu.lname, tstu.roll_no, tstu.stu_id, tstu.pwd);
																if(tstu.gender == 1){
																	strcpy(gender, "Male");
																}
																else if(tstu.gender == 2){
																	strcpy(gender, "Female");
																}
																else{
																	strcpy(gender, "Not Found");
																}
																printf("Gender: %s\nDate of Birth : %s\nPhone: %s\nEmail: %s\n", gender, tstu.dob, tstu.phone, tstu.email);
																printf("----------Permanent Address-----------\nProvinvce: %s\nDistrict: %s\nStreet/town: %s\n", tstu.address.per_prov, tstu.address.per_dist, tstu.address.per_street);
																printf("----------Temporary Address-----------\nProvinvce: %s\nDistrict: %s\nStreet/town: %s\n", tstu.address.temp_prov, tstu.address.temp_dist, tstu.address.temp_street);
																
																check = check_isdata(temp.inst_id, ACAD, id);
																if(check == 1){
																	fetch_one_stuacad(temp.inst_id, id, &tres);
																	printf("\n\n--------------Academic Data-------------\n");
																	printf("Subject One : %f\nSubject Two : %f\nSubject Three : %f\nSubject Four : %f\nSubject Five : %f\n", tres.sub[0], tres.sub[1], tres.sub[2], tres.sub[3], tres.sub[4]);
																	printf("Total scored : %f", tres.sub[0] + tres.sub[1] + tres.sub[2] + tres.sub[3] + tres.sub[4]);
																	printf("\n\nPercentage : %f", tres.per);
																	
																	
																	printf("\n\n Enter 1 to exit data view mode ");
																	do{
																		printf("===> ");
																		scanf("%d", &inopt);
																		if(inopt == 1){
																			printf("\n\n Exiting now ..........\n");
																			Sleep(500);
																			opt =101;
																		}
																		else{
																			printf("invalid, try again ");
																		}
																		
																		
																	}while(inopt != 1);
																	
																	
																}
																else{
																	printf("\n\n Academic data not found!!");
																}
															}
															else{
																printf("invalid id not found!!");
																Sleep(500);
																
																
															}
															
															
															
														break;
														
														case 5:
															//exit or back
															
															printf("\n Getting Back ...............\n ");
															Sleep(500);
															opt = 101;
														break;
														
														default:
															opt = 10;
															printf("that is invalid try again! ");
															Sleep(500);
													}
													
												}while(opt != 101);
												
											break;
											
											case 3:
												//view latest result
												do{
													
												
													Sleep(500);
													system("cls");
													
													update_rollno(128);
													generate_path(temp.inst_id, PERS, name);
													data_no = data_count(name);
	
													struct student perss[data_no];
													fetch_stupers(temp.inst_id, perss);
														
													struct result acads[data_no];
													fetch_stuacad(temp.inst_id, acads);
													
													printf("-------------------Viewing Latest Result---------------------\n\n");
													printf("Roll NO\tName\t\tID\tSubject One\tSubject Two\tSubject Three\tSubject Four\tSubject Five\t Percentage\n");
												
													for (i=0; i<data_no; i++){
														
														printf("%d\t%s %s", perss[i].roll_no, perss[i].fname, perss[i].lname);
														if(strlen(perss[i].lname)<5){
															printf("\t");
														}
														printf("\t%d\t%f\t%f\t%f\t%f\t%f\t%f%% \t",acads[i].stu_id, acads[i].sub[0], acads[i].sub[1], acads[i].sub[2], acads[i].sub[3], acads[i].sub[4], acads[i].per);
												
														printf("\n");
													}
													
													printf("\n\nif any error in result press 2, to exit press 1 .. ");
													do{
														printf("===> ");
														scanf("%d",&check);
														if(check == 2){
															printf("\n\nfixing issues.. and exititng ... \n");
															update_rollno(temp.inst_id);
															Sleep(500);
															inopt = 2;
															break;
														}
														else if(check == 1 ){
															printf("\n\nexiting data view mode........\n");
															Sleep(500);
															inopt = 1;
															break;
														}
														else{
															printf("\n invalid input!! try again ");
															
														}
														
													}while(1 == 1);
												
												}while(inopt != 1);
												
											break;
											
											case 4:
												//modify data
												do{
													Sleep(500);
													system("cls");
													printf("-----------Modifying Datas-----------\n");
													printf("What do you want to do?\n\t1. Update Roll no\n\t2. Edit Student Academic Data\n\t3. Edit Student Personal Data\n\t4. Edit Student All Data\n\t5. Delete Student Data\n\t6. Back\n===> ");
													scanf("%d",&opt);
													switch(opt){
														case 1:
															//update roll no
															system("cls");
															printf("updating roll on basis of result...........");
															update_rollno(temp.inst_id);
															Sleep(500);
														break;
														
														case 2:
															//Edit student acad
															system("cls");
															printf("\n------------Editing academic data----------\nplease provide student id ==> ");
															scanf("%d",&id);
															check = check_isdata(temp.inst_id, ACAD, id);
															if(check == 1){
																system("cls");
																tres.stu_id = id;
																
																printf("Subject One marks ==> ");
																scanf("%f",&tres.sub[0]);
																printf("Subject Two marks ==> ");
																scanf("%f",&tres.sub[1]);
																printf("Subject Three marks ==> ");
																scanf("%f",&tres.sub[2]);
																printf("Subject Four marks ==> ");
																scanf("%f",&tres.sub[3]);
																printf("Subject Five marks ==> ");
																scanf("%f",&tres.sub[4]);
																
																delete_stuacad(temp.inst_id, tres.stu_id);
																
																add_stuacad(temp.inst_id, tres);
																
																printf("\nWould you like to update roll no?\n\t1. NO & Save\t2. Yes & Save \n");
																do{
																	printf("\t==> ");
																	scanf("%d",&inopt);
																	if(inopt == 1){
																		//no
																		printf("\nData Saved and roll not updated!\n");
																		Sleep(500);
																		opt == 6;
																		break;
																		
				
																	}
																	else if(inopt == 2){
																		// yes
																		printf("\nData Saved and Roll no Updated\n");
																		update_rollno(temp.inst_id);
																		opt == 6;
																		Sleep(500);
																		break;
																	}
																	else{
																		//default
																		printf("\ninvalid case, try again ");
																	}
																	
																
																}while(1 == 1);
															}
															else{
																printf("\nStudent Data doesnt exit for that id!!\n");
																Sleep(500);
															}
															
															
														break;
														
														case 3:
															//edit student pers
															Sleep(500);
															system("cls");
															printf("\n------------Editing Personal data----------\nplease provide student id ==> ");
															scanf("%d",&id);
															check = check_isdata(temp.inst_id, PERS, id);
															if(check == 1){
																generate_path(temp.inst_id, PERS, name);
																data_no = data_count(name);
			
																struct student persdt[data_no];
																fetch_stupers(temp.inst_id, persdt);
														
																printf("--------Changing data --------\n");
																printf("First Name: ");
																scanf("%s",tstu.fname);
																printf("Last Name: ");
																scanf("%s",tstu.lname);
																
																printf("previous roll no is as it is.. \n");
																for(i=0; i<data_no; i++){
																	if(id == persdt[i].stu_id){
																		tstu.roll_no = persdt[i].roll_no;
																		printf("roll no = %d\n",tstu.roll_no);
																		break;
																	}
																}
																
																
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
																
																tstu.stu_id = id;
																//password auto done from dB
																
																delete_stupers(temp.inst_id, id);
																Sleep(30);
																verify = add_pers_with_id(temp.inst_id, tstu);
																
																printf("\n\nstudent id is ==> %d\n",verify);
																Sleep(1500);
																
								
															}
															else{
																printf("Error! Data for that ID doesn't Exist\n");
																Sleep(500);
																
															}
														break;
														
														case 4:
															//edit student all
															Sleep(500);
															system("cls");
															printf("\n------------Editing Personal data----------\nplease provide student id ==> ");
															scanf("%d",&id);
															check = check_isdata(temp.inst_id, PERS, id);
															if(check == 1){
																generate_path(temp.inst_id, PERS, name);
																data_no = data_count(name);
			
																struct student persdts[data_no];
																fetch_stupers(temp.inst_id, persdts);
														
																printf("--------Changing data --------\n");
																printf("First Name: ");
																scanf("%s",tstu.fname);
																printf("Last Name: ");
																scanf("%s",tstu.lname);
																
																printf("previous roll no is as it is.. \n");
																for(i=0; i<data_no; i++){
																	if(id == persdts[i].stu_id){
																		tstu.roll_no = persdts[i].roll_no;
																		
																		break;
																	}
																}
																
																
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
																
																tstu.stu_id = id;
																//password auto done from dB
																
																delete_stupers(temp.inst_id, id);
																
																verify = add_pers_with_id(temp.inst_id, tstu);
																
																printf("\n\nstudent id is ==> %d\n",verify);
																Sleep(1000);
																
																check = check_isdata(temp.inst_id, ACAD, verify);
																if(check != 1){
																	printf("acad data not found for that id\n\tStill..... ");
																	Sleep(500);
																}
																printf("-----------adding academic data---------\n");
																system("cls");
																tres.stu_id = verify;
																
																printf("Subject One marks ==> ");
																scanf("%f",&tres.sub[0]);
																printf("Subject Two marks ==> ");
																scanf("%f",&tres.sub[1]);
																printf("Subject Three marks ==> ");
																scanf("%f",&tres.sub[2]);
																printf("Subject Four marks ==> ");
																scanf("%f",&tres.sub[3]);
																printf("Subject Five marks ==> ");
																scanf("%f",&tres.sub[4]);
																
																delete_stuacad(temp.inst_id, tres.stu_id);
																
																add_stuacad(temp.inst_id, tres);
																
																printf("\nWould you like to update roll no?\n1. NO & Save\t2. Yes & Save \n");
																do{
																	printf("\t==> ");
																	scanf("%d",&inopt);
																	if(inopt == 1){
																		//no
																		printf("\nData Saved and roll not updated!\n");
																		Sleep(500);
																		opt == 6;
																		break;
																		
				
																	}
																	else if(inopt == 2){
																		// yes
																		printf("\nData Saved and Roll no Updated\n");
																		update_rollno(temp.inst_id);
																		opt == 6;
																		Sleep(500);
																		break;
																	}
																	else{
																		//default
																		printf("\ninvalid case, try again ");
																	}
																	
																
																}while(1 == 1);
																
															}
															else{
																printf("Error! Data for that ID doesn't Exist\n");
																Sleep(500);
																
															}
															
														break;
														
														case 5:
															//delete student
															do{
																system("cls");
																printf("Select one deletion:-\n\t1. Delete and update roll no\n\t2. Only detete\n\t3.Exit/Back \n====> ");
																scanf("%d",&opt);
																if(opt == 1 || opt == 2){
																	printf("Provide student id ==> ");
																	scanf("%d",&id);
																	check = check_isdata(temp.inst_id, PERS, id);
																	if(check == 1){
																		printf("\npersonal data found and deleted\n");
																		delete_stupers(temp.inst_id, id);
																		
																	}
																	else{
																		printf("\nPersonal data for id not found!\n");
																		
																	}
																	Sleep(500);
																	check = check_isdata(temp.inst_id, ACAD, id);
																	if(check == 1){
																		printf("\nAcademic data found and deleted\n");
																		delete_stuacad(temp.inst_id, id);
																	}
																	else{
																		printf("\nAcademic data for id not found\n");
																		
																	}
																	Sleep(500);
																	if(opt == 1){
																		printf("\nroll no updated \n");
																		update_rollno(temp.inst_id);
																		Sleep(500);
																	}
																	else{
																		printf("\nroll no not updated\n");
																	}
																	Sleep(1500);
																	opt = 3;
																}
																else if(opt == 3){
																	printf("\nGetting Back.........\n");
																	Sleep(500);
																}
																else{
																	printf("\ninvalid try again!!\n ");
																	Sleep(500);
																}
																
															}while(opt != 3);
															
															
															
														break;
														
														case 6:
															//back
														break;
														
														default:
															printf("this is invalid !!!\n");
															Sleep(500);
													}
													
													
												}while(opt != 6);
												
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
