/**************************************************
Copyright (C) jiang liu 066888058
File name: // ISBNPrefix.h
Author:jiang liu     Version:1.0   Date:2013-11-19
Dscription: 
   head file for ISBNPrefix.cpp.
Others: // oop244-assignment3		

*************************************************/

class ISBNPrefix{
private:
	FILE* fp;
	ISBNPrefix(const ISBNPrefix& source);
	ISBNPrefix& operator=(const ISBNPrefix& source);

public:	
	ISBNPrefix(const char* filename);
	bool isRegistered(int area) const;
	int minNoDigits(int area) const;
	bool isRegistered(int area, const char* publisher) const;
	~ISBNPrefix();


};


