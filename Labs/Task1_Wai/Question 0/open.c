#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv){
	int fd;
	if(argc != 2)
	{
		printf("Invaild input!\nUsage: open source_file\n");
		return 1;
	}

	//read only and create new file if not exist
	fd = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

	printf("fd = %d\n", fd);

	//check error
	if (fd == -1) 
	{
		printf("Error Number %d\n", errno);

		perror("Program");
	}
	else 
	{
		printf("\n Open() Successful\n");
	}
	return 0;
}