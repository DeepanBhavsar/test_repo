#include <linux/module.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/capability.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>
#include <linux/miscdevice.h>

struct test_ioctl {
        int cmd_no;
        char data[64];
};

#define SAMPLE_IOCTL_MAGIC_NUMBER 's'

#define SAMPLE_IOCTL_CMD_1 \
        _IOR(SAMPLE_IOCTL_MAGIC_NUMBER, 0x1, int)

#define SAMPLE_IOCTL_CMD_2 \
        _IOW(SAMPLE_IOCTL_MAGIC_NUMBER, 0x2, int)

#define SAMPLE_IOCTL_CMD_3 \
        _IO(SAMPLE_IOCTL_MAGIC_NUMBER, 0x3)

#define SAMPLE_IOCTL_CMD_4 \
        _IOWR(SAMPLE_IOCTL_MAGIC_NUMBER, 0x4, struct test_ioctl)

char ei_str[100];
static ssize_t sample_char_read(struct file * file, char __user * buf,
                       size_t count, loff_t *fpos)
{
	int len ;
	printk(KERN_NOTICE "ei-driver: read called..\n");
	strcpy(ei_str,"Welcome to eItra driver\n");
	len=strlen(ei_str);

        if (count < len)
                return -EINVAL;

        if (*fpos != 0)
                return 0;

	if (!access_ok(VERIFY_WRITE, buf, count))
		return -EFAULT;

        if (copy_to_user(buf, ei_str, len))
                return -EINVAL;

	*fpos = len;
       	return len;
}

static ssize_t sample_char_write(struct file * file, char __user * buf,
                       size_t count, loff_t *fpos)
{
	int len = 100;
	printk(KERN_INFO "ei-driver: write called..\n");

        if (count > len)
                return -EINVAL;

	if (!access_ok(VERIFY_READ, buf, count))
		return -EFAULT;

        if (copy_from_user(ei_str,buf, count))
                return -EINVAL;
	ei_str[count]='\0';

	printk(KERN_INFO "value written into device is: %s",ei_str);

        return count;

}

int sample_char_open(struct inode *inode, struct file *filp)
{
       printk("sample_char_open\n");
       return 0;
}

int sample_char_release(struct inode *inode, struct file *filp)
{

       printk("sample_char_release\n");
       return 0;
}

/*
 * The ioctl() implementation
 */

int sample_char_ioctl (struct file *filp,
                 unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	int v = 20;
	printk("sample_char_ioctl\n");
	switch (cmd) {
	case SAMPLE_IOCTL_CMD_1:
		printk("IOCTL CMD1\n");
		put_user(v,(char *)arg);
		printk("v: %d\n",v);
				
		/*Do Something*/
	break;
	case SAMPLE_IOCTL_CMD_2:
		printk("IOCTL CMD2\n");
		get_user(v,(char *)arg);
		printk("v: %d\n",v);
		/*if (copy_from_user(ei_str,(char *)arg, 4))
                	return -EINVAL;
		ei_str[strlen(ei_str)+1]='\0';

		printk(KERN_INFO "value written into device is: %s",ei_str);
	*/
		/*Do Something*/
	break;
	case SAMPLE_IOCTL_CMD_3:
		printk("IOCTL CMD3\n");
		/*Do Something*/
	break;
	case SAMPLE_IOCTL_CMD_4:
		printk("IOCTL CMD4\n");
		get_user(v,(char *)arg);
		printk("v: %d\n",v);
		v=30;
		put_user(v,(char *)arg);
		printk("v: %d\n",v);
		/*Do Something*/
	break;

	default: /*Default option*/
		/*Do Something or return invalid command error*/
		printk("Invalid IOCTL CMD\n");
		ret = -EINVAL;
	}
	return ret;
}

static struct file_operations sample_char_fops = {
       read:          sample_char_read,
       write:         sample_char_write,
       open:          sample_char_open,
       release:        sample_char_release,
       unlocked_ioctl:	sample_char_ioctl,
};

static struct miscdevice	misc_dev = {
	.minor =  MISC_DYNAMIC_MINOR,
        .name = "sample_misc_ioctl_dev",
        .fops =  &sample_char_fops,
        .mode = S_IRWXUGO,
};
int major_no;

int init_module(void)
{
	int ret = 0;
	printk("\nLoading the sample misc char device driver\n");
	ret = misc_register(&misc_dev);
	if (ret)
		 printk("Unable to register misc dev\n");
	return ret;
}

void cleanup_module(void)
{
       	printk("\nUnloading the sample char device driver\n");
	misc_deregister(&misc_dev);

}
