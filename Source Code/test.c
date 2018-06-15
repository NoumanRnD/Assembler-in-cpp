#include "Assembler.h"
 
   char line[100];
   char *token = NULL;
    char *op1, *op2, *op3, *label;
    char ch;
    int  chch;

    int program[1000];
    int counter=0;   
     


void ldi(){
                	  
                    
                    op1 = strtok(NULL,"\n\t\r ");                                   
					op2 = strtok(NULL,"\n\t\r ");                                
					printf("\n\t%s\t%s   %s\n",strupr(token),op1,op2);		 
			 	  program[counter]=0x1000+hex2int(op1);                 
					printf("> %d\t%04x\n",counter,program[counter]);
					counter++;                                                   
					if ((op2[0]=='0')&&(op2[1]=='x'))                             
						{
						program[counter]=(int)strtol(op2+2, NULL, 0)&0xffff;           
						  printf("\n%d     \n",  program[counter]);     }
					else if ((  (op2[0])=='-') || ((op2[0]>='0')&&(op2[0]<='9')))      
					{
							program[counter]=atoi(op2)&0xffff;   
								  printf("ldi - 0 9 \n%d     \n",  program[counter]);    
						}
					else                                                           
					{                                                              
						lditable[noofldis].location = counter;   
						              
						op1=(char*)malloc(sizeof(op2));                        
						strcpy(op1,op2);                                       
						lditable[noofldis].name = op1;
						  printf("\n%d     \n",  op1);    
						noofldis++;
					}
					printf("> %d\t%04x\n",counter,program[counter]);
					counter++;              
	
}
 void ld(){
 	  op1 = strtok(NULL,"\n\t\r ");                 
                    op2 = strtok(NULL,"\n\t\r ");            
                    ch = (op1[0]-48)| ((op2[0]-48) << 3);    
                    program[counter]=0x2000+((ch)&0x00ff);   
                      printf("ld \n%d     \n",  program[counter]);    
                    counter++;       
 }
 void jmp(){
 	  op1 = strtok(NULL,"\n\t\r ");            
                    jumptable[noofjumps].location = counter; 
                      printf("location jmp %d \n",      jumptable[noofjumps].location );
                    op2=(char*)malloc(sizeof(op1));          
                    strcpy(op2,op1);                 
                    jumptable[noofjumps].label=op2;          
                    noofjumps++;                 
                    program[counter]=0x5000;     
                       printf("machine code %d \n",     program[counter]);
                    counter++;     
 }
 void add(){
 	
 	op1 = strtok(NULL,"\n\t\r ");                 
                    op2 = strtok(NULL,"\n\t\r ");
                    op3 = strtok(NULL,"\n\t\r ");
                       printf("\n%d     \n", op1);   
                    chch = (op1[0]-48)| ((op2[0]-48)<<3)|((op3[0]-48)<<6);  
                  
                      program[counter]=0x7000+((chch)&0x00ff); 
                      printf("\n%d     \n",  program[counter]);    
              
                    counter++; 
 }
 
void section(){
		op1 = strtok(NULL,"\n\t\r ");                 
                    op2 = strtok(NULL,"\n\t\r ");
                    op3 = strtok(NULL,"\n\t\r ");
                    chch = (op1[0]-48)| ((op2[0]-48)<<3)|((op3[0]-48)<<6);  
                    program[counter]=0x7000+((chch)&0x00ff); 
                      printf("section \n%d     \n",  program[counter]);    
                    counter++; 
} 
 void labelCall(){
 	              labeltable[nooflabels].location = counter;  
                    op1=(char*)malloc(sizeof(token));
                     printf("label location \n%d     \n",  op1);    
                    strcpy(op1,token);
                    labeltable[nooflabels].label=op1;
                     
                    nooflabels++;
 }
