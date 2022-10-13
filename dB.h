#include "template.h"

//dynamic pathing
char db[] = "all_dbs/";
char inst_file[] = "institutes.txt";
char admin_code[] = "admin_code.txt";
char c_data[] = "c_datas/";


//function declarartion
int data_count(char file_name[]);
int fetch_passcode();
int create_institute(char name[], char pass[]);
void fetch_institute(struct institute *arr);
int check_institute(int id, char pass[]);
int delete_institute(int id);
void access_one_institute(struct institute *arr, int id);
void generate_path(int Co_id, int mode, char *gen_path );
void fetch_stupers(int Co_id, struct student *arr);
int add_stupers(int Co_id, struct student arr);
void fetch_stuacad(int Co_id, struct result *arr);
void add_stuacad(int Co_id, struct result marks);
int fetch_one_stupers(int Co_id, int stu_id, struct student *stu);
int fetch_one_stuacad(int Co_id, int stu_id, struct result *stu);
int check_isdata(int Co_id, int mode, int stu_id);


// counts number of data from any file
int data_count(char file_name[]){		//working
	char name[300];
	strcpy(name,db);
//	char name[]= "all_dbs\\";
	strcat(name,file_name);
	FILE *fp;
	fp = fopen(name,"r");
	if(fp == NULL){
		printf("error occured file not found!");
		exit(0);
	}
	char ch;
	int i=0;
	ch = fgetc(fp);
	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch == '\n'){
			i++;
		}
	}
	fclose(fp);
	return i;
}


int fetch_passcode(){
	char path[300];
	int pass;
	strcpy(path,db);
	strcat(path,admin_code);
	
	FILE *fp;
	fp = fopen(path,"r");
	if(fp==NULL){
		printf("\n\t...Error Ouccured...");
		exit(0);
	}
	fscanf(fp,"%d",&pass);
	fclose(fp);
	return pass;
}


int create_institute(char name[], char pass[]){
	int id, data_no;
	
	//this code is imp for fetching infos
	data_no = data_count(inst_file);
	struct institute insta[data_no];
	fetch_institute(insta);
//testing=>	printf("%s %s %s %s ",insta[0].name,insta[1].pass,insta[2].name, insta[3].name);
	
	FILE *fp;
	
	char path[300];
	strcpy(path,db);
	strcat(path,inst_file);		
	fp = fopen(path,"a");
	
	id = data_no - 1;
	id = insta[id].inst_id + 2;
	
	fprintf(fp,"%d %s %s\n", id, name, pass);
	
	fclose(fp);
	
	return id;
	
}

//fetch all institute data
void fetch_institute(struct institute *arr){ 	//completed working pass array of struct name , while array should be formed using function!
	int data_no,i;
	
	char path[300];
	strcpy(path,db);
	strcat(path,inst_file);	
	
	FILE *fp;
	
	data_no = data_count(inst_file);
	
	
	fp = fopen(path,"r");
	if(fp == NULL){
		printf("error occured file not found! - fetch institute");
		exit(0);
	}
	
	
	for(i=0; i<data_no; i++){
		fscanf(fp, "%d %s %s\n", &arr->inst_id, arr->name, arr->pass);
		arr++;
	}
	fclose(fp);
}

int check_institute(int id, char pass[]){
	
	int data_no, i;
	//this code is imp for fetching infos
		
	data_no = data_count(inst_file);
	
	struct institute insta[data_no];
	fetch_institute(insta);
//	testing=>	
//	printf("%s %s %s %s ",insta[0].name,insta[1].pass,insta[2].name, insta[9].name);

	for(i=0; i < data_no; i++){
//		printf("%d %s %s \n",insta[i].inst_id, insta[i].name, insta[i].pass);
		
		if( insta[i].inst_id == id && strcmp(insta[i].pass, pass) == 0){
			return i;
		}

	}
	return 0;
}

