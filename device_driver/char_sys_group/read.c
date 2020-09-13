#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define LENGTH 100

static char receive[LENGTH];
int main(int argc, char const *argv[])
{
	int fd,ret;
	//fork();
	fd=open("/sys/kernel/kobject_example/foo",O_RDWR);
	if (fd<0)
	{
		perror("Fail to open\n");
		return 0;
	}	
	ret=read(fd,receive,LENGTH);
	printf("The received message : %s\n",receive );
	close(fd);	
	return 0;
}
