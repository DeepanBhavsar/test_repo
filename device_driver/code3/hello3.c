#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
static int hello_3_data __initdata = 5;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("eItra character driver example");
MODULE_AUTHOR("jay");

static int __init hello3_init(void)
{
	printk(KERN_INFO "HELLO : THIS is my 1st k modual %d\n",hello_3_data);
	return 0;
}

static void __exit hello3_exit(void)
{
	printk(KERN_INFO "BYE, unloading kernel\n");
}

module_init(hello3_init);
module_exit(hello3_exit);