int delete_institute(int id){
	
	int data_no, i;
	//this code is imp for fetching infos
		
	data_no = data_count(inst_file);
	
	struct institute insta[data_no];
	fetch_institute(insta);
	
	char path[300];
	strcpy(path,db);
	strcat(path,inst_file);
	
	FILE *fp;
	fp = fopen(path, "w");
	
	for( i=0; i<data_no; i++){
		if(insta[i].inst_id != id){
			//print
			fprintf(fp,"%d %s %s\n", insta[i].inst_id, insta[i].name, insta[i].pass);
		}
	}
	fclose(fp);
	
	return 1;
}

// access only one institute and provide gives reasult.
void access_one_institute(struct institute *arr, int id){
	
	int i, data_no;
	
	data_no = data_count(inst_file);
	struct institute insta[data_no];
	fetch_institute(insta);
	
	for( i=0; i<data_no; i++){
		if(insta[i].inst_id == id){
			
			arr->inst_id = insta[i].inst_id;
			
			strcpy(arr->name, insta[i].name);
			strcpy(arr->pass, insta[i].pass);

			return;
		}
	}
	printf("error occured!!");
	exit(0);
}

void generate_path(int Co_id, int mode, char *gen_path ){
	char gen_name[100];
	struct institute temp;
	access_one_institute(&temp, Co_id);
	
	int count =0;
	do{
        count++;
        Co_id /= 10;
    } while(Co_id!= 0);
    
	char str[count];
	sprintf(str, "%d", temp.inst_id);
	
	strcpy(gen_name, str);
	strcat(gen_name, temp.name);
	
	if(mode == PERS){
		strcat(gen_name, "pers");
	}
	else if(mode == ACAD){
		strcat(gen_name, "acad");
	}
	strcat(gen_name, ".txt");
	
	strcpy(gen_path, c_data);
	strcat(gen_path, gen_name);
}


void fetch_stupers(int Co_id, struct student *arr){
	char name[300], path[300];
	int i;
//	strcpy(path, db);
	generate_path(Co_id, PERS, name);
	int data_no = data_count(name);
	
	strcpy(path,db);
	strcat(path,name);
	
	FILE *fp;
	fp = fopen(path, "r");
	if(fp == NULL){
		printf("error occured while opening file!!");
		exit(0);
	}
	
	for(i=0; i<data_no; i++){
		fscanf(fp, "%d %s %d %s %s %d %s %d %s %s %s %s %s %s %s\n", &arr->stu_id, arr->pwd, &arr->roll_no, arr->fname, arr->lname, &arr->gender, arr->dob, arr->phone, arr->email, arr->address.per_prov, arr->address.per_dist, arr->address.per_street, arr->address.temp_prov, arr->address.temp_dist, arr->address.temp_street);
		arr++;
	}
	
	fclose(fp);
	
	
}
int add_stupers(int Co_id, struct student arr){
	FILE *fp;
	char name[300], path[300];
	int i, id;
//	strcpy(path, db);
	generate_path(Co_id, PERS, name);	
	int data_no = data_count(name);
	
	struct student stu[data_no];
	fetch_stupers(Co_id, stu);
	
	id = stu[data_no - 1].stu_id + 3;
	arr.stu_id = id;
	
	strcpy(path,db);
	strcat(path,name);
	
	fp = fopen(path, "a");
	
	strcpy(arr.pwd, arr.fname);
	
	fprintf(fp,"%d %s %d %s %s %d %s %d %s %s %s %s %s %s %s\n", arr.stu_id, arr.pwd, arr.roll_no, arr.fname, arr.lname, arr.gender, arr.dob, arr.phone, arr.email, arr.address.per_prov, arr.address.per_dist, arr.address.per_street, arr.address.temp_prov, arr.address.temp_dist, arr.address.temp_street);
	
	
	fclose(fp);
	
	
	return id;
}

void fetch_stuacad(int Co_id, struct result *arr){
	char name[300], path[300];
	int i;
//	strcpy(path, db);
	generate_path(Co_id, ACAD, name);
	int data_no = data_count(name);
	
	strcpy(path,db);
	strcat(path,name);
	
	FILE *fp;
	fp = fopen(path, "r");
	
	for(i=0; i<data_no; i++){
		fscanf(fp, "%d %f %f %f %f %f %f\n" , &arr->stu_id, &arr->sub[0], &arr->sub[1], &arr->sub[2], &arr->sub[3], &arr->sub[4], &arr->per);
		arr++;
	}
	
	fclose(fp);
	
}


