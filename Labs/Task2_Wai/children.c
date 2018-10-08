#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    pid_t child1, child2;
    pid_t pid;
    child1 = fork();
    if(child1 == 0)
        printf("I am child one, my pid is: %d\n", getpid());
    else
    {
        pid = wait(child1, NULL, 0);
        child2 = fork();
        if(child2 == 0)
        {
            printf("I am child two, my pid is: %d\n",getpid());
        }
        else
        {
            pid = wait(child2, NULL, 0);
            printf("I am parent, my pid is: %d\n",getpid());
        }
    }
    return 0;
}
