#include<stdio.h>
#include<string.h>
#include<fcntl.h>
int main()
{
int fd,i=0;
char buff[100];
fd=open("/proc/driver/mydriver/settings/hello",O_RDONLY);
read(fd,buff,13);
buff[13]='\0';
printf("%s read from device\n",buff);
close(fd);
return 0;
}
