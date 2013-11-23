/*  ISBNPrefix.cpp
/   5 functions are  in this program .
/   open and close for file operate.
/   Two isRegistered for check area and publisher.    
/   jiang liu 
/   (066888058)
*/  

#include <cstring>
#include<fstream>
#include<stdlib.h>
using namespace std;
// file open function
FILE* open(const char filename[]){
	FILE* fp=NULL;
	if ( filename != NULL){   // to avoid filename = NLLL
		
		fp=fopen(filename, "r"); 
		if(fp!=NULL)
			return fp;
		else
			return NULL; 
		}
	else 
		return fp;
}
//check if the area code equal the record in file. 
int isRegistered(FILE* fp, int area){
	int rc=0,a,publisher,title; 
	if(fp!=NULL){
		rewind(fp);
		do{
			fscanf(fp,"%d%d%d",&a,&publisher,&title);
			if(a==area)
				rc=1;
		}
		while(a!=area&&!feof(fp));//read to last record until find the match
		//otherwise do nothing, leave the rc with 0 as default.
	}
	return rc;
}
//test minimin digi for area function	

int minNoDigits(FILE* fp, int area){

int a, min=0;
	char publishs[10], publishe[10];
	if(fp!=NULL){
		rewind(fp);
		do{
			fscanf(fp,"%d%s%s",&a,publishs,publishe);
			if(a==area)
				min=strlen(publishs);// min is the area length
		}
		while(!feof(fp)&&min==0);
	}
	return min;
}


int isRegistered(FILE* fp, int area, const char publisher[]){
	int ip=atoi(publisher);
	int rc=0, max=0, min, a;
	int stringlen=strlen(publisher);
	char publishs[8], publishe[8];
	if(fp!=NULL){
		rewind(fp);
		do{
			fscanf(fp,"%d%s%s",&a,publishs,publishe);
			if(area==a&&stringlen==strlen(publishs)){
				max=atoi(publishe);
				min=atoi(publishs);
				// if the input number in the gap
				if(ip<=max&&ip>=min)
					rc=1;// in the gap
			}
		}
		while(!feof(fp)&&rc!=1);// not to the end of the file and rc not 0;


	}
	return rc;// find out the number in the gap, return true(1), else return fault(0); 
}
int close(FILE* fp){
	int rc=0;
	if(fp!=NULL){
		fclose(fp);
	rc=1;
	}
	return rc;
}
