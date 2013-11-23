/**************************************************
Copyright (C) jiang liu 066888058
File name: // Order.cpp
Author:jiang liu     Version:1.0   Date:2013-11-19
Dscription: 
  Order class manages a single bookstore order, 
where the order refers to one specific edition of 
a publication; that is, to one ISBN.

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

#include<cstring>
#include<iostream>
#include<stdlib.h>
using namespace std;
#include "ISBNPrefix.h"
#include "Order.h"
#include <iomanip>


//a no-argument constructor that creates an Order object in a safe empty state 

Order::Order(){
	ordered = 0;
	delivered = 0;	
	clientname =NULL;

}

//a one-argument constructor that receives a reference to an ISBN object and initializes an Order object for that ISBN

Order::Order(const ISBN& isbn){
	ordered=0;
	delivered=0;
	temp.set(isbn);
	clientname=NULL;
}

Order::~Order(){};

//receives a reference to an ISBN object and initializes an Order object for
// thatISBN and the address of a C-style null-terminated string containing the name of the client.

Order::Order(const ISBN& isbn, const char* nm){
	if(nm !=NULL){
		ordered=0;
		delivered=0;
		temp.set(isbn);
		clientname= new char[strlen(nm) +1];
		strcpy(clientname, nm);
	}	else{
		ordered=0;
		delivered=0;		
		clientname= NULL;
		
	}
}

// This function constructs an identical copy of the referenced object and 
//allocates separate memory for the object's instruction. 

Order::Order(const Order& source){
	ordered= source.ordered;
	delivered = source.delivered;
	temp.set(source.temp);
	if (source.clientname != NULL) {
         clientname = new char[strlen(source.clientname) + 1]; 
         // copy data from the original resource
         // to newly allocated resource
         strcpy(clientname, source.clientname);
     }
     else
         clientname = NULL;

}

// a query that receives a reference to an ISBN object and returns 
// true if the Order object is for that ISBN, false otherwise 

bool Order::has(const ISBN& isbn) const {
	return (temp == isbn);
}

// a query that returns the name held by the current object

void Order::name(char* str) const{
	strcpy(str, clientname);
}

//a query that returns the number of copies remaining on order in the current object

int Order::outstanding() const {
	return (ordered - delivered);       
}

// a modifier that receives a reference to an istream object and updates the 
//name held by the order based upon data recieved from input stream is
bool Order::client(istream& is){
	bool rt = false;
	char str[102];
	do{
		cout << "Name (0 to quit) : ";
		is.get(str,100);
		is.ignore(1024,'\n');
		if (!strcmp(str,"0")){			
			rt=false;
		}
		else if (strlen(str)<100){			
			clientname = new  char[strlen(str) + 1];
			strcpy(clientname, str);			
			rt=true;	  
	    }	  
		else{			
			cout << "name is too long"<<endl;
		}
			
	}while(rt==false);
	  	  
	  return rt;

}


//a modifier that receives a reference to an istream object and increases the number of copies 
//to be ordered based upon data received from input stream is 

bool Order::add(istream& is) {
	bool rt = false;
	int no;

	do{
		cout << "Quantity (0 to quit) : ";
		is >> no;  
		is.ignore(1024,'\n');

		if(no < 1)
			cout<< "Enter a positive number.  Try again." << endl;
		else{
			rt = true;                       
			ordered += no;       
		}
	}while(!rt);	  
	return rt;      
}

//a modifier that receives the number of copies to be added to the current order 

bool Order::add(int n){
	bool rt = false;

	if(n >0){
	   if(temp.isRegistered()){                
		rt = true;
		ordered = ordered + n;               
	   }
	}

	return rt;
}

//a modifier that receives a reference to an istream object and records receipt of 
//copies based upon data from the input stream 

bool Order::receive(istream& is){

	bool rt = false;
	int no;
	
	do{
		cout<<"Quantity (0 to quit) : ";
		is >> no;

		if(no < 0)
			cout<< "Enter a positive number.  Try again." << endl;

		if(no > outstanding())
			cout<< no <<"not on order.  Only "<< outstanding() << " are on order.  Try again."<<endl;



		if(no==0)
			cout << "**No delivery recorded!" << endl;
	} while(no > outstanding() ||  no < 0);               


	if(no){
		rt = true;
		delivered+=no;
	}

	return rt;
}

//a query that receives a reference to an ostream object and displays the current object on the output stream

void Order::display(ostream& os) const{
	os << right<< setw(13) << temp << setw(9)  << ordered << setw(11) << delivered<<" "<< left<< clientname;
}

//an non friend overloaded operator that receives a reference to an ostream object along with 
//a reference to an unmodifiable Order object and inserts that object's information into 
//the specified output stream  

ostream& operator << (ostream& os, const Order& order) {
	order.display(os);
	return os;
}

//	an assignment operator that receives a reference to an unmodifable Order 
//object and copies the information in that referenced object into the current object

Order&  Order::operator=(const Order& source){
	// check for self-assignment
     if (this != &source) {
         // shallow copy non-resource variable
		 ordered= source.ordered;
		 delivered = source.delivered;
		 temp.set(source.temp);
		 
         // deallocate previously allocated dynamic memory
         if (clientname != NULL) delete [] clientname;
         // allocate new dynamic memory, if needed
         if (source.clientname != NULL) {
             clientname = new char[strlen(source.clientname) + 1];
             // copy the resource data
             strcpy(clientname, source.clientname);
         }
         else
             clientname = NULL;
     }
     return *this;
}
