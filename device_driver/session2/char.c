#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
//#include "char_ioctl.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("eItra character driver example");
MODULE_AUTHOR("Jay");

ssize_t ei_char_read(struct file *, char *, size_t , loff_t *);
ssize_t ei_char_write(struct file *, const char *, size_t , loff_t *);
int ei_char_open(struct inode *, struct file *);
int ei_char_release(struct inode *, struct file *);
//long ei_char_ioctl(struct file *, unsigned int, unsigned long);

static struct file_operations ei_fops = 
{
	.owner = THIS_MODULE,
	.read = ei_char_read,
	.write = ei_char_write,
	.open = ei_char_open,
	.release = ei_char_release,
	//.unlocked_ioctl = ei_char_ioctl,
};

static int ei_major = 1;
static const char dev_name[] = "ei-driver";

static int register_device(void)
{
	int res;
	printk(KERN_NOTICE "ei-driver: register char device is called\n");

	res = register_chrdev(0, dev_name, &ei_fops);
	if (res < 0)
	{
		printk(" ei device registration failed\n");
		return res;
	}

	ei_major = res;
//	printk("'mknod /dev/ei-driver c %d 0'",ei_major);
	printk(KERN_NOTICE "ei-driver: registerd as a char device with major # = %d\n", ei_major);
	return 0;
}

void unregister_device(void)
{
	printk(KERN_NOTICE "ei-driver: unregistering...\n");
	if (ei_major != 0)
{
printk("'rm /dev/ei-driver'");		
unregister_chrdev(ei_major, dev_name);
}
}


char ei_str[100];

ssize_t ei_char_read(struct file *fp, char __user *buf, size_t count, loff_t *fpos)
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

ssize_t ei_char_write(struct file *fp, const char __user *buf, size_t count, loff_t *fpos)
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

/*long ei_char_ioctl(struct file *fp, unsigned int ioctl_no, unsigned long ioctl_param)
{
	switch (ioctl_no)
	{
		case IOCTL_SET_MSG:
			printk(KERN_INFO "SET MSG ioctl is called\n");
			break;
		case IOCTL_GET_MSG:
			printk(KERN_INFO "GET MSG ioctl is called\n");
			break;
	}
	return 0;
}
*/
int ei_char_open(struct inode *node, struct file *fp)
{
        printk(KERN_NOTICE "ei-char-driver: open is called\n");
        return 0;
}

int ei_char_release(struct inode *node, struct file *fp)
{
        printk(KERN_NOTICE "ei-char-driver: release is called\n");
        return 0;
}


static int ei_char_init(void)
{
	printk(KERN_ALERT "ei Char driver Init\n");
	return register_device() ;
}



static void ei_char_exit(void)
{
	unregister_device() ;
	printk(KERN_ALERT "Bye\n");
}

module_init(ei_char_init);
module_exit(ei_char_exit);

