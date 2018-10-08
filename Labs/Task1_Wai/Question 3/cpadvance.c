#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char* argv[]){
	ssize_t rd, wr;
	ssize_t numread;
	char buffer[100];
	char addchar[] = "XYZ";

    //check vaild input
	if(argc != 3 || argv[1] == "--help")
	{
		printf("Invaild input!\nUsage: cpcmd source_file destination_file\n");
		return 1;
	}

	rd = open(argv[1], O_RDONLY | O_CREAT);
	if(rd == -1)
	{
		printf("\nError opening source file!\n");
		perror("open")
		return 1;
	}

	wr = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	if(wr == -1)
	{
		printf("\nError opening destination file!\n");
		perror("open")
		return 1;
	}

    //using lseek system call to check the size of the source file
	int size = lseek(rd,0L,SEEK_END);
    //printf("size of the file:%d\n", size);// output the size for testing purpose
    lseek(rd,0L,SEEK_SET);

	while (size > 0)
	{
		//replace the next 100 bytes with 1->A && adding XYZ
		if (size >= 100)
		{
			numread = read(rd, buffer, sizeof(buffer) + 1);
			for (int i=0; i<100; i++)
	        	if (buffer[i] == '1') buffer[i] = 'A';
			write(wr,buffer,numread);
			write(wr,addchar, 3);
			size = size - 100;
		}
		//the last step with less than 100 bytes, change 1->A ONLY
		else
		{
			numread = read(rd, buffer, size);
			for (int i=0; i<size; i++)
	        	if (buffer[i] == '1') buffer[i] = 'A';
	        write(wr,buffer,numread);
	        size = 0;
		}
	}
	close(rd);
	close(wr);
	return 0;
}