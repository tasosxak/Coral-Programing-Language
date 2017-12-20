#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


void remExt(char* mystr) {
    char *lastdot;
    if (mystr == NULL)
         return;
    lastdot = strrchr (mystr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
}

int main(int argc, char* argv[]){
	
	int i;
	char* dot;
	char* filename;
	char str[255];
	int error = 0;
	
	for(i=1; i<argc; i++){
		
		dot = strrchr(argv[i], '.');
		if (dot && !strcmp(dot, ".cl")){
		    
			
		    remExt(argv[i]);
			
			sprintf(str,"precoral %s.cl",argv[i]);
			error = system(str);
			
			if(error) exit(1);
		    
		    sprintf(str,"coralc<final.clc");
		    error = system(str);
			
			if(error) exit(1);
		    
			
			
		    sprintf(str,"mkdir %s",argv[i]);
		    error = system(str);
		    if(error) exit(1);
		    
		    error = system("nasm -f win32 program.asm");
			if(error) exit(1);
			
		    sprintf(str,"gcc -m32 program.obj -o %s/%s.exe",argv[i],argv[i]);
	            error = system(str);
		    if(error) exit(1);
			
		    error = system("del program.asm");
		    if(error) exit(1);
	        error = system("del program.obj");
		    if(error) exit(1);
			error = system("del final.clc");
		    if(error) exit(1);

		}
		else{
		    printf("Wrong extension. The correct extension is '.cl'\n");
		    exit(1);
		}
		    
	
	}

 
	
	return 0;
	
}
