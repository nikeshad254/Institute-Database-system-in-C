#include "template.h"

//dynamic pathing
char db[] = "all_dbs/";
char inst_file[] = "institutes.txt";
char admin_code[] = "admin_code.txt";
char c_data[] = "all_dbs/c_datas/";


//function declarartion
int data_count(char file_name[]);
int fetch_passcode();
int create_institute(char name[], char pass[]);
void fetch_institute(struct institute *arr);
int check_institute(int id, char pass[]);
int delete_institute(int id);
void access_one_institute(struct institute *arr, int id);
void generate_name(int Co_id, int mode, char *gen_name );


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

void generate_name(int Co_id, int mode, char *gen_name ){
	
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
	
}


void fetch_stupers(struct student *arr){
	
}

