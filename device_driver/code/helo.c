#include<linux/init.h>	
#include<linux/module.h>	
#include<linux/kernel.h>
#include <linux/fs.h>
	

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("eItra character driver example");
MODULE_AUTHOR("jay");

static int hello_init(void)		
{	
	printk(KERN_INFO "Hello:This is my first kernel module\n");
	return 0;	
}	
static void hello_exit(void)
{
	printk(KERN_INFO "bye unloading the module\n");	
}	

module_init(hello_init);	
module_exit(hello_exit);	
MODULE_DESCRIPTION("Greeting module");	
MODULE_AUTHOR("eItra");
