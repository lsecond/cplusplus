/**************************************************
Copyright (C) jiang liu 066888058
File name: // ISBN.h
Author:jiang liu     Version:1.0   Date:2013-11-19
Dscription: 
   head file for ISBN.cpp.
Others: // oop244-assignment3
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
	void set(const ISBN& inISBN);
	friend bool operator==(const ISBN& left, const ISBN& right);
	friend ostream& operator<<(ostream& os, const ISBN& isbn);
};


//Global function 
int isValid(const char* str);