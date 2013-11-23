/**************************************************
Copyright (C) jiang liu 066888058
File name: // Order.h
Author:jiang liu     Version:1.0   Date:2013-11-19
Dscription: 
  Head file for Order.cpp, detail information see
Oreder.cpp.

Others: // oop244-assignment3 
Function List: 		
1.	Order();
2.	Order(const ISBN& isbn);
3.	Order(const ISBN& isbn, const char* nm);
4.	Order(const Order& source);
5.	bool has(const ISBN& isbn) const;
6.	void name(char* str) const;
7.	int outstanding() const;
8.	bool client(istream& is);
9.	bool add(istream& is);
10.	bool add(int n);
11.	bool receive(istream& is);
12.	void display(ostream& os) const;
13.	Order& operator=(const Order& source);
14.	~Order();
*************************************************/

#include<cstdio>
#include<iostream>
#include "ISBN.h"
using namespace std;



class Order{
private:
	ISBN temp;
	int ordered;
	int delivered;
	char* clientname;
public:
	Order();
	Order(const ISBN& isbn);
	Order(const ISBN& isbn, const char* nm);
	Order(const Order& source);
	bool has(const ISBN& isbn) const;
	void name(char* str) const;
	int outstanding() const;
	bool client(istream& is);
	bool add(istream& is);
	bool add(int n);
	bool receive(istream& is);
	void display(ostream& os) const;
	Order& operator=(const Order& source);
    ~Order();
};

ostream& operator<<(ostream& os, const Order& order);
