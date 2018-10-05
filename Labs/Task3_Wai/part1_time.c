#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child = fork();
    if(child != 0)
    {
        printf("The child PID is: %d\n", getpid());
        execl("/bin/date", "date", NULL);
        
    }
    else if (child == -1)
    {
        perror("error: ");
    }
}