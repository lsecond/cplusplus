/**************************************************
Copyright (C) jiang liu 066888058
File name: // ISBN.h
Author:jiang liu     Version:1.0   Date:2013-10-24
Dscription: 
   head file for ISBN.cpp.
Others: // oop244-assignment2 
Function List: 		

*************************************************/
#include <iostream>
using namespace std;
class ISBNPrefix;
class ISBN{
	char isbn[11];
	char area[6];
	char publisher[8];
	char title[7];
	bool isRegistered(const ISBNPrefix& list);
public:
	ISBN();
	ISBN(const char* str, const ISBNPrefix& list);
	bool empty() const;
	bool isRegistered() const;
	void toStr(char* str) const;
	void toStrWithStyle(char* str) const;
	void display(ostream& os) const;
	bool read(istream& is, const ISBNPrefix& list);
};


//Global function 
int isValid(const char* str);