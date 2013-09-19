#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<error.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<fcntl.h>
int main()
{
    char *str,*temp;
    char **arg;
    char *output;
    arg=(char**)malloc(100*sizeof(char*));
    char c;
    int i,no,start,out,current_out,fd,check=0;
    pid_t pid;
    while(1)
    {
    	//gets(str);
    	str = readline ("Parmeet's Shell:");
	
	if(strcmp(str,"")==0)
	continue;
	
	add_history(str);
		i=0;no=0,out=0,check=0;
		while((c=str[i])!='\0')
		   {
		       arg[no]=(char*)malloc(100*sizeof(char));	
		      
		       while((c=str[i])==' ')
			  i++;
			start=0;
			while((c=str[i])!=' ' && (c=str[i])!='\0')
			  {
			      arg[no][start]=c;
			      start++;
			      i++;
			  }
			  arg[no][start]='\0';
		  	  
		  	  no++;
		  }
		  if(arg[no-1]!=NULL && arg[no-1][0]=='>')
		  out=1,output=&arg[no-1][1],arg[no-1]=(char*)NULL;	
		  	
		  arg[no]=(char*)NULL;

		   if(strcmp(arg[0],"cd")==0)
		   {
		   if(chdir(arg[1])!=0)
		   perror("cd");
		   continue;
		   }
		   if(strcmp("exit",str)==0)
		 	break;
		pid=fork();
		if(pid==0)   
		   {  
			if (out) { //if '>' was found in string inputted by user
			    fd = creat(output, 0666);
			    dup2(fd, STDOUT_FILENO);
			    out = 0;
	    		    current_out = dup(1);
				}
		
		   check=execvp(arg[0],arg);
		   if(check==-1)
		   printf("Command not found\n");
		   _exit(1);
		   }
		else {
 		   wait(&pid);
 		   dup2(current_out, 1);
		}
	  
    }
}
