#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;
	char content[fd];

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {

		printf("File is either does not exist or not accessible\n");
		perror("open");
		return 1;
	}
	else {
		//read # bytes from the src file and write
		ssize_t byte = read(fd, content, sizeof(content) - 1);
		write(1, content, byte);
		close(fd);
	}
	return 0;
}
