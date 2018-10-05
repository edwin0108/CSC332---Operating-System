#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	ssize_t rd, wr, wr1;
	ssize_t numread, numread1;
	char buffer[100];
    char buffer1[50];

    //check vaild input
	if(argc != 4 || argv[1] == "--help")
	{
		printf("Invaild input!\nUsage: cpcmd source_file destination_file\n");
		return 1;
	}

	rd = open(argv[1], O_RDONLY | O_CREAT);
	if(rd == -1)
	{
		printf("\nError opening source file!\n");
		perror("open");
		return 1;
	}

	wr = open(argv[2], O_CREAT|O_WRONLY, S_IWUSR | S_IRUSR);
	if(wr == -1)
	{
		printf("\nError opening first destination file!\n");
		perror("open");
		return 1;
	}

    wr1 = open(argv[3], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	if(wr == -1)
	{
		printf("\nError opening second destination file!\n");
		perror("open");
		return 1;
	}

    //using lseek system call to check the size of the source file
	int size = lseek(rd,0L,SEEK_END);
    //printf("size of the file:%d\n", size);// output the size for testing purpose
    lseek(rd,0L,SEEK_SET);

	while (size > 0)
	{
		//replace the next 100 bytes with 1->A && adding XYZ
		if (size >= 150)
		{
			numread = read(rd, buffer, sizeof(buffer) + 1);
			for (int i = 0; i < 100; i++)
	        	if (buffer[i] == '1') buffer[i] = 'A';
			write(wr,buffer,numread);
			size = size - 100;

            numread1 = read(rd, buffer1, sizeof(buffer1) + 1);
            for (int j = 0; j < 50; j++)
                if(buffer1[j] == '2') buffer1[j] = 'B';
            write(wr1,buffer1,numread1);
            size = size - 50;
		}
		//the last step with less than 100 bytes, change 1->A ONLY
		else if (size < 150 && size >= 100) // 100 <= size <= 150
		{
            numread = read(rd, buffer, sizeof(buffer) + 1);
			for (int i = 0; i < 100; i++)
	        	if (buffer[i] == '1') buffer[i] = 'A';
			write(wr,buffer,numread);
			size = size - 100;

            numread1 = read(rd, buffer1, size);
            for (int j = 0; j < size; j++)
                if(buffer1[j] == '2') buffer1[j] = 'B';
            write(wr1,buffer1,numread1);
            size = 0;
		}
        else //size < 100
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
    close(wr1);
	return 0;
}