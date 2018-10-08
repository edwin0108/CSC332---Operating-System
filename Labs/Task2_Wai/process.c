#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    /* code */
    int a = 10, b = 25, fq = 0, fr = 0;
    fq = fork();
    if(fq == 0)
    {
        a = a + b;
        printf("\nValue of a is: %d", a);
        printf("\nValue of b is: %d", b);
        printf("\nThe pid is: %d\n", getpid());
        fr = fork();

        if(fr != 0)
        {
            b = b + 20;
            printf("\nValue of a is: %d", a);
            printf("\nValue of b is: %d", b);
            printf("\nThe pid is: %d", getpid());
        }
        else
        {
            a = (a * b) + 30;
            printf("\nValue of a is: %d", a);
            printf("\nValue of b is: %d", b);
            printf("\nThe pid is: %d", getpid());
        }

    }
    else
    {
        b = a + b - 5;
        printf("\nValue of a is: %d", a);
        printf("\nValue of b is: %d", b);
        printf("\nThe pid is: %d", getpid());
    }
    return 0;
}
