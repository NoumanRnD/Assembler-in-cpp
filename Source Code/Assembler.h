 
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

 void ld();
  void jmp();
   void add();
    void labelCall();
 
int hex2int( char* hex)  ;
 
 struct label  
    {
        int location;
        char *label;
    };
    struct label labeltable[50];  
    int nooflabels = 0;  


 
    struct jumpinstruction   
    {
        int location;
        char *label;
    };
    struct jumpinstruction jumptable[100];  
    int noofjumps=0;   




 
    struct variable
    {
        int location;
        char *name;
    };
    struct variable variabletable[50];  
    int noofvariables = 0;




 
    struct ldiinstruction   
    {
        int location;
        char *name;
    };
    struct ldiinstruction lditable[100];
    int noofldis=0;
 
