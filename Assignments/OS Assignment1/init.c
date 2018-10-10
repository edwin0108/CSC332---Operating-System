#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main(int argc, char* argv[])
{
    pid_t cpu_id, scheduler_id;
    pid_t pid;
    int status;

    cpu_id = fork();
    if(cpu_id == 0)
    {
        printf("CPU_Emulator pid is: %d\n", getpid());
        execl("/usr/bin/java", "/usr/bin/java", "-cp", "CPU_Emulator.jar", "CPU_Emulator", NULL);
        perror("CPUServer");
        exit(EXIT_FAILURE);
    }

    scheduler_id = fork();
    if(scheduler_id == 0)
    {
        printf("Scheduler pid is: %d\n", getpid());
        if (argc > 1)
        {
            if(strcmp(argv[1],"priority") == 0)
                execl("/usr/bin/java", "/usr/bin/java", "-cp", "Scheduler.jar", "Scheduler", "priority", NULL);
        }
        else
            execl("/usr/bin/java", "/usr/bin/java", "-cp", "Scheduler.jar", "Scheduler", NULL);
        perror("Scheduler");
        exit(EXIT_FAILURE);
    }

    while ((pid = waitpid(-1, &status, 0)) != -1)
    {
        printf("PID %d has terminated.\n",pid);
    }

    printf("All process has been terminated. \n");
    return EXIT_SUCCESS;
}
