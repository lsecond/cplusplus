/*  ISBN.CPP
/   this program for check if the string is valid and register .
/   subfuncition will be call from ISBNPrefix.cpp.    
/   jiang liu 
/   (066888058)
*/ 

FILE* open(const char filename[]);
int isRegistered(FILE* fp, int area);
int minNoDigits(FILE* fp, int area);
int isRegistered(FILE* fp, int area, const char publisher[]);
int close(FILE* fp);

