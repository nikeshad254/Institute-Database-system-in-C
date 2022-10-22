// declaring all libaries we may need through out files
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define PERS 1001
#define ACAD 1010

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
	char pwd[50];
	int roll_no;
	char fname[50];
	char lname[50];
	int gender; // 1=male , 0=female ;;;
	char dob[50];
	char phone[13];
	char email[50];
	
	// address info:
	struct addres{
		char per_prov[50];
		char per_dist[50];
		char per_street[50];
		
		char temp_prov[50];
		char temp_dist[50];
		char temp_street[50];
	}address;
	
};
// for result
struct result{
	int stu_id;
	float sub[5];
	float per;
};