#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd, fd1;
    if (argc != 3 || argv[1] == "--help")
    {
        printf("Invaild input!\nUsage: create file1 file2\n");
		return 1;
    }
    
    fd = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    fd1 = open(argv[2], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1 && fd1 == -1)
    {
        perror("Open failed: ");
    }
    else
    {
        printf("\n open() Successful\n");
    }
    return 0;
}