#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    argv[0] = "ls";
    argv[1] = "-la";
    argv[2] = NULL;
    pid_t child = fork();
    if(child != 0)
    {
        printf("The child PID is: %d\n", getpid());
        execvp(argv[0], argv);
    }
    else if (child == -1)
    {
        perror("error: ");
    }
}