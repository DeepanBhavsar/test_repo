#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("eItra character driver example");
MODULE_AUTHOR("jay");

static int __init hello2_init(void)
{
	printk(KERN_INFO "HELLO : THIS is my 1st k modual\n");
	return 0;
}

static void __exit hello2_exit(void)
{
	printk(KERN_INFO "BYE, unloading kernel\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

