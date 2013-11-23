/**************************************************
Copyright (C) jiang liu 066888058
File name: // ISBNPrefix.h
Author:jiang liu     Version:1.0   Date:2013-10-24
Dscription: 
   head file for ISBNPrefix.cpp.
Others: // oop244-assignment2 		

*************************************************/

class ISBNPrefix{
	FILE* fp;
public:	
	ISBNPrefix(const char* filename);
	bool isRegistered(int area) const;
	int minNoDigits(int area) const;
	bool isRegistered(int area, const char* publisher) const;
	~ISBNPrefix();
};


