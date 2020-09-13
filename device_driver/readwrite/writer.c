#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define LEN  100

int main(int argc, char const *argv[])
{
	int fd,ret;
	char string[LEN];
	fd=open("/dev/reader_writer",O_RDWR);
	if (fd<0)
	{
		perror("Fail to open\n");
		return 0;
	}
	printf("Enter string which you want to send \n");
	scanf("%s",string);
	ret=write(fd,string,strlen(string));
	close(fd);
	return 0;
}
