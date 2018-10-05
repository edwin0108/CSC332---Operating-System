#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t child1, child2;
    pid_t pid;

    int status;

    child1 = fork();
    if(child1 == 0)
    {
        printf("child1 PID is: %d\n", getpid());
        char* arg1[] = {"./proc1", "destionation1.txt", "destionation2.txt", NULL};
        execv(arg1[0], arg1);
        perror("Child1: ");
        exit(EXIT_FAILURE);
    }

    child2 = fork();
    if(child2 == 0)
    {
        printf("child1 PID is: %d\n", getpid());
        char* arg2[] = {"./proc2", "source.txt", "destionation1.txt", "destionation2.txt", NULL};
        execv(arg2[0], arg2);
        perror("Child2: ");
        exit(EXIT_FAILURE);
    }

    while ((pid = waitpid(-1, &status, 0)) != -1)
    {
        printf("PID %d has terminated.\n",pid);
    }

    printf("All process has been terminated. \n");
    return EXIT_SUCCESS;
}