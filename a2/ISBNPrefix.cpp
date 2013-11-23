/**************************************************
Copyright (C) jiang liu 066888058
File name: // ISBNPrefix.cpp
Author:jiang liu     Version:1.0   Date:2013-10-24
Dscription: 
ISBNPrefix class manages access to the prefix table,
include 5 member functions;

Others: // oop244-assignment2 
Function List: 		
1, ISBNPrefix::ISBNPrefix(const char* filename);
2, bool ISBNPrefix::isRegistered(int area) const;
3, int ISBNPrefix::minNoDigits(int area) const;
4, bool ISBNPrefix::isRegistered(int area, const char* publisher);
5, ISBNPrefix::~ISBNPrefix();
*************************************************/

#include <cstring>
#include <fstream>
#include <stdlib.h>


using namespace std;
#include "ISBNPrefix.h"

//   a one-argument constructor that receives a C-style, null-terminated string 
//   containing the name of a file that holds the prefix table;
ISBNPrefix::ISBNPrefix(const char* filename){
	fp=NULL;
	if ( filename != NULL){   // to avoid filename = NLLL		
		fp=fopen(filename, "r"); 		
	};
		
}

//check if the area code equal the record in file. 
bool  ISBNPrefix::isRegistered(int area) const{
	bool rc= false;
	int a,publisher,title; 
	if(fp!=NULL){
		rewind(fp);
		do{
			fscanf(fp,"%d%d%d",&a,&publisher,&title);
			if(a==area)
				rc=true;
		}
		while(a!=area&&!feof(fp));//read to last record until find the match
		//otherwise do nothing, leave the rc with 0 as default.
	}
	return rc;
}


//   a query that receives an area identifier and determines the minimum number of
//   digits in any publisher identifier registered under that area;
int ISBNPrefix::minNoDigits(int area) const{

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

//     A query that receives an area identifier along with a publisher identifier 
//   and determines if the publisher identifier is within a publisher range 
//   listed under that area;
bool ISBNPrefix::isRegistered(int area, const char* publisher) const{
	int ip=atoi(publisher);
	bool rc= false;
	int max=0, min, a;
	int stringlen=strlen(publisher);
	char publishs[10], publishe[10];
	if(fp!=NULL){
		rewind(fp);
		do{
			fscanf(fp,"%d%s%s",&a,publishs,publishe);
			if(area==a&&stringlen==strlen(publishs)){
				max=atoi(publishe);
				min=atoi(publishs);
				// if the input number in the gap
				if(ip<=max&&ip>=min)
					rc=true;// in the gap
			}
		}
		while(!feof(fp)&&rc!=1);// not to the end of the file and rc not 0;


	}
	return rc;// find out the number in the gap, return true, else return false; 
}

//a destructor that cleans up before the current object goes out of scope 

ISBNPrefix::~ISBNPrefix(){
	if(fp){
		fclose(fp);
	}
}
