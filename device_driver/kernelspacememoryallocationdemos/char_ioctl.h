#include <linux/ioctl.h>

#define MAJOR_NUM 'j'

#define IOCTL_SET_MSG _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_MSG _IOR(MAJOR_NUM, 1, char *)
