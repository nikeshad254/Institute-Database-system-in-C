#include "template.h"

//dynamic pathing
char db[] = "all_dbs/";
char inst_file[] = "institutes.txt";
char admin_code[] = "admin_code.txt";
char c_data[] = "all_dbs/c_datas/";

//function declarartion
int fetch_passcode();


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