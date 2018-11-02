#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define BUFFSIZE 1024

int main(void) {
    char line[BUFFSIZE];

    while(1) {
        printf("~$ ");
        if(!fgets(line, BUFFSIZE, stdin)) 
        	break;
        char *p = strchr(line, '\n');
        if (p) 
        	*p = 0;

        if(strcmp(line, "quit")==0) 
        	break;

        int i = 0;
        char* argv[10];
        argv[i]  = strtok(line, " ");
        
        while(argv[i] != NULL)
        	argv[++i] = strtok(NULL, " ");
        
        int pid = fork(); //fork a child
        if(pid < 0)
        	printf("Fork Failed\n");
        else if(pid==0)
        {               
            execvp(argv[0], argv); 	
            perror("exec");
            exit(1);
        } 
        else //Parent process
            wait(NULL);
    }
    return 0;
}
