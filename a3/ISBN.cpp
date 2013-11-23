/**************************************************
Copyright (C) jiang liu 066888058
File name: // ISBN.cpp
Author:jiang liu     Version:1.0   Date:2013-11-19
Dscription: 
ISBNPrefix class manages access to the prefix table,
include 12 member functions;

Others: // oop244-assignment3
Function List:
 private:
 bool isRegistered(const ISBNPrefix& list);
 pulbic:
 1, ISBN::ISBN();
 2, ISBN::ISBN(const char* str, const ISBNPrefix& list);
 3, bool ISBN::empty() const;
 4, bool ISBN::isRegistered( const ISBNPrefix& list);
 5, bool ISBN::isRegistered() const;
 6, void ISBN::toStr(char* str) const;
 7, void ISBN::toStrWithStyle(char* str) const;
 8, void ISBN::display(ostream& os) const;
 9, bool ISBN::read(istream& is, const ISBNPrefix& list)
 10, void set(const ISBN& inISBN);
 friend :
 friend bool operator==(const ISBN& left, const ISBN& right);
 friend ostream& operator<<(ostream& os, const ISBN& isbn);
global function:
 10, int isValid(const char* str);

*************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include "ISBNPrefix.h"
#include "ISBN.h"
#include <iomanip>
#include <stdlib.h> 
using namespace std;

//A no arguement constructor that creates an ISBN object in a safe empty state

ISBN::ISBN(){    
	isbn[0]='\0';
	area[0]='\0';
	publisher[0]='\0';
	title[0]='\0';

}

// A two-arguement constructor to valid the input as well as to stores the area,
// publisher and title components
ISBN::ISBN(const char* str, const ISBNPrefix& list){
	if(isValid(str)){	
		strcpy(isbn,str);
		if(!isRegistered(list)){
			*this=ISBN();
			strcpy(isbn,str);
		}
	}
	else
		*this=ISBN();		
}


// A query that returns true if the object is in a safe empty state, 
// false otherwise

bool ISBN::empty() const{
	return (isbn[0]=='\0');
}


// A private modifier that receives a reference to an ISBNPrefix object and, if
// possible, decomposes an ISBN string into area, publisher and title components

bool ISBN::isRegistered( const ISBNPrefix& list){
	bool rc =true;
	int i, areaint, aLenth=0, pLenth=0;
	/*    get the area code from str[] one digit by one digit,compare with 
	      file record.as soon as they match, put to the area then get the area 
	      length save in aLenth  */
	
		for(i=0;i<5;i++){
			area[i]=isbn[i];
			area[i+1]='\0';
			areaint=atoi(area);
			if(list.isRegistered(areaint)){/*check if areaint is match the record*/
				i=5;
				aLenth=strlen(area);
			}
		}
		/* use the same way find the publisher put to the publisher[], the only 
		different is begin from str[aLenth]   */
		if(aLenth!=0){
			for(i=0;i<7;i++){
				publisher[i]=isbn[aLenth+i];
				publisher[i+1]='\0';
				if(list.isRegistered(areaint,publisher)){
					i=7;
					pLenth=strlen(publisher);
				}
			}
		}
		else
			rc=false;
		// for the title from str[pLenth+aLenth]; 

		if(pLenth!=0){
			for(i=0;i<(9-pLenth-aLenth);i++){
				title[i]=isbn[pLenth+aLenth+i];
				title[i+1]='\0';
			}
		}
		else
			rc=false;
		
	return rc;	
}

//A query, returns true if the object is registered, false otherwise

bool ISBN::isRegistered() const{
	return (area[0]!='\0'&& publisher[0]!='\0'&&title[0]!='\0');
}


//A query that passes the ISBN string through the function's parameter

void ISBN::toStr(char* str) const{
	strcpy(str,isbn);
}

// A query that returns the ISBN string through the function's parameter in the 
// form of a formatted C-style null-terminated string

void ISBN::toStrWithStyle(char* str) const{
	if(str!=NULL && isRegistered()){
		strcpy(str,area);
		strcat(str,"-");
		strcat(str,publisher);
		strcat(str,"-");
		strcat(str,title);
		strcat(str,"-");
		char s[2]={isbn[9],'\0'};
		strcat(str,s);       //for the last digit
	}
	else 
		toStr(str);

}

//A query that receives a reference to an ostream object and inserts the ISBN string in the current output style

void ISBN::display(ostream& os) const{
	char str[14]={"\0"};
	toStrWithStyle(str);
	os<<right<<setw(13)<<str;

}


//read function prompts for and accepts a string of up to ten characters.

bool ISBN::read(istream& is, const ISBNPrefix& list){
	char str[12];
	bool rc=true;
	do{
		cout << "ISBN (0 to quit) : ";
		is.get(str,12);
		is.ignore(1024,'\n');
		if (!strcmp(str,"0")){
			rc=false;
		}
		else{
			 if(strlen(str)<10){
				cout<<"Too few characters. Try again."<<endl;
			     	strcpy(str,"\0");
			}
			 if(strlen(str)==10){
				ISBN isbn(str, list);
			     	if (!isbn.empty()) {
			     		*this=isbn;
				 	rc=false;
				}
				else{
					cout << "Invalid check digit. Try agian"<<endl;
				}
			}
		}
	}while(rc==true);
	return (!this->empty());
}
// Global function to test if a string is valid;

int isValid(const char* str){
	int sum=0, i;
	bool rc=false;
	if(str!=0){
		for(i=0;i<9;i++){
			sum+=(str[i]-'0')*(10-i);
			/*just for the first 9 digit, and the (first digit*10) +(second digit*9)+ .
			get the sum for the 9 digit.                                             */ 
			
			if(i==8&&str[i+1]=='X')//X means 10, so the sum must add 10
				sum=sum+10;
			if(i==8&&str[i+1]!='X')
				sum+=(str[i+1]-'0');
		}
		if(sum%11==0)//without remainder by 11 , valid !!
			rc=true;
	}
	return rc;
}

/*************************************************************************/

//This operator returns true if both objects hold the same ISBN; false otherwise.  
//The objects need not hold the same style for this equality comparison to succeed. 
bool operator==(const ISBN& left, const ISBN& right) {
	bool rt = false;

	if(strcmp(left.isbn, right.isbn) == 0)       
		rt = true;

	return rt;
}

//This operator displays the ISBN in the form created by the display() member function.

ostream& operator << (ostream& os, const ISBN& isbn) {
	isbn.display(os);
	return os;
}

//initialize isbn object created in Order class

void ISBN::set(const ISBN& src) {
	strcpy(isbn, src.isbn);
	strcpy(area, src.area);
	strcpy(publisher, src.publisher);
	strcpy(title, src.title);
}
