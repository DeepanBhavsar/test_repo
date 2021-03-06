#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

struct test_ioctl {
        int cmd;
        char data[64];
}s1;

struct rw{
	int read;
}s;

#define SAMPLE_IOCTL_MAGIC_NUMBER 's'

#define SAMPLE_IOCTL_CMD_1 \
        _IOR(SAMPLE_IOCTL_MAGIC_NUMBER, 0x1, int)

#define SAMPLE_IOCTL_CMD_2 \
        _IOW(SAMPLE_IOCTL_MAGIC_NUMBER, 0x2, int)

#define SAMPLE_IOCTL_CMD_3 \
        _IO(SAMPLE_IOCTL_MAGIC_NUMBER, 0x3)

#define SAMPLE_IOCTL_CMD_4 \
        _IOWR(SAMPLE_IOCTL_MAGIC_NUMBER, 0x4, struct test_ioctl)


int main()
{
	int fd, ret = 0, val = 0;
	
	fd = open("/dev/sample_misc_ioctl_dev", O_RDWR);

	printf("file descriptor fd(%d)\n", fd);
	if (fd < 0) {
		printf("File open error\n");	
	}

	printf("Sending ioctl CMD 3\n");
	ret = ioctl(fd, SAMPLE_IOCTL_CMD_3);
	printf("ioctl ret val (%d) errno (%d)\n", ret, errno);
	perror("IOCTL error: ");

	printf("Sending ioctl CMD 1\n");
	ret = ioctl(fd, SAMPLE_IOCTL_CMD_1, &val);
	printf("ioctl ret val (%d) ,val : %d ,errno (%d)\n", ret,val,errno);
	perror("IOCTL error: ");

	val = 10;
	printf("Sending ioctl CMD 2\n");
	ret = ioctl(fd, SAMPLE_IOCTL_CMD_2, &val);
	printf("ioctl ret val (%d) errno (%d)\n", ret, errno);
	perror("IOCTL error: ");

	//s1.data="Hello";
	s1.cmd = 1;
	s1.data[0]='H';
	s1.data[1]='i';
	s1.data[2]='\0';
	printf("Sending ioctl CMD 4\n");
	ret = ioctl(fd, SAMPLE_IOCTL_CMD_4, &s1);
	printf("ioctl ret val (%d) errno (%d) %s\n", ret, errno,s1.data);
	perror("IOCTL error: ");
	close(fd);
}
