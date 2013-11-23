/*  ISBN.CPP
/   this program for check if string is valid and register .
/   sub funcition will be call from ISBNPrefix.cpp.    
/   jiang liu (066888058)
*/  
#include <cstring>
#include<fstream>
#include<cstdlib>
#include "ISBNPrefix.h"
using namespace std;

// check if string is Valid.  
int isValid(const char str[]){
	int sum=0, i, rc=0;
	if(str!=0){
		for(i=0;i<9;i++){
			sum+=(str[i]-'0')*(10-i);
			/*just for the first 9 digit, and the (first digit*10) +(second digit*9)+ ...
			get the sum for the 9 digit.                                             */ 
			
			if(i==8&&str[i+1]=='X')//X means 10, so the sum must add 10
				sum=sum+10;
			if(i==8&&str[i+1]!='X')
				sum+=(str[i+1]-'0');
		}
		if(sum%11==0)//without remainder by 11 , valid !!
			rc=1;
	}
	return rc;
}

/* read data from str[], compare with record in file fp, if match, put in area[] ,
   publisher[] and title[]    */
int isRegistered(FILE* fp, const char str[], char area[], char publisher[], char title[]){
	int rc=1, i, areaint, aLenth=0, pLenth=0;
	/*    get the area code from str[] one digit by one digit,compare with 
	      file record.as soon as they match, put to the area then get the area 
	      length save in aLenth  */
	if(fp!=NULL){
		for(i=0;i<5;i++){
			area[i]=str[i];
			area[i+1]='\0';
			areaint=atoi(area);
			if(isRegistered(fp,areaint))/*check if areaint is match the record*/{
				i=5;
				aLenth=strlen(area);
			}
		}
		/* use the same way find the publisher put to the publisher[], the only 
		different is begin from str[aLenth]   */
		if(aLenth!=0){
			for(i=0;i<7;i++){
				publisher[i]=str[aLenth+i];
				publisher[i+1]='\0';
				if(isRegistered(fp,areaint,publisher)){
					i=7;
					pLenth=strlen(publisher);
				}
			}
		}
		else
			rc=0;
		// for the title from str[pLenth+aLenth]; 

		if(pLenth!=0){
			for(i=0;i<(9-pLenth-aLenth);i++){
				title[i]=str[pLenth+aLenth+i];
				title[i+1]='\0';
			}
		}
		else
			rc=0;	
	}
	return rc;	
}