main()
{   
    FILE *fp;
     
      
      
     fp = fopen("code.asm","r");

 
	 if (fp != NULL)
    {  
     counter = 0;
        while(fgets(line,sizeof line,fp)!= NULL)  //skip till .code section
		{
			token=strtok(line,"\n\t\r ");
			if (strcmp(token,".code")==0)
			{
				printf("\nsegment .code\n");
				break;
			}
		}
		while(fgets(line,sizeof line,fp)!= NULL)
		{
            token=strtok(line,"\n\t\r ");   

 
            while (token)
            {
            	if (strcmp(token,"section")==0)         
                {
                    section();                                                   
                }   
                else if (strcmp(token,"ldi")==0)         
                {
                    ldi();                                                   
                }                                       
            else if (strcmp(token,"and")==0)                   
                { 
				
				      op1 = strtok(NULL,"\n\t\r ");
                    op2 = strtok(NULL,"\n\t\r ");
                    op3 = strtok(NULL,"\n\t\r ");
                    printf("\n\t%s\t%s   %s   %s\n",strupr(token),op1,op2,op3);
                    chch = (op1[0]-48) | ((op2[0]-48)<<3) | ((op3[0]-48)<<6);
                    program[counter]=0x7200+((chch)&0x00ff); 
                    printf("> %d\t%04x\n",counter,program[counter]);
                    counter++;
				
				
				}
                else if (strcmp(token,"ld")==0)                   
                {                                                 
                               ld();           
                }                                            
                                                          
                else if (strcmp(token,"jmp")==0)   
                {                                            
                      jmp();          
                }                                            
                else if (strcmp(token,"add")==0)  
                {            printf(token);                                
                    add();
                }
               
                else if (strcmp(token,"not")==0)
                {
                    op1 = strtok(NULL,"\n\t\r ");
                    op2 = strtok(NULL,"\n\t\r ");
                    ch = (op1[0]-48)| ((op2[0]-48)<<3);
                    program[counter]=0x7500+((ch)&0x00ff);  
                    counter++;
                }
                 
                else if (strcmp(token,"inc")==0)
                {
                    op1 = strtok(NULL,"\n\t\r ");
                    ch = (op1[0]-48)| ((op1[0]-48)<<3);
                    program[counter]=0x7700+((ch)&0x00ff);  
                    counter++;
                }
                else if (strcmp(token,"pop")==0)
                {
                    op1 = strtok(NULL,"\n\t\r ");
					printf("\n\t%s\t%s\n",strupr(token),op1);
					ch = (op1[0]-48);
					program[counter]=0x9000+((ch)&0x00ff);  
					printf("> %d\t%04x\n",counter,program[counter]);
					counter++;
                }
                 else if (strcmp(token,"push")==0)
                {
		
                    op1 = strtok(NULL,"\n\t\r ");
					printf("\n\t%s\t%s\n",strupr(token),op1);
					ch = ((op1[0]-48)<<5);
					program[counter]=0x8000+((ch)&0x00ff); 
					printf("> %d\t%04x\n",counter,program[counter]);
					counter++;
				
				
				
				}
                else  
                {
                  labelCall();
                } 
                token = strtok(NULL,",\n\t\r ");  
            }
        }
}

     int i,j;         
        for (i=0; i<noofjumps;i++)                                                                 
        {
            j=0;
            while ( strcmp(jumptable[i].label , labeltable[j].label) != 0 )           
                j++;                                                                
            program[jumptable[i].location] +=(labeltable[j].location-jumptable[i].location-1)&0x0fff;      
               printf("machine code %d \n",    program[jumptable[i].location] );
        }                                                     




               
        rewind(fp);  
        while(fgets(line,sizeof line,fp)!= NULL)   
        {
            token=strtok(line,"\n\t\r ");
            if (strcmp(token,".data")==0 )
                break;

        }


                 
        int dataarea=0;
        while(fgets(line,sizeof line,fp)!= NULL)
        {
            token=strtok(line,"\n\t\r ");
            if (strcmp(token,".code")==0 )   
                break;
            else if (token[strlen(token)-1]==':')
            {               
                token[strlen(token)-1]='\0';   
                variabletable[noofvariables].location=counter+dataarea;
                op1=(char*)malloc(sizeof(token));
                strcpy(op1,token);
                variabletable[noofvariables].name=op1;
                token = strtok(NULL,",\n\t\r ");
                if (token==NULL)
                    program[counter+dataarea]=0;
                else if (strcmp(token, ".space")==0)
                {
                    token=strtok(NULL,"\n\t\r ");
                    dataarea+=atoi(token);
                }
                else if((token[0]=='0')&&(token[1]=='x')) {
				
                      program[counter+dataarea]=hex2int(token+2)&0xffff; 
                      printf("machine code %d \n",    program[counter+dataarea]);
                  }
                else if ((  (token[0])=='-') || ('0'<=(token[0])&&(token[0]<='9'))  )
                    program[counter+dataarea]=atoi(token)&0xffff;  
                noofvariables++;
                dataarea++;
            }
        }






 
        for( i=0; i<noofldis;i++)
        {
            j=0;
            while ((j<noofvariables)&&( strcmp( lditable[i].name , variabletable[j].name)!=0 ))
                j++;
            if (j<noofvariables)
                program[lditable[i].location] = variabletable[j].location;              
        } 

 
        for( i=0; i<noofldis;i++)
        {
            j=0;
            while ((j<nooflabels)&&( strcmp( lditable[i].name , labeltable[j].label)!=0 ))
                j++;
            if (j<nooflabels){
                program[lditable[i].location] = (labeltable[j].location)&0x0fff;
                printf("%d %d %d\n", i, j, (labeltable[j].location));   
            }           
        } 

 
    		 
	   printf("label table\n");
        for (i=0;i<nooflabels;i++)
            printf("label %d %s\n", labeltable[i].location, labeltable[i].label); 
        printf("\n");
        printf("JUMP TABLE\n");
        for (i=0;i<noofjumps;i++)
            printf("jmp %d %s\n", jumptable[i].location, jumptable[i].label);   
        printf("\n");
        printf("VARIABLE TABLE\n");
        for (i=0;i<noofvariables;i++)
            printf("var %d %s\n", variabletable[i].location, variabletable[i].name);    
        printf("\n");
        printf("LDI INSTRUCTIONS\n");
        for (i=0;i<noofldis;i++)
            printf("idi %d %s\n", lditable[i].location, lditable[i].name);  
        printf("\n");
        fclose(fp);
        fp = fopen("RAM","w");
        fprintf(fp,"v2.0 raw\n");
        for (i=0;i<counter+dataarea;i++)
            fprintf(fp,"%04x\n",program[i]);
    }   


 int hex2int( char* hex)  
{
    int result=0;

    while ((*hex)!='\0')
    {
        if (('0'<=(*hex))&&((*hex)<='9'))
            result = result*16 + (*hex) -'0';
        else if (('a'<=(*hex))&&((*hex)<='f'))
            result = result*16 + (*hex) -'a'+10;
        else if (('A'<=(*hex))&&((*hex)<='F'))
            result = result*16 + (*hex) -'A'+10; 
        hex++;
    }
    return(result);
}

 
