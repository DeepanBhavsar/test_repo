#include<stdio.h>
#include<string.h>
#include<fcntl.h>
int main()
{
int fd,i=0;
char buff[100];
fd=open("/proc/driver/mydriver/settings/hello",O_WRONLY);
scanf("%s",buff);
write(fd,buff,strlen(buff));
close(fd);
return 0;
}
