#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[]){
	int src, dest;
	ssize_t numread;
	char *buff[BUFF_SIZE];

	//check vaild input
	if(argc != 3 || argv[1] == "--help")
	{
		printf("Invaild input!\nUsage: cpcmd source_file destination_file\n");
		return 1;
	}

	src = open(argv[1], O_RDONLY);
	if (src == -1) 
	{
		printf("\nError opening source file!\n");
		perror("open");
		return 1;
	}

	//S_IXUSR / S_IXOTH / S_IXGRP is for the modes, gicing permission to different groups
	//'X' is either W or R
	int openFlags = O_WRONLY | O_CREAT | O_TRUNC;
	mode_t openModes = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	dest = open(argv[2], openFlags, openModes);

	if (dest == -1) 
	{
		printf("\nError opening destination file!\n");
		perror("open");
		return 1;
	}

	while((numread = read(src, buff, BUFF_SIZE)) > 0)
	{
		write(dest, buff, numread);
	}

	if(numread == -1)
	{
		printf("\nError in reading data from %s\n",argv[1]);
		perror("read");
	}

	if(close(src) == -1)
	{
		printf("\nError in closing file %s\n",argv[1]);
		perror("close");
	}
 
	if(close(dest) == -1)
	{
		printf("\nError in closing file %s\n",argv[2]);
		perror("close");
	}

	close(src);
	close(dest);
	return 0;
}