// declaring all libaries we may need through out files
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int true = 1;
int false = 0;

// structure template
// for institute
struct institute{
	int inst_id;
	char name[20];
	char pass[16];
};
// for student
struct student{
	int stu_id;
	char pwd[20];
	int roll_no;
	char fname[20];
	char lname[20];
	int gender; // 1=male , 0=female ;;;
	char dob[30];
	int phone;
	char email[40];
	
	// address info:
	struct addres{
		char per_prov[20];
		char per_dist[20];
		char per_street[20];
		
		char temp_prov[20];
		char temp_dist[20];
		char temp_street[20];
	}address;
	
};
// for reasult
struct reasult{
	float sub[5];
	float per;
};