void add_stuacad(int Co_id, struct result marks){
	
	//calculation
	float total = marks.sub[0] + marks.sub[1] + marks.sub[2] + marks.sub[3] + marks.sub[4];
	marks.per = total/5;
	
	char name[100], path[100];
	generate_path(Co_id, ACAD, name);	
	
	strcpy(path,db);
	strcat(path,name);
	
	
	FILE *fp;
	fp = fopen(path, "a");
	if(fp==NULL){
		printf("error occured while file opening");
		exit(0);
	}
	
	fprintf(fp, "%d %f %f %f %f %f %f\n" ,marks.stu_id, marks.sub[0], marks.sub[1], marks.sub[2], marks.sub[3], marks.sub[4], marks.per);
	
	fclose(fp);
	
}
int fetch_one_stupers(int Co_id, int stu_id, struct student *stu){
	
	char name[300];
	int i;
//	strcpy(path, db);
	generate_path(Co_id, PERS, name);
	int data_no = data_count(name);
	struct student all[data_no];
	
	fetch_stupers(Co_id, all);
	
	for(i=0; i<data_no; i++){
		if(stu_id == all[i].stu_id){
			
			stu->stu_id = all[i].stu_id;
			strcpy(stu->pwd , all[i].pwd);
			stu->roll_no = all[i].roll_no;
			strcpy(stu->fname , all[i].fname) ;
			strcpy(stu->lname , all[i].lname) ;
			stu->gender = all[i].gender;
			strcpy(stu->dob , all[i].dob) ;
			strcpy(stu->phone , all[i].phone) ;
			strcpy(stu->email , all[i].email) ;
			
			strcpy(stu->address.per_prov , all[i].address.per_prov) ;
			strcpy(stu->address.per_dist , all[i].address.per_dist) ;
			strcpy(stu->address.per_street , all[i].address.per_street) ;
			
			strcpy(stu->address.temp_prov , all[i].address.temp_prov) ;
			strcpy(stu->address.temp_dist , all[i].address.temp_dist) ;
			strcpy(stu->address.temp_street , all[i].address.temp_street) ;
			
			return 1;
		}
	}
	return 0;
	
}
int fetch_one_stuacad(int Co_id, int stu_id, struct result *stu){
	char name[300];
	int i;
//	strcpy(path, db);
	generate_path(Co_id, ACAD, name);
	int data_no = data_count(name);
	struct result all[data_no];
	
	fetch_stuacad(Co_id, all);
	for(i=0; i<data_no; i++){
		if(stu_id == all[i].stu_id){
			
			stu->stu_id = all[i].stu_id;
			stu->sub[0] = all[i].sub[0];
			stu->sub[1] = all[i].sub[1];
			stu->sub[2] = all[i].sub[2];
			stu->sub[3] = all[i].sub[3];
			stu->sub[4] = all[i].sub[4];
			
			stu->per = all[i].per;
			return 1;
		}
	}
	return 0;
}

int check_isdata(int Co_id, int mode, int stu_id){
	char name[300];
	int i, data_no;
	
	if(mode == PERS){
		generate_path(Co_id, PERS, name);
		data_no = data_count(name);
		struct student arr[data_no];
		fetch_stupers(Co_id, arr);
		for(i=0; i<data_no; i++){
		
			if(stu_id == arr[i].stu_id){
				return 1;
			}
		}
	}
	else if(mode == ACAD){
		generate_path(Co_id, ACAD, name);
		data_no = data_count(name);
		struct result all[data_no];
		fetch_stuacad(Co_id, all);
		for(i=0; i<data_no; i++){
			if(stu_id == all[i].stu_id){
				return 1;
			}
		}
	}
	return 0;
}

int delete_stu_data(int Co_id, int Stu_id){
	char name[300];
	int i, data_no;
//	strcpy(path, db);
	generate_path(Co_id, ACAD, name);
	data_no= data_count(name);
	struct result all[data_no];
	
	generate_path(Co_id, PERS, name);
	data_no = data_count(name);
	struct student stu[data_no];
	return 0;
